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

#include "LObjectManager.h"
#include "LRenderer.h"
#include "LSprite.h"

//! \brief LEngine delegate class
class LEngine
{
public:

	//! \brief Constructor and destructor
	LEngine();
	~LEngine();

	//! \brief run ( will not return until finished running )
	//! Includes the full cycle
	eError run_full();

	//! \brief run ( will not return until finished running )
	//! start to run the engine, useful for seperate threads
	eError run();

	// Other functions

	//! \brief the main render thread loop
	eError EngineThreadLoop();

	//! \brief the main render thread loop
	eError RenderThreadLoop();

	//! \brief the main game thread loop
	eError GameThreadLoop();

	//! \brief set the desired frame time
	eError SetDesiredFrameTime( ms frameTime );

	//! \brief set the window size
	eError SetWindowSize(int w, int h);

private:

	// main engine run cycle functions (managed by run_full)

	//! \brief Init the engine
	eError init();

		//! \brief Loads assets
		eError load();

		//! \brief calls the event loop	
		eError loop();

		//! \brief Pre-Update
		eError PreUpdate();

		//! \brief update the engine
		eError Update(ms elapsed);

		//! \brief post-update
		eError PostUpdate();

		//! \brief Render the engine
		eError Render();

		//! \brief unloads the assets
		eError unload();

	//! \brief quit the engine
	eError quit();
	
	// Various members for the Engine
private:

	//! \brief The window Width
	int m_windowWidth;

	//! \brief The window Height
	int m_windowHeight;

	//! \brief The main window
	SDLInterface::Window m_MainWindow;

	//! \brief The Renderer
	LRenderer2D m_Renderer;

	//! \brief the desired time for each frame
	ms m_msDesiredFrameTime;

	//! \brief The Object Manager
	LObjectManager	m_ObjectManager;

	//! \brief The Banana
	LSprite	m_banana;

	// The threads

	//! \brief the engine thread
	SDLInterface::Thread m_engineThread;

	//! \brief the game update thread
	SDLInterface::Thread m_gameUpdateThread;

	//! \brief the render thread
	SDLInterface::Thread m_renderThread;

};

// These functions must be anonymous to be called by a starting thread

//! \brief start point for the engine thread
int EngineThreadStart(void* data);

//! \brief start point for the game thread
int GameThreadStart(void* data);

//! \brief start point for the render thread
int RenderThreadStart(void* data);

#endif //_LENGINE_H_