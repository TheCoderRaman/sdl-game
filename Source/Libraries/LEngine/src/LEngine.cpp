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
		// give the SDLThread system the function queue
		err = SDLThread::SetMainThreadQueue(&m_mainThreadQueue);
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
	RUNTIME_LOG("Looping...")

	eError err = eError::noErr;

	// Spawn SDLEventloop thread
	SDLThread::Thread sdlLoopThread;
	sdlLoopThread.name = "SDLEventLoop";

	SDLThread::SpawnThread(sdlLoopThread, SDLLoopThreadStart, this);

	// Spawn Game thread
	SDLThread::Thread gameUpdateThread;
	gameUpdateThread.name = "LGameUpdate";

	SDLThread::SpawnThread(gameUpdateThread, GameThreadStart, this);

	// Spawn the render thread
	SDLThread::Thread renderThread;
	renderThread.name = "Render";

	SDLThread::SpawnThread(renderThread, RenderThreadStart, this);

	// Run the main thread queue
	err = m_mainThreadQueue.Run();

	// Main thread queue has quit out
	//TODO: Send some kind of message to the other threads that they need to quit

	// Wait for all the threads to close off
	int returnVal;
	SDLThread::WaitForThread(renderThread, &returnVal);

	SDLThread::WaitForThread(gameUpdateThread, &returnVal);

	SDLThread::WaitForThread(sdlLoopThread, &returnVal);


		// These functions bellow MUST now to be farmed off to other threads
		// Removing them for now to ensure no funny business
		/*
        err |= SDLEventLoop::DoLoop(exit_request);

        if ( eError::noErr == err )
            err |= LGameBase::GetGame()->Update();

        if ( eError::noErr == err )
        	err |= m_MainWindow.Update();
		*/

    return err;
}

//===============================================================
// LEngine::
//===============================================================
eError LEngine::unload()
{
	eError err = eError::noErr;

    err |= LGameBase::GetGame()->Destroy();

	return err;
}

//===============================================================
// LEngine::UpdateWindow
//===============================================================
eError LEngine::UpdateWindow()
{
	eError err = eError::noErr;

	err |= m_MainWindow.Update();

	return err;
}


//===============================================================
int SDLLoopThreadStart(void* data)
{
	DEBUG_LOG("SDLLoopThread Starting");

	SDLEventLoop::DoLoop();

	DEBUG_LOG("SDLLoopThread Ending");
	return 0;
}

//===============================================================
int GameThreadStart(void* data)
{
	DEBUG_LOG("GameThread Starting");
	eError err = eError::noErr;
	
	while (!ERROR_HAS_TYPE_FATAL(err)
		&& !ERROR_HAS(err, eError::quitRequest))
	{
		LGameBase::GetGame()->Update();

		// TODO: Better delay mechanism for update rate and such
		SDLTimer::GlobalDelay(10);
	}

	DEBUG_LOG("GameThread Ending");
	return 0;
}

//===============================================================
int RenderThreadStart(void* data)
{
	DEBUG_LOG("RenderThread Starting");
	eError err = eError::noErr;

	LEngine* thisEngine = (LEngine*)data;

	while (!ERROR_HAS_TYPE_FATAL(err)
		&& !ERROR_HAS(err, eError::quitRequest))
	{
		err = thisEngine->UpdateWindow();

		// TODO: Better delay mechanism for update rate and such
		SDLTimer::GlobalDelay(10);
	}

	DEBUG_LOG("RenderThread Ending");
	return 0;
}