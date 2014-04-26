//! \file LEngine.h
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Header for LEngine.cpp
//!
#ifndef _LENGINE_H_
#define _LENGINE_H_

#include "types.h"
#include "SDLWindow.h"

// LEngine delegate class
class LEngine
{
public:

	// Constructor and destructor
	LEngine();
	~LEngine();

	// run ( will not return until finished running )
	eError run_full();

	// Other functions

	// Update the window
	eError UpdateWindow();

private:

	// main engine run cycle functions (managed by run_full)

	// Init the engine
	eError init();

	// run ( will not return until finished running )
	eError run();

		// Loads assets
		eError load();

		// calls the event loop	
		eError loop();

		// unloads the assets
		eError unload();

	// quit the engine
	eError quit();

	// Member variables
	SDLWindow m_MainWindow;

};

//! \brief start point for the game thread
int GameThreadStart(void* data);

//! \brief start point for the render thread
int RenderThreadStart(void* data);

#endif //_LENGINE_H_