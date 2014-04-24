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

	// Init the engine
	eError init();

	// run ( will not return until finished running )
	eError run();

	// quit the engine
	eError quit();	

	// Update the window
	eError UpdateWindow();

private:

	// Loads assets
	eError load();

	// calls the event loop	
	eError loop();

	// unloads the assets
	eError unload();

	// Member variables
	SDLWindow m_MainWindow;

};

//! \brief start point for the game thread
int GameThreadStart(void* data);

//! \brief start point for the render thread
int RenderThreadStart(void* data);

#endif //_LENGINE_H_