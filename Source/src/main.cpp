//includes
#include "stdio.h"

#include "debug.h"
#include "error.h"

#include "LEngine.h"


// Main
int main( int argc, char* args[] )
{
    DEBUG_LOG("Program Starting...\n");

    // Create the engine
    LEngine myEngine = LEngine();

    eError err =  eError_noErr;

    err = myEngine.init();
    
    if( eError_noErr == err )
    	err = myEngine.run();

    if( eError_noErr == err )
    	err = myEngine.quit();
    
    DEBUG_LOG("Program Exiting with error %i \n",err);

    return err;    
}