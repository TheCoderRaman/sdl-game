//! \file PlatformGame.cpp
//!
//! \author  Marc Di luzio
//! \date    July 2014
//!
//! Platform Game class definitions
//!
#include "PlatformGame.h"

#include "LEngine.h"	//! for the engine itself
#include "debug.h"		//! for logging

#ifdef WINDOWS_BUILD // For freeing the console
	#include <Windows.h>
#endif

//========================================================
int main(int argc, char* args[])
{ 
	LError err = LError::NoErr;

	// log the program start
	RUNTIME_LOG("Platform Game booting up...");

#ifdef WINDOWS_BUILD
	// Removes the default VS output window
	FreeConsole();
#endif

	// Create the game
	PlatformGame theGame;

	// Create and run the engine
	LEngine myEngine(theGame);

	// Run the engine
	err |= myEngine.Start();

	// end the engine once it returns
	err |= myEngine.End();

	// LOG the program exit parameter
	RUNTIME_LOG("Platform game exiting with error value 0x%08X", err);
	// Assert here if we've had an error
	DEBUG_ASSERT(err == LError::NoErr);

	// Return -1 as a failure
	return LERROR_HAS_FATAL(err) ? -1 : 0;
}


//========================================================
PlatformGame::PlatformGame()
{

}

//========================================================
PlatformGame::~PlatformGame()
{

}

//========================================================
LError PlatformGame::VOnCreate()
{
	LError err = LError::NoErr;

	return err;
}

//========================================================
LError PlatformGame::VOnPreUpdate()
{
	LError err = LError::NoErr;

	return err;
}

//========================================================
LError PlatformGame::VOnUpdate(ms elapsed)
{
	LError err = LError::NoErr;

	return err;
}

//========================================================
LError PlatformGame::VOnPostUpdate()
{
	LError err = LError::NoErr;

	return err;
}

//========================================================
LError PlatformGame::VOnReset()
{
	LError err = LError::NoErr;

	return err;
}

//========================================================
LError PlatformGame::VOnDestroy()
{
	LError err = LError::NoErr;

	return err;
}