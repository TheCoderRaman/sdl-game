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
#include "eError.h"

#define DebugTimerUpdateRate_Sec 5.0f

#define ms_30FPS 33
#define ms_60FPS 16

#define WINDOW_WIDTH			720 
#define WINDOW_HEIGHT			480

#define DESIRED_FRAMETIME_MS	ms_60FPS

//===============================================================
LEngine::LEngine(LGameBase& game)
: m_bQuitting				( false )
, m_myGame					( game )
{

}

//===============================================================
LEngine::~LEngine()
{

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
eError LEngine::Start()
{
	//Initialization flag
	SDLInterface::Error err = SDLInterface::Error::None;

	// initialise SDL
	if (!SDL_ERROR_HAS_TYPE_FATAL(err))
		err |= SDLInterface::Init();

	// create the sdl event loop
	if (!SDL_ERROR_HAS_TYPE_FATAL(err))
		err |= SDLInterface::EventLoop::Create();

	// the engine thread
	SDLInterface::Thread engineThread("LEngine", EngineThreadStart);

	// Spawn the engine thread
	if (!SDL_ERROR_HAS_TYPE_FATAL(err))
		err |= engineThread.Spawn(this);

	// Do the main SDL event loop
	// This won't return until requested
	if (!SDL_ERROR_HAS_TYPE_FATAL(err))
		err |= SDLInterface::EventLoop::DoLoop();

	// If the event loop has quit here without the engine requesting it we need to request one
	// This should only happen if the event loop has recieved a fatal error of some kind
	RequestQuit();

	// Wait for the engine thread
	if (!SDL_ERROR_HAS_TYPE_FATAL(err))
		err |= engineThread.Wait();

	return SDL_ERROR_HAS_TYPE_FATAL(err) ? eError::Type_Fatal : eError::NoErr;
}

//===============================================================
eError LEngine::EngineThreadLoop()
{
	//Initialization flag
	eError err = eError::NoErr;

	// Initialise the engine
	if (!ERROR_HAS_TYPE_FATAL(err))
		err |= Init();

	// Load up
	if (!ERROR_HAS_TYPE_FATAL(err))
		err |= Load();

	// do the full engine loop
	if (!ERROR_HAS_TYPE_FATAL(err))
		err |= Loop();

	// unload
	if (!ERROR_HAS_TYPE_FATAL(err))
		err |= Unload();

	// Quit the engine
	if (!ERROR_HAS_TYPE_FATAL(err))
		err |= Quit();

	// Request the quit for the SDLEventLoop
	// Note: by the point this is called ALL dependent code must have finished
	SDLInterface::EventLoop::EndLoop();

	return err;
}

//===============================================================
eError LEngine::Init()
{
	RUNTIME_LOG("Initialising...")

	// Create the window
	SDLInterface::Error sdlerr = m_MainWindow.Create(WINDOW_WIDTH, WINDOW_HEIGHT);

	eError err = SDL_ERROR_HAS_TYPE_FATAL(sdlerr) ? eError::Type_Fatal : eError::NoErr;

	// Create the renderer
	if (!ERROR_HAS_TYPE_FATAL(err))
		err |= m_Renderer.Create(m_MainWindow);

	// Create the objects
	if (!ERROR_HAS_TYPE_FATAL(err))
		err |= m_ObjectManager.Create();

	// create the event manager for the engine events
	if (!ERROR_HAS_TYPE_FATAL(err))
		err |= m_engineEventManager.Create();

    return err;
}

//===============================================================
eError LEngine::Quit()
{
	RUNTIME_LOG("Quiting...")

	eError err = eError::NoErr;

	// create the event manager for the engine events
	err |= m_engineEventManager.Destroy();

	// Destroy the renderer
	err |= m_Renderer.Destroy();

	SDLInterface::Error sdlerr = m_MainWindow.Destroy();

	err |= SDL_ERROR_HAS_TYPE_FATAL(sdlerr) ? eError::Type_Fatal : eError::NoErr;
	
    return err;
}

//===============================================================
eError LEngine::End()
{
	//Quit SDL subsystems
	SDLInterface::Error sdlerr = SDLInterface::Quit();

	return SDL_ERROR_HAS_TYPE_FATAL(sdlerr) ? eError::Type_Fatal : eError::NoErr;
}

//===============================================================
eError LEngine::Load()
{
	RUNTIME_LOG("Loading...")
    
	//Loading err flag
    eError err = eError::NoErr;

	// Set the game's renderer
	m_myGame.SetRenderer( &m_Renderer );
	// Set the game's object manager
	m_myGame.SetObjectManager( &m_ObjectManager );
	// Set the game's input manager
	m_myGame.SetInputManager( &m_InputManager );

	// Create the game
	err |= m_myGame.Create();

	// Initialise the objects
	if( !ERROR_HAS_TYPE_FATAL( err ) )
		err |= m_ObjectManager.Create();

	// Initialse the game
	if (!ERROR_HAS_TYPE_FATAL(err))
		err |= m_myGame.Initialise();

	// Initialise the objects
	if( !ERROR_HAS_TYPE_FATAL( err ) )
		err |= m_ObjectManager.Initialise();

    return err;
}

//===============================================================
eError LEngine::Loop()
{
	eError err = eError::NoErr;
	RUNTIME_LOG("Looping...");

	// Spawn both the threads
	SDLInterface::Thread gameThread("LEngine", GameThreadStart);
	SDLInterface::Thread renderThread("Render", RenderThreadStart);

	SDLInterface::Error sdlerr = gameThread.Spawn(this);

	if (!SDL_ERROR_HAS_TYPE_FATAL(sdlerr))
		sdlerr |= renderThread.Spawn(this);

	// pull the sdl error in
	err |= SDL_ERROR_HAS_TYPE_FATAL(sdlerr) ? eError::Type_Fatal : eError::NoErr;

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
	REMOVE_ERR(err, eError::QuitRequest);

	sdlerr = SDLInterface::Error::None;

	// Wait for all the threads to close off
	// Do this regardless of Error state
	sdlerr |= renderThread.Wait();
	sdlerr |= gameThread.Wait();

	// pull the sdl error in
	err |= SDL_ERROR_HAS_TYPE_FATAL(sdlerr) ? eError::Type_Fatal : eError::NoErr;

    return err;
}

//===============================================================
eError LEngine::Unload()
{
	eError err = eError::NoErr;

	// Destroy the objects
	if( !ERROR_HAS_TYPE_FATAL( err ) )
		err |= m_ObjectManager.Destroy();

	// Destroy the game
	if ( !ERROR_HAS_TYPE_FATAL( err ) )
		err |= m_myGame.Destroy();

	// Set the games renderer back to null
	m_myGame.SetRenderer(nullptr);

	return err;
}

//===============================================================
eError LEngine::PreUpdate( void )
{
	eError err = eError::NoErr;

	// Push the current frame's inputs to last frame's and clear this frame's key buffer
	// Poll the keyboard now for the current frame's inputs
	m_InputManager.StartKeyboardUpdate();

	err |= m_myGame.PreUpdate();

	return err;
}

//===============================================================
eError LEngine::Update(ms elapsed)
{
	eError err = eError::NoErr;

	// We need to decide when this happens
	err |=  m_ObjectManager.Update( elapsed );

	// Update the game
	err |= m_myGame.Update(elapsed);

	return err;
}

//===============================================================
eError LEngine::PostUpdate( void )
{
	eError err = eError::NoErr;

	// Reset the Engine level keyboard polling
	m_InputManager.EndKeyboardUpdate();

	err |= m_myGame.PostUpdate();

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
		SDLInterface::Thread::DelayUntil(frameTime + DESIRED_FRAMETIME_MS);
		
		// Update the engine window
		err |= m_Renderer.Render();

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

// Anonymous thread start functions

//===============================================================
int EngineThreadStart(void* data)
{
	DEBUG_LOG("EngineThread Starting");
	eError err = eError::NoErr;

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