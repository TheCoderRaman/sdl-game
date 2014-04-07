//includes
#include "stdio.h"

#include "types.h"
#include "Engine.h"

// Main
int main( int argc, char* args[] )
{
    DEBUG_LOG("Program Starting...\n");

    // Create the engine
    Engine myEngine = Engine();

    eError err;

    err = myEngine.init();
    
    if( eError_noErr == err )
    	err = myEngine.run();

    if( eError_noErr == err )
    	err = myEngine.quit();
    
    if( err != eError_noErr )
        DEBUG_LOG("Program finished with ERROR %i\n",err);

    DEBUG_LOG("Program Exiting Safely...\n");
    return err;    
}