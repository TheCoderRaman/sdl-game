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
	// Error tracking
	eError err = eError::noErr;

	// log the program start
	RUNTIME_LOG("Program Starting...");

    // Create the engine
    LEngine myEngine = LEngine();

	// Initialise the engine
	if ( !ERROR_HAS_TYPE_FATAL(err) )
		err |= myEngine.init();
    
	// Run the engine
	if ( !ERROR_HAS_TYPE_FATAL(err) )
    	err |= myEngine.run();

	// Quit the engine
	if ( !ERROR_HAS_TYPE_FATAL(err) )
    	err |= myEngine.quit();
    
	// LOG the program exit parameter
	RUNTIME_LOG("Program Exiting with eError %i", err);

	// Return an int cast of the error
    return (int)err;    
}