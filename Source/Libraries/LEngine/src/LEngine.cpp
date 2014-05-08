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
, m_engineThread			( "LEngine" , EngineThreadStart )
, m_msDesiredFrameTime		( ms_60FPS )
, m_windowWidth				( defaultWindowWidth )
, m_windowHeight			( defaultWindowHeight )
, m_bQuitting				( false )
{

}

//===============================================================
LEngine::~LEngine()
{

}


//===============================================================
eError LEngine::Start()
{
	//Initialization flag
	eError err = eError::NoErr;

	// Initialise the engine
	if (!ERROR_HAS_TYPE_FATAL(err))
		err |= PreInit();

	// Spawn both the threads
	if (!ERROR_HAS_TYPE_FATAL(err))
		err | m_engineThread.Spawn(this);

	// Do the main SDL event loop
	if (!ERROR_HAS_TYPE_FATAL(err))
		err |= SDLInterface::EventLoop::DoLoop();

	// If the event loop has quit here without the engine requesting it we need to request one
	// This should only happen if the event loop has recieved a fatal error of some kind
	RequestQuit();

	if (!ERROR_HAS_TYPE_FATAL(err))
		err |= m_engineThread.Wait();

	return err;
}

//===============================================================
eError LEngine::RunFull()
{
	//Initialization flag
	eError err = eError::NoErr;

	// Initialise the engine
	if (!ERROR_HAS_TYPE_FATAL(err))
		err |= Init();

	// Run the engine
	if (!ERROR_HAS_TYPE_FATAL(err))
		err |= Run();

	// Quit the engine
	if (!ERROR_HAS_TYPE_FATAL(err))
		err |= Quit();

	// Request the quit for the SDLEventLoop
	// Note: by the point this is called ALL dependent code must have finished
	SDLInterface::EventLoop::EndLoop();

	return err;
}

//===============================================================
eError LEngine::PreInit()
{
    //Initialization flag
    eError err = eError::NoErr;

	// initialise SDL
	err |= SDLInterface::Init();

	// create the sdl event loop
	if (!ERROR_HAS_TYPE_FATAL(err))
		err |= SDLInterface::EventLoop::Create();

    return err;
}

//===============================================================
eError LEngine::Init()
{
	RUNTIME_LOG("Initialising...")

    //Initialization flag
    eError err = eError::NoErr;

	// Create the window
	if (!ERROR_HAS_TYPE_FATAL(err))
		err |= m_MainWindow.Create(m_windowWidth, m_windowHeight);

	// Create the renderer
	if (!ERROR_HAS_TYPE_FATAL(err))
		err |= m_Renderer.Create(m_MainWindow);

	// Create the objects
	if( !ERROR_HAS_TYPE_FATAL( err ) )
		err |= m_ObjectManager.Create();

    return err;
}

//===============================================================
eError LEngine::Run()
{
	eError err = eError::NoErr;

	// Load up
	err |= Load();

	// do the full engine loop
	if (!ERROR_HAS_TYPE_FATAL(err))
		err |= Loop();

	// unload
	if (!ERROR_HAS_TYPE_FATAL(err))
		err |= Unload();

	return err;
}

//===============================================================
eError LEngine::Quit()
{
	RUNTIME_LOG("Quiting...")

	eError err = eError::NoErr;

	// Destroy the renderer
	if (!ERROR_HAS_TYPE_FATAL(err))
		err |= m_Renderer.Destroy();

	// Destroy the main window
	if (!ERROR_HAS_TYPE_FATAL(err))
		err |= m_MainWindow.Destroy();

    return err;
}

//===============================================================
eError LEngine::End()
{
	eError err = eError::NoErr;

	//Quit SDL subsystems
	if (!ERROR_HAS_TYPE_FATAL(err))
		err |= SDLInterface::Quit();

	return err;
}

//===============================================================
eError LEngine::Load()
{
	RUNTIME_LOG("Loading...")
    
	//Loading err flag
    eError err = eError::NoErr;

	// Create the game
    err |= LGameBase::GetGame()->Create();

	// Initialse the game
	if (!ERROR_HAS_TYPE_FATAL(err))
        err |= LGameBase::GetGame()->Initialise();

	// Create the banana
	if (!ERROR_HAS_TYPE_FATAL(err))
		err |= m_banana.Create(m_Renderer, "Media/banana.jpg");

	// Set up the banana
	m_banana.SetSourceRect( {0,0,400,300} );
	m_banana.SetSize(200, 150);
	m_banana.SetPos(defaultWindowWidth / 2, defaultWindowHeight / 2);

	// Add said banana to the renderer
	if (!ERROR_HAS_TYPE_FATAL(err))
		err |= m_Renderer.AddRenderable(&m_banana);

	// Initialise the objects
	if( !ERROR_HAS_TYPE_FATAL( err ) )
		err |= m_ObjectManager.Initialise();

    return err;
}

//===============================================================
eError LEngine::Loop()
{
	eError err = eError::NoErr;
	RUNTIME_LOG("Looping...")

	// Spawn both the threads
	if (!ERROR_HAS_TYPE_FATAL(err))
		err | m_gameUpdateThread.Spawn(this);

	if (!ERROR_HAS_TYPE_FATAL(err))
		err | m_renderThread.Spawn(this);

	// Spin while not quitting
	while ( !QuitHasBeenRequested() 
		&& !SDLInterface::EventLoop::QuitHasBeenRequested() )
	{
		SDLInterface::Thread::Delay(10);
	}

	// Set that we're quiting now ( in the case that the event loop has quit )
	RequestQuit();

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
eError LEngine::Unload()
{
	eError err = eError::NoErr;

	// Remove the banana from the renderer
	if (!ERROR_HAS_TYPE_FATAL(err))
		err |= m_Renderer.RemoveRenderable(&m_banana);

	// Destroy the game
	if (!ERROR_HAS_TYPE_FATAL(err))
		err |= LGameBase::GetGame()->Destroy();

	return err;
}

//===============================================================
eError LEngine::Render()
{
	eError err = eError::NoErr;

	// Run the renderer
	err |= m_Renderer.Render();

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

		// get if the engine has finished
		if (QuitHasBeenRequested())
			err |= eError::QuitRequest;

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

		// get if the engine has finished
		if (QuitHasBeenRequested())
			err |= eError::QuitRequest;

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
bool LEngine::QuitHasBeenRequested()
{
	return m_bQuitting;
}

//===============================================================
void LEngine::RequestQuit()
{
	m_bQuitting = true;
}

//===============================================================
int EngineThreadStart(void* data)
{
	DEBUG_LOG("EngineThread Starting");
	eError err = eError::NoErr;

	// Grab the engine from the thread data
	LEngine* thisEngine = (LEngine*)data;

	// Run the game thread loop
	err |= thisEngine->RunFull();

	DEBUG_LOG("EngineThread Ending");
	return (int)err;
}

//===============================================================
int GameThreadStart(void* data)
{
	DEBUG_LOG("GameThread Starting");
	eError err = eError::NoErr;

	// Grab the engine from the thread data
	LEngine* thisEngine = (LEngine*)data;

	// Run the game thread loop
	err |= thisEngine->GameThreadLoop();

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
	err |= thisEngine->RenderThreadLoop();

	DEBUG_LOG("RenderThread Ending");
	return (int)err;
}