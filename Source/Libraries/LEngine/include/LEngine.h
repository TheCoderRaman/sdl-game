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
#include "SDLThread.h"

//! \brief LEngine delegate class
class LEngine
{
public:

	//! \brief Constructor and destructor
	LEngine();
	~LEngine();

	//! \brief run ( will not return until finished running )
	eError run_full();

	// Other functions

	//! \brief the main render thread loop
	eError RenderThreadLoop();

	//! \brief the main game thread loop
	eError GameThreadLoop();

private:

	// main engine run cycle functions (managed by run_full)

	//! \brief Init the engine
	eError init();

	//! \brief run ( will not return until finished running )
	eError run();

		//! \brief Loads assets
		eError load();

		//! \brief calls the event loop	
		eError loop();

		//! \brief Update the window
		eError Render();

		//! \brief unloads the assets
		eError unload();

	//! \brief quit the engine
	eError quit();

	//! \brief Member variables
	SDLWindow m_MainWindow;

	//! \brief the game update thread
	SDLThread::Thread m_gameUpdateThread;

	//! \brief the render thread
	SDLThread::Thread m_renderThread;

};

//! \brief start point for the game thread
int GameThreadStart(void* data);

//! \brief start point for the render thread
int RenderThreadStart(void* data);

#endif //_LENGINE_H_