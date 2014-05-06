//! \file EventLoop.cpp
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Description
//! 
#include "LEngine.h"

#include "SDLMain.h"
#include "SDLEventLoop.h"
#include "SDLThread.h"
#include "SDLTimer.h"

#include "LGameBase.h"

#include "debug.h"
#include "eError.h"

#define DebugTimerUpdateRate_Sec 5.0f

#define ms_30FPS 33
#define ms_60FPS 16

#define defaultWindowWidth 720 
#define defaultWindowHeight 480

//===============================================================
LEngine::LEngine()
: m_gameUpdateThread		( "Game" , GameThreadStart		)
, m_renderThread			( "Render" , RenderThreadStart	)
, m_msDesiredFrameTime		( ms_60FPS )
, m_windowWidth				( defaultWindowWidth )
, m_windowHeight			( defaultWindowHeight )
{

}

//===============================================================
LEngine::~LEngine()
{

}

//===============================================================
eError LEngine::run_full()
{
	//Initialization flag
	eError err = eError::NoErr;

	// Initialise the engine
	if (!ERROR_HAS_TYPE_FATAL(err))
		err |= init();

	// Run the engine
	if (!ERROR_HAS_TYPE_FATAL(err))
		err |= run();

	// Quit the engine
	if (!ERROR_HAS_TYPE_FATAL(err))
		err |= quit();

	return err;
}

//===============================================================
eError LEngine::init()
{
	RUNTIME_LOG("Initialising...")

    //Initialization flag
    eError err = eError::NoErr;

	// initialise SDL
	err = SDLInterface::Init();

	// create the sdl event loop
	if (!ERROR_HAS_TYPE_FATAL(err))
		err = SDLInterface::EventLoop::Create();

	// Create the window
	if (!ERROR_HAS_TYPE_FATAL(err))
		err = m_MainWindow.Create(m_windowWidth, m_windowHeight);

	// Create the renderer
	if (!ERROR_HAS_TYPE_FATAL(err))
		err = m_Renderer.Create(&m_MainWindow);

	// Create the objects
	if( !ERROR_HAS_TYPE_FATAL( err ) )
		err = m_ObjectManager.Create();

    return err;
}

//===============================================================
eError LEngine::run()
{
	eError err = eError::NoErr;

	// Load up
	err |= load();

	// do the full engine loop
	if (!ERROR_HAS_TYPE_FATAL(err))
		err |= loop();

	// unload
	if (!ERROR_HAS_TYPE_FATAL(err))
		err |= unload();

	return err;
}

//===============================================================
eError LEngine::quit()
{
	RUNTIME_LOG("Quiting...")

	eError err = eError::NoErr;

	// Destroy the renderer
	if (!ERROR_HAS_TYPE_FATAL(err))
		err |= m_Renderer.Destroy();

	// Destroy the main window
	if (!ERROR_HAS_TYPE_FATAL(err))
		err |= m_MainWindow.Destroy();

    //Quit SDL subsystems
	if (!ERROR_HAS_TYPE_FATAL(err))
		SDLInterface::Quit();

    return err;
}

//===============================================================
eError LEngine::load()
{
	RUNTIME_LOG("Loading...")
    
	//Loading err flag
    eError err = eError::NoErr;

	// Create the game
    err |= LGameBase::GetGame()->Create();

	// Initialse the game
	if (!ERROR_HAS_TYPE_FATAL(err))
        err |= LGameBase::GetGame()->Initialise();

	// Load the banana
	if (!ERROR_HAS_TYPE_FATAL(err))
		err |= m_banana.Create(&m_Renderer, "Media/banana.jpg");

	// Create the objects
	if( !ERROR_HAS_TYPE_FATAL( err ) )
		err = m_ObjectManager.Initialise();

    return err;
}

//===============================================================
eError LEngine::loop()
{
	eError err = eError::NoErr;
	RUNTIME_LOG("Looping...")

	// Spawn both the threads
	if (!ERROR_HAS_TYPE_FATAL(err))
		err | m_gameUpdateThread.Spawn(this);

	if (!ERROR_HAS_TYPE_FATAL(err))
		err | m_renderThread.Spawn(this);

	// Do the main SDL event loop
	if (!ERROR_HAS_TYPE_FATAL(err))
		err |= SDLInterface::EventLoop::DoLoop();

	// Remove any quit request error
	REMOVE_ERR(err, eError::QuitRequest);

	// Wait for all the threads to close off
	// Do this regardless of Error state
	if (!ERROR_HAS_TYPE_FATAL(err))
		err |= m_renderThread.Wait();

	if (!ERROR_HAS_TYPE_FATAL(err))
		err |= m_gameUpdateThread.Wait();

    return err;
}

//===============================================================
eError LEngine::unload()
{
	eError err = eError::NoErr;

	// Create the objects
	if( !ERROR_HAS_TYPE_FATAL( err ) )
		err |= m_ObjectManager.Destroy();

	if (!ERROR_HAS_TYPE_FATAL(err))
		err |= m_banana.Destroy();

	// Destroy the game
	if (!ERROR_HAS_TYPE_FATAL(err))
		err |= LGameBase::GetGame()->Destroy();

	return err;
}

//===============================================================
eError LEngine::Render()
{
	eError err = eError::NoErr;

	// Start the renderer
	err |= m_Renderer.RenderStart();

	//TODO: render the objects

	// Test code for rendering a rectangle
	//SDLInterface::Rect rect = { 50, 50, 50, 50 };
	//err |= m_Renderer.RenderRectangle( rect, 100, 150, 0, 255);

	// Render the banana
	SDLInterface::Rect rect = { 0, 0, 400, 300 };
	SDLInterface::Rect drect = { 0, 0, defaultWindowWidth, defaultWindowHeight };
	m_Renderer.RenderTexture(&m_banana, rect, drect);

	// End the renderer
	err |= m_Renderer.RenderEnd();

	return err;
}

//===============================================================
eError LEngine::PreUpdate( void )
{
	eError err = eError::NoErr;

	err |= LGameBase::GetGame()->PreUpdate();

	return err;
}

//===============================================================
eError LEngine::Update(ms elapsed)
{
	eError err = eError::NoErr;

	// We need to decide when this happens
	err |=  m_ObjectManager.Update( elapsed );

	// Update the game
	err |= LGameBase::GetGame()->Update(elapsed);

	return err;
}

//===============================================================
eError LEngine::PostUpdate( void )
{
	eError err = eError::NoErr;

	err |= LGameBase::GetGame()->PostUpdate();

	return err;
}

//===============================================================
eError LEngine::RenderThreadLoop()
{
	eError err = eError::NoErr;

	// the current frame time
	ms frameTime = SDLInterface::Timer::GetGlobalLifetime();

	// Timer for the logging
	SDLInterface::Timer logTimer;
	logTimer.Start();

	// frame counter
	unsigned int frameCounter = 0;


	while (!ERROR_HAS_TYPE_FATAL(err)
		&& !ERROR_HAS(err, eError::QuitRequest))
	{
		// Delay until the end of the desired frame time
		err |= SDLInterface::Thread::DelayUntil(frameTime + m_msDesiredFrameTime);
		
		// Update the engine window
		err |= Render();

		// grab the current time
		frameTime = SDLInterface::Timer::GetGlobalLifetime();

		// get if the EventLoop has finished
		err |= SDLInterface::EventLoop::GetHasFinished();

		// Increment the framecounter
		frameCounter++;

		// if the timer is over the 
		if (logTimer.GetTimePassed() >= secToMS(DebugTimerUpdateRate_Sec))
		{
			// Debug output
			RUNTIME_LOG("Render thread updates per second %f", (float)frameCounter / DebugTimerUpdateRate_Sec);

			// Reset the timer and the frame counter
			logTimer.Reset();
			frameCounter = 0;
		}

	}

	// remove any quit request error
	REMOVE_ERR(err, eError::QuitRequest);

	return err;
}

//===============================================================
eError LEngine::GameThreadLoop()
{
	eError err = eError::NoErr;

	// the current frame time
	ms frameTime = SDLInterface::Timer::GetGlobalLifetime();

	// Timer for the logging
	SDLInterface::Timer logTimer;
	logTimer.Start();

	// frame counter
	unsigned int frameCounter = 0;

	// The main loop
	while ( !ERROR_HAS_TYPE_FATAL( err )
		&& !ERROR_HAS( err, eError::QuitRequest ) )
	{
		// Delay until the end of the desired frame time
		err |= SDLInterface::Thread::DelayUntil( frameTime + m_msDesiredFrameTime );

		// Call any pre-update functionality
		err |= PreUpdate();

		// Call the main engine update method
		err |= Update( m_msDesiredFrameTime );

		// Call any post-update functionality
		err |= PostUpdate();

		// grab the current time
		frameTime = SDLInterface::Timer::GetGlobalLifetime();

		// get if the EventLoop has finished
		err |= SDLInterface::EventLoop::GetHasFinished();

		// Increment the framecounter
		frameCounter++;

		// if the timer is over the 
		if (logTimer.GetTimePassed() >= secToMS(DebugTimerUpdateRate_Sec))
		{
			// Debug output
			RUNTIME_LOG("Game thread updates per second %f", (float)frameCounter / DebugTimerUpdateRate_Sec);

			// Reset the timer and the frame counter
			logTimer.Reset();
			frameCounter = 0;
		}
			
	}

	// remove any quit request error
	REMOVE_ERR(err, eError::QuitRequest);

	return err;
}

//===============================================================
eError LEngine::SetDesiredFrameTime(ms frameTime)
{
	eError err = eError::NoErr;

	DEBUG_ASSERT(frameTime > 0);

	m_msDesiredFrameTime = frameTime;

	return err;
}

//===============================================================
eError LEngine::SetWindowSize(int w, int h)
{
	m_windowWidth = w;
	m_windowHeight = h;

	return eError::NoErr;
}

//===============================================================
int GameThreadStart(void* data)
{
	DEBUG_LOG("GameThread Starting");
	eError err = eError::NoErr;

	// Grab the engine from the thread data
	LEngine* thisEngine = (LEngine*)data;

	// Run the game thread loop
	err =thisEngine->GameThreadLoop();

	DEBUG_LOG("GameThread Ending");
	return (int)err;
}

//===============================================================
int RenderThreadStart(void* data)
{
	DEBUG_LOG("RenderThread Starting");
	eError err = eError::NoErr;

	// Grab the engine from the thread data
	LEngine* thisEngine = (LEngine*)data;

	// Run the render thread loop
	err = thisEngine->RenderThreadLoop();

	DEBUG_LOG("RenderThread Ending");
	return (int)err;
}