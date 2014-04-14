//! \file main.cpp
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Description
//! 

//includes
#include "stdio.h"

#include "debug.h"
#include "eError.h"

#include "LEngine.h"


// Main
int main( int argc, char* args[] )
{
	RUNTIME_LOG("Program Starting...\n");

    // Create the engine
    LEngine myEngine = LEngine();

    eError err =  eError::noErr;

    err |= myEngine.init();
    
    if( eError::noErr == err )
    	err |= myEngine.run();

    if( eError::noErr == err )
    	err |= myEngine.quit();
    
	RUNTIME_LOG("Program Exiting with eError %i \n", err);

    return (int)err;    
}