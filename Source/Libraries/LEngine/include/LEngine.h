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

#include "LUpdateLoop.h"
#include "LInput.h"
#include "LRenderer.h"
#include "LGameBase.h"
#include "LEvents.h"

#include <atomic>

//! \brief type define for engine events
enum class EEngineEventType
{
	Pause,
	Num
};

//! \brief typpe define for the data in engine events
union UEngineEventData
{
	//! \brief data for pause events
	struct
	{
		int pause_level;
	} pause;
};

// These functions must be anonymous to be called by a starting thread

//! \brief start point for the engine thread
int EngineThreadStart(void* data);

//! \brief start point for the game thread
int GameThreadStart(void* data);

//! \brief start point for the render thread
int RenderThreadStart(void* data);

//! \brief LEngine delegate class
class LEngine
{
private:
	
	static LEngine* s_currentEngine;
	static LEngine& GetCurrentEngine();

public:

	//! \brief Constructor and destructor
	LEngine(LGameBase& game);
	~LEngine();

	//! \brief start the engine
	LError Start();

	//! \brief end the engine
	LError End();


	// Thread loop functions

	//! \brief the main engine thread loop
	LError EngineThreadLoop();

	//! \brief the main render thread loop
	LError RenderThreadLoop();

	//! \brief the main game thread loop
	LError GameThreadLoop();


	//! \brief get if the engine is quitting
	bool QuitHasBeenRequested();

	//! \brief request an engine quit
	void RequestQuit();

	//! \brief get the renderer
	static inline LRenderer2D&		GetRenderer();
	static inline LUpdateLoop&		GetEventLoop();
	static inline LInput&			GetInputManager();

private:

	// Cannot call the normal constructor
	LEngine();

	// main engine run cycle functions (managed by EngineThreadLoop)

	//! \brief Init the engine
	LError Init();

	//! \brief Loads assets
	LError Load();

	//! \brief calls the event loop	
	LError Loop();

		//! \brief Pre-Update
		LError PreUpdate();

		//! \brief update the engine
		LError Update(ms elapsed);

		//! \brief post-update
		LError PostUpdate();

	//! \brief unloads the assets
	LError Unload();

	//! \brief quit the engine
	LError Quit();
	
	// Various members for the Engine
private:

	//! \brief The main window
	SDLInterface::Window	m_MainWindow;

	//! \brief The Renderer
	LRenderer2D				m_Renderer;

	//! \brief The UpdateLoop
	LUpdateLoop				m_UpdateLoop;

	//! \brief The InputManager
	LInput					m_InputManager;

	//! \brief The engine event manager
	LEventManager<EEngineEventType, UEngineEventData> m_engineEventManager;

	//! \brief member to show that the engine is quitting
	std::atomic<bool>		m_bQuitting;

	//! \brief The game the engine will be using
	LGameBase&	m_myGame;
};

// Inline functions
inline LRenderer2D& LEngine::GetRenderer()
{
	return GetCurrentEngine().m_Renderer;
}

inline LUpdateLoop& LEngine::GetEventLoop()
{
	return GetCurrentEngine().m_UpdateLoop;
}

inline LInput& LEngine::GetInputManager()
{
	return GetCurrentEngine().m_InputManager;
}

#endif //_LENGINE_H_