#include "Engine.h"

#include "SDLMain.h"
#include "SDLEventLoop.h"

//===============================================================
// Engine::
//===============================================================
Engine::Engine()
{

}

//===============================================================
// Engine::
//===============================================================
Engine::~Engine()
{

}

//===============================================================
// Engine::
//===============================================================
eError Engine::init()
{
	DEBUG_LOG("Initialising...\n")

    //Initialization flag
    eError err = eError_noErr;

    err = SDLMain::Init();

    if ( eError_noErr == err )
    	myMainWindow.Create();

    return err;
}

//===============================================================
// Engine::
//===============================================================
eError Engine::run()
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
// Engine::
//===============================================================
eError Engine::quit()
{
	DEBUG_LOG("Quiting...\n")

	eError err = eError_noErr;

	err = myMainWindow.Destroy();

    //Quit SDL subsystems
    SDLMain::Quit();

    return err;
}

//===============================================================
// Engine::
//===============================================================
eError Engine::load()
{
	DEBUG_LOG("Loading...\n")
    
	//Loading err flag
    eError err = eError_noErr;

    // Do some sort of loading here

    return err;
}

//===============================================================
// Engine::
//===============================================================
eError Engine::loop()
{
	DEBUG_LOG("Looping...\n")

	eError err = eError_noErr;

	//While application is running
    bool exit_request = false;

    while(  eError_noErr == err 
        &&  false == exit_request )
    {
        err = SDLEventLoop::DoLoop(exit_request);

        if ( eError_noErr == err )
        	err = myMainWindow.Update();
    }

    return err;
}

//===============================================================
// Engine::
//===============================================================
eError Engine::unload()
{
	eError err = eError_noErr;

	// Some unloading of some sort

	return err;
}