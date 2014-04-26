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
	// log the program start
	RUNTIME_LOG("Program Starting...");

    // Create and run the engine
    LEngine myEngine = LEngine();
	eError err = myEngine.run_full();
    
	// LOG the program exit parameter
	RUNTIME_LOG("Program Exiting with error value %i", err);

	// Return -1 as a failure
    return ERROR_HAS_TYPE_FATAL(err) ? -1 : 0;    
}