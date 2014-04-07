//includes
#include "stdio.h"

#include "types.h"
#include "SDLWindow.h"
#include "SDLEventLoop.h"
#include "SDLMain.h"

// Functions
eError init();
eError load();
eError loop();
eError close();

// Global variables
SDLWindow gMainWindow = SDLWindow();

// Main
int main( int argc, char* args[] )
{
    DEBUG_LOG("Program Starting...\n");

    eError err;

    err = init();

    if( err == eError_noErr )
    	err = load();

    if( err == eError_noErr )
    	err = loop();

    if( err == eError_noErr )
    	err = close();
    
    if( err != eError_noErr )
        DEBUG_LOG("Program finished with ERROR %i\n",err);

    DEBUG_LOG("Program Finished...\n");
    return err;    
}

// Function Definitions
eError init() 
{
	DEBUG_LOG("Initialising...\n")

    //Initialization flag
    eError err = eError_noErr;

    err = SDLMain::Init();

    if ( err == eError_noErr )
    	gMainWindow.Create();

    return err;
}

eError load()
{
	DEBUG_LOG("Loading...\n")
    
	//Loading err flag
    eError err = eError_noErr;

    return err;
}

eError loop()
{
	DEBUG_LOG("Looping...\n")

	eError err = eError_noErr;

	//While application is running
    bool exit_request = false;

    while( err == eError_noErr && !exit_request)
    {
        err = SDLEventLoop::DoLoop(exit_request);

        if ( err == eError_noErr )
        	err = gMainWindow.Update();
    }

    return err;
}

eError close()
{
	DEBUG_LOG("Closing...\n")

	eError err = eError_noErr;

	err = gMainWindow.Destroy();

    //Quit SDL subsystems
    SDLMain::Quit();

    return err;
}