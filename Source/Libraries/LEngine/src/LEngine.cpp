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
	RUNTIME_LOG("Initialising...\n")

    //Initialization flag
    eError err = eError_noErr;

    err = SDLMain::Init();

    if ( eError_noErr == err )
    	myMainWindow.Create();

    return err;
}

//===============================================================
// LEngine::
//===============================================================
eError LEngine::run()
{
	eError err = eError_noErr;

	err = load();

	if ( eError_noErr == err )
		err = loop();

	if ( eError_noErr == err )
		err = unload();

	return err;
}

//===============================================================
// LEngine::
//===============================================================
eError LEngine::quit()
{
	RUNTIME_LOG("Quiting...\n")

	eError err = eError_noErr;

	err = myMainWindow.Destroy();

    //Quit SDL subsystems
    SDLMain::Quit();

    return err;
}

//===============================================================
// LEngine::
//===============================================================
eError LEngine::load()
{
	RUNTIME_LOG("Loading...\n")
    
	//Loading err flag
    eError err = eError_noErr;

    err = LGameBase::GetGame()->Create();

    if( eError_noErr == err )
        err = LGameBase::GetGame()->Initialise();

    return err;
}

//===============================================================
// LEngine::
//===============================================================
eError LEngine::loop()
{
	RUNTIME_LOG("Looping...\n")

	eError err = eError_noErr;

	//While application is running
    bool exit_request = false;

    while(  eError_noErr == err 
        &&  false == exit_request )
    {
        err = SDLEventLoop::DoLoop(exit_request);

        if ( eError_noErr == err )
            err = LGameBase::GetGame()->Update();

        if ( eError_noErr == err )
        	err = myMainWindow.Update();
    }

    return err;
}

//===============================================================
// LEngine::
//===============================================================
eError LEngine::unload()
{
	eError err = eError_noErr;

    err = LGameBase::GetGame()->Destroy();

	return err;
}