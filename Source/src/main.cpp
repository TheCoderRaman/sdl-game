//! \file main.cpp
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! entry point for program
//! 

//includes
#include "debug.h"		//! for logging
#include "eError.h"		//! for error handling

#include "LEngine.h"	//! for the engine itself

#if defined(WIN32) || defined(_WIN32)
	#include <Windows.h>
#endif

//========================================================
//! \brief main entry point for the program
int main( int argc, char* args[] )
{
	// log the program start
	RUNTIME_LOG("Program Starting...");
	
#if defined(WIN32) || defined(_WIN32)
	// Removes the default VS output window
	FreeConsole();
#endif

    // Create and run the engine
    LEngine myEngine = LEngine();
	eError err = myEngine.run_full();
    
	// LOG the program exit parameter
	RUNTIME_LOG("Program Exiting with error value %i", err);

	// Assert here if we've had an error
	DEBUG_ASSERT(err == eError::NoErr);

	// Return -1 as a failure
    return ERROR_HAS_TYPE_FATAL(err) ? -1 : 0 ;    
};