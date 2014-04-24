//! \file SDLEventLoop.cpp
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

//===============================================================
// LEngine::
//===============================================================
LEngine::LEngine()
{

}

//===============================================================
// LEngine::
//===============================================================
LEngine::~LEngine()
{

}

//===============================================================
// LEngine::
//===============================================================
eError LEngine::init()
{
	RUNTIME_LOG("Initialising...")

    //Initialization flag
    eError err = eError::noErr;

    err = SDLMain::Init();

	if (!ERROR_HAS_TYPE_FATAL(err))
	{
		err = m_MainWindow.Create();
	}

	if (!ERROR_HAS_TYPE_FATAL(err))
	{
		// create the sdl event loop
		err = SDLEventLoop::Create();
	}

    return err;
}

//===============================================================
// LEngine::
//===============================================================
eError LEngine::run()
{
	eError err = eError::noErr;

	err |= load();

	if ( eError::noErr == err )
		err |= loop();

	if ( eError::noErr == err )
		err |= unload();

	return err;
}

//===============================================================
// LEngine::
//===============================================================
eError LEngine::quit()
{
	RUNTIME_LOG("Quiting...")

	eError err = eError::noErr;

	err |= m_MainWindow.Destroy();

    //Quit SDL subsystems
    SDLMain::Quit();

    return err;
}

//===============================================================
// LEngine::
//===============================================================
eError LEngine::load()
{
	RUNTIME_LOG("Loading...")
    
	//Loading err flag
    eError err = eError::noErr;

    err |= LGameBase::GetGame()->Create();

    if( eError::noErr == err )
        err |= LGameBase::GetGame()->Initialise();

    return err;
}

//===============================================================
// LEngine::
//===============================================================
eError LEngine::loop()
{
	eError err = eError::noErr;

	RUNTIME_LOG("Looping...")

	// Spawn Game thread
	SDLThread::Thread gameUpdateThread;
	gameUpdateThread.name = "LGameUpdate";
	SDLThread::SpawnThread(gameUpdateThread, GameThreadStart, this);

	// Spawn the render thread
	SDLThread::Thread renderThread;
	renderThread.name = "Render";
	SDLThread::SpawnThread(renderThread, RenderThreadStart, this);

	// Do the main SDL event loop
	err = SDLEventLoop::DoLoop();

	// Wait for all the threads to close off
	int returnVal;
	SDLThread::WaitForThread(renderThread, &returnVal);
	SDLThread::WaitForThread(gameUpdateThread, &returnVal);

	//TODO: Handle these return vals

    return err;
}

//===============================================================
// LEngine::
//===============================================================
eError LEngine::unload()
{
	eError err = eError::noErr;

	// Destroy the game
    err |= LGameBase::GetGame()->Destroy();

	return err;
}

//===============================================================
// LEngine::UpdateWindow
//===============================================================
eError LEngine::UpdateWindow()
{
	eError err = eError::noErr;

	// Update the main window
	err |= m_MainWindow.Update();

	return err;
}

//===============================================================
int GameThreadStart(void* data)
{
	DEBUG_LOG("GameThread Starting");
	eError err = eError::noErr;
	
	// The main loop
	while (!ERROR_HAS_TYPE_FATAL(err)
		&& !ERROR_HAS(err, eError::quitRequest))
	{
		// Update the game
		err |= LGameBase::GetGame()->Update();

		// TODO: Better delay mechanism for update rate and such
		SDLTimer::GlobalDelay(10);

		// get if the SDLEventLoop has finished
		err |= SDLEventLoop::GetHasFinished();
	}

	DEBUG_LOG("GameThread Ending");
	return 0;
}

//===============================================================
int RenderThreadStart(void* data)
{
	DEBUG_LOG("RenderThread Starting");
	eError err = eError::noErr;

	// Grab the engine from the thread data
	LEngine* thisEngine = (LEngine*)data;

	while (!ERROR_HAS_TYPE_FATAL(err)
		&& !ERROR_HAS(err, eError::quitRequest))
	{
		// Update the engine window
		err |= thisEngine->UpdateWindow();

		// TODO: Better delay mechanism for update rate and such
		SDLTimer::GlobalDelay(10);

		// get if the SDLEventLoop has finished
		err |= SDLEventLoop::GetHasFinished();
	}

	DEBUG_LOG("RenderThread Ending");
	return 0;
}