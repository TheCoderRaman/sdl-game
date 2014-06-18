//! \file LEngine.cpp
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
#include "SDLError.h"

#include "LGameBase.h"

#include "debug.h"
#include "LError.h"

#define DebugTimerUpdateRate_Sec 5.0f

#define ms_30FPS 33
#define ms_60FPS 16

#define WINDOW_WIDTH			720 
#define WINDOW_HEIGHT			480

#define DESIRED_FRAMETIME_MS	ms_60FPS

//===============================================================
LEngine* LEngine::s_currentEngine = nullptr;

//===============================================================
LEngine& LEngine::GetCurrentEngine()
{
	return *s_currentEngine;
}

//===============================================================
LEngine::LEngine(LGameBase& game)
: m_bQuitting				( false )
, m_myGame					( game )
{

}

//===============================================================
LEngine::~LEngine()
{
	// stop the current engine pointing to this one
	s_currentEngine = nullptr;
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
void LEngine::WaitIfPaused(LEnginePauseSystem::TFlags system)
{
	while (GetIsPaused(system))
	{
		// Delay for 10ms and check again
		SDLInterface::Thread::Delay(10);
	}
}

//===============================================================
LError LEngine::Start()
{
	// Set the current engine to this one
	s_currentEngine = this;

	//Initialization flag
	SDLInterface::Error err = SDLInterface::Error::None;

	// initialise SDL
	if (!SDL_ERROR_HAS_FATAL(err))
		err |= SDLInterface::Init();

	// create the sdl event loop
	if (!SDL_ERROR_HAS_FATAL(err))
		err |= SDLInterface::EventLoop::Create();

	// the engine thread
	SDLInterface::Thread engineThread("LEngine", EngineThreadStart);

	// Spawn the engine thread
	if (!SDL_ERROR_HAS_FATAL(err))
		err |= engineThread.Spawn(this);

	// Do the main SDL event loop
	// This won't return until requested
	if (!SDL_ERROR_HAS_FATAL(err))
		err |= SDLInterface::EventLoop::DoLoop();

	// If the event loop has quit here without the engine requesting it we need to request one
	// This should only happen if the event loop has recieved a fatal error of some kind
	RequestQuit();

	// Wait for the engine thread
	if (!SDL_ERROR_HAS_FATAL(err))
		err |= engineThread.Wait();

	return SDL_ERROR_HAS_FATAL(err) ? LError::Fatal : LError::NoErr;
}

//===============================================================
LError LEngine::EngineThreadLoop()
{
	//Initialization flag
	LError err = LError::NoErr;

	// Initialise the engine
	if (!LERROR_HAS_FATAL(err))
		err |= Init();

	// Load up
	if (!LERROR_HAS_FATAL(err))
		err |= Load();

	// do the full engine loop
	if (!LERROR_HAS_FATAL(err))
		err |= Loop();

	// unload
	if (!LERROR_HAS_FATAL(err))
		err |= Unload();

	// Quit the engine
	if (!LERROR_HAS_FATAL(err))
		err |= Quit();

	// Request the quit for the SDLEventLoop
	// Note: by the point this is called ALL dependent code must have finished
	SDLInterface::EventLoop::EndLoop();

	return err;
}

//===============================================================
LError LEngine::Init()
{
	RUNTIME_LOG("Initialising...")

	// Create the window
	SDLInterface::Error sdlerr = m_MainWindow.Create(WINDOW_WIDTH, WINDOW_HEIGHT);

	LError err = SDL_ERROR_HAS_FATAL(sdlerr) ? LError::Fatal : LError::NoErr;

	// Create the renderer
	if (!LERROR_HAS_FATAL(err))
		err |= m_Renderer.Create(m_MainWindow);

	// create the event manager for the engine events
	if (!LERROR_HAS_FATAL(err))
		err |= m_engineEventManager.Create();

    return err;
}

//===============================================================
LError LEngine::Quit()
{
	RUNTIME_LOG("Quiting...")

	LError err = LError::NoErr;

	// create the event manager for the engine events
	err |= m_engineEventManager.Destroy();

	// Destroy the renderer
	err |= m_Renderer.Destroy();

	SDLInterface::Error sdlerr = m_MainWindow.Destroy();

	err |= SDL_ERROR_HAS_FATAL(sdlerr) ? LError::Fatal : LError::NoErr;
	
    return err;
}

//===============================================================
LError LEngine::End()
{
	//Quit SDL subsystems
	SDLInterface::Error sdlerr = SDLInterface::Quit();

	return SDL_ERROR_HAS_FATAL(sdlerr) ? LError::Fatal : LError::NoErr;
}

//===============================================================
LError LEngine::Load()
{
	RUNTIME_LOG("Loading...")
    
	//Loading err flag
    LError err = LError::NoErr;

	// Create the game
	err |= m_myGame.Create();

    return err;
}

//===============================================================
LError LEngine::Loop()
{
	LError err = LError::NoErr;
	RUNTIME_LOG("Looping...");

	// Spawn both the threads
	SDLInterface::Thread gameThread("LEngine", GameThreadStart);
	SDLInterface::Thread renderThread("Render", RenderThreadStart);

	SDLInterface::Error sdlerr = gameThread.Spawn(this);

	if (!SDL_ERROR_HAS_FATAL(sdlerr))
		sdlerr |= renderThread.Spawn(this);

	// pull the sdl error in
	err |= SDL_ERROR_HAS_FATAL(sdlerr) ? LError::Fatal : LError::NoErr;

	// Spin while not quitting
	while ( !QuitHasBeenRequested() 
		&& !SDLInterface::EventLoop::QuitHasBeenRequested() )
	{
		// Do something useful here?
		SDLInterface::Thread::Delay(10);
	}

	// Set that we're quiting now ( in the case that the event loop has quit )
	RequestQuit();

	// Remove any quit request error
	REMOVE_ERR(err, LError::QuitRequest);

	sdlerr = SDLInterface::Error::None;

	// Wait for all the threads to close off
	// Do this regardless of Error state
	sdlerr |= renderThread.Wait();
	sdlerr |= gameThread.Wait();

	// pull the sdl error in
	err |= SDL_ERROR_HAS_FATAL(sdlerr) ? LError::Fatal : LError::NoErr;

    return err;
}

//===============================================================
LError LEngine::Unload()
{
	LError err = LError::NoErr;

	// Destroy the game
	if ( !LERROR_HAS_FATAL( err ) )
		err |= m_myGame.Destroy();

	return err;
}

//===============================================================
LError LEngine::PreUpdate( void )
{
	LError err = LError::NoErr;

	m_pauseFlags.FlushNextFlags();

	// Push the current frame's inputs to last frame's and clear this frame's key buffer
	// Poll the keyboard now for the current frame's inputs
	m_InputManager.StartKeyboardUpdate();

	err |= m_myGame.PreUpdate();

	err |= m_UpdateLoop.PreUpdate();

	return err;
}

//===============================================================
LError LEngine::Update(ms elapsed)
{
	LError err = LError::NoErr;

	// We need to decide when this happens
	err |=  m_UpdateLoop.Update( elapsed );

	err |= m_myGame.Update(elapsed);

	return err;
}

//===============================================================
LError LEngine::PostUpdate( void )
{
	LError err = LError::NoErr;

	err |= m_UpdateLoop.PostUpdate();

	err |= m_myGame.PostUpdate();

	// Reset the Engine level keyboard polling
	m_InputManager.EndKeyboardUpdate();

	return err;
}

//===============================================================
LError LEngine::RenderThreadLoop()
{
	LError err = LError::NoErr;

	// the current frame time
	ms frameTime = SDLInterface::Timer::GetGlobalLifetime();

	// Timer for the logging
	SDLInterface::Timer logTimer;
	logTimer.Start();

	// frame counter
	unsigned int frameCounter = 0;


	while (!LERROR_HAS_FATAL(err)
		&& !LERROR_HAS(err, LError::QuitRequest))
	{
		// Wait if we're paused
		WaitIfPaused(EEnginePauseFlag::Render);

		// Delay until the end of the desired frame time
		SDLInterface::Thread::DelayUntil(frameTime + DESIRED_FRAMETIME_MS);
		
		// Update the engine window
		err |= m_Renderer.Render();

		// grab the current time
		frameTime = SDLInterface::Timer::GetGlobalLifetime();

		// get if the engine has finished
		if (QuitHasBeenRequested())
			err |= LError::QuitRequest;

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
	REMOVE_ERR(err, LError::QuitRequest);

	return err;
}

//===============================================================
LError LEngine::GameThreadLoop()
{
	LError err = LError::NoErr;

	// the current frame time
	ms frameTime = SDLInterface::Timer::GetGlobalLifetime();

	// Timer for the logging
	SDLInterface::Timer logTimer;
	logTimer.Start();

	// frame counter
	unsigned int frameCounter = 0;

	// The main loop
	while ( !LERROR_HAS_FATAL( err )
		&& !LERROR_HAS( err, LError::QuitRequest ) )
	{
		// Wait if we're paused
		WaitIfPaused(EEnginePauseFlag::Game);

		// Delay until the end of the desired frame time
		SDLInterface::Thread::DelayUntil(frameTime + DESIRED_FRAMETIME_MS);

		// Call any pre-update functionality
		err |= PreUpdate();

		// Call the main engine update method
		err |= Update(DESIRED_FRAMETIME_MS);

		// Call any post-update functionality
		err |= PostUpdate();

		// grab the current time
		frameTime = SDLInterface::Timer::GetGlobalLifetime();

		// get if the engine has finished
		if (QuitHasBeenRequested())
			err |= LError::QuitRequest;

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
	REMOVE_ERR(err, LError::QuitRequest);

	return err;
}

// Anonymous thread start functions

//===============================================================
int EngineThreadStart(void* data)
{
	DEBUG_LOG("EngineThread Starting");
	LError err = LError::NoErr;

	// Grab the engine from the thread data
	LEngine* thisEngine = (LEngine*)data;

	// Run the game thread loop
	err |= thisEngine->EngineThreadLoop();

	DEBUG_LOG("EngineThread Ending");
	return (int)err;
}

//===============================================================
int GameThreadStart(void* data)
{
	DEBUG_LOG("GameThread Starting");
	LError err = LError::NoErr;

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
	LError err = LError::NoErr;

	// Grab the engine from the thread data
	LEngine* thisEngine = (LEngine*)data;

	// Run the render thread loop
	err |= thisEngine->RenderThreadLoop();

	DEBUG_LOG("RenderThread Ending");
	return (int)err;
}