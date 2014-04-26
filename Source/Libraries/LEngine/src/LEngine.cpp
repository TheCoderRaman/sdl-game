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
LEngine::LEngine()
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
	eError err = eError::noErr;

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
    eError err = eError::noErr;

	// initialise SDL
    err = SDLMain::Init();

	// create the sdl event loop
	if (!ERROR_HAS_TYPE_FATAL(err))
		err = SDLEventLoop::Create();

	// Create the window
	if (!ERROR_HAS_TYPE_FATAL(err))
		err = m_MainWindow.Create();

    return err;
}

//===============================================================
eError LEngine::run()
{
	eError err = eError::noErr;

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

	eError err = eError::noErr;

	// Destroy the main window
	err |= m_MainWindow.Destroy();

    //Quit SDL subsystems
	if (!ERROR_HAS_TYPE_FATAL(err))
		SDLMain::Quit();

    return err;
}

//===============================================================
eError LEngine::load()
{
	RUNTIME_LOG("Loading...")
    
	//Loading err flag
    eError err = eError::noErr;

	// Create the game
    err |= LGameBase::GetGame()->Create();

	// Initialse the game
	if (!ERROR_HAS_TYPE_FATAL(err))
        err |= LGameBase::GetGame()->Initialise();

    return err;
}

//===============================================================
eError LEngine::loop()
{
	eError err = eError::noErr;

	RUNTIME_LOG("Looping...")

	// Spawn Game thread
	SDLThread::Thread gameUpdateThread;
	gameUpdateThread.name = "Game";
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
eError LEngine::unload()
{
	eError err = eError::noErr;

	// Destroy the game
    err |= LGameBase::GetGame()->Destroy();

	return err;
}

//===============================================================
eError LEngine::Render()
{
	eError err = eError::noErr;

	//TODO: render the objects

	// Update the main window
	err |= m_MainWindow.Update();

	return err;
}

//===============================================================
eError LEngine::RenderThreadLoop()
{
	eError err = eError::noErr;

	while (!ERROR_HAS_TYPE_FATAL(err)
		&& !ERROR_HAS(err, eError::quitRequest))
	{
		// Update the engine window
		err |= Render();

		// TODO: Better delay mechanism for update rate and such
		SDLThread::Delay(10);

		// get if the SDLEventLoop has finished
		err |= SDLEventLoop::GetHasFinished();
	}

	return err;
}

//===============================================================
eError LEngine::GameThreadLoop()
{
	eError err = eError::noErr;

	// The main loop
	while (!ERROR_HAS_TYPE_FATAL(err)
		&& !ERROR_HAS(err, eError::quitRequest))
	{
		// Update the game
		err |= LGameBase::GetGame()->Update();

		// TODO: Better delay mechanism for update rate and such
		SDLThread::Delay(10);

		// get if the SDLEventLoop has finished
		err |= SDLEventLoop::GetHasFinished();
	}

	return err;
}

//===============================================================
int GameThreadStart(void* data)
{
	DEBUG_LOG("GameThread Starting");
	eError err = eError::noErr;

	// Grab the engine from the thread data
	LEngine* thisEngine = (LEngine*)data;

	// Run the game thread loop
	thisEngine->GameThreadLoop();

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

	// Run the render thread loop
	thisEngine->RenderThreadLoop();

	DEBUG_LOG("RenderThread Ending");
	return 0;
}