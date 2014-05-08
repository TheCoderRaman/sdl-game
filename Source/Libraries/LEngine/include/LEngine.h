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

#include <atomic>

//! \brief LEngine delegate class
class LEngine
{
public:

	//! \brief Constructor and destructor
	LEngine();
	~LEngine();

	//! \brief start the engine
	eError Start();

	//! \brief end the engine
	eError End();


	// Thread loop functions

	//! \brief the main engine thread loop
	eError EngineThreadLoop();

	//! \brief the main render thread loop
	eError RenderThreadLoop();

	//! \brief the main game thread loop
	eError GameThreadLoop();


	//! \brief get if the engine is quitting
	bool QuitHasBeenRequested();

	//! \brief request an engine quit
	void RequestQuit();

private:

	// main engine run cycle functions (managed by EngineThreadLoop)

	//! \brief Init the engine
	eError Init();

	//! \brief Loads assets
	eError Load();

	//! \brief calls the event loop	
	eError Loop();

		//! \brief Pre-Update
		eError PreUpdate();

		//! \brief update the engine
		eError Update(ms elapsed);

		//! \brief post-update
		eError PostUpdate();

	//! \brief unloads the assets
	eError Unload();

	//! \brief quit the engine
	eError Quit();
	
	// Various members for the Engine
private:

	//! \brief The main window
	SDLInterface::Window	m_MainWindow;

	//! \brief The Renderer
	LRenderer2D				m_Renderer;

	//! \brief The Object Manager
	LObjectManager			m_ObjectManager;

	//! \brief member to show that the engine is quitting
	std::atomic<bool>		m_bQuitting;

	//! \brief The Banana
	LSprite					m_banana;


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