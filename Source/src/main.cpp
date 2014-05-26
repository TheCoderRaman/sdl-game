//! \file main.cpp
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! entry point for program
//! 

//includes
#include "debug.h"		//! for logging
#include "LError.h"		//! for error handling

#include "LEngine.h"	//! for the engine itself

#include "GameOne.h"	//! for GameOne

#ifdef WINDOWS_BUILD
	#include <Windows.h>
#endif

//========================================================
//! \brief main entry point for the program
int main( int argc, char* args[] )
{
	// log the program start
	RUNTIME_LOG("Program Starting...");

	LError err = LError::NoErr;
	
#ifdef WINDOWS_BUILD
	// Removes the default VS output window
	FreeConsole();
#endif

	// Create the game
	GameOne myGame;

    // Create and run the engine
	LEngine myEngine( myGame );
	
	// Run the engine
	err |= myEngine.Start();

	// end the engine once it returns
	err |= myEngine.End();
    
	// LOG the program exit parameter
	RUNTIME_LOG("Program Exiting with error value 0x%08X", err);

	// Assert here if we've had an error
	DEBUG_ASSERT(err == LError::NoErr);

	// Return -1 as a failure
    return LERROR_HAS_FATAL(err) ? -1 : 0 ;    
};