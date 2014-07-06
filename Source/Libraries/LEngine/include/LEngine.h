//! \file LEngine.h
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! LEngine
//! A Simple SDL and Box2D based multithreaded game engine.
//! Designed and made as an experiment in game engine design, and maybe
//! To end up being used for some cool game in the future!
//!
#ifndef _LENGINE_H_
#define _LENGINE_H_

#include "types.h"

#include "SDLWindow.h"
#include "SDLThread.h"
#include "SDLAudio.h"

#include "LUpdatingList.h"
#include "LInput.h"
#include "LRenderer.h"
#include "LGameBase.h"
#include "LEvents.h"
#include "LAudio.h"
#include "LPauseSystem.h"

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

//! Enum for pause flags
// Not strongly typed as it's just a flag
enum EEnginePauseFlag
{
	Game = 0x0001,
	Render = 0x0002,
	Physics = 0x0004,
	Audio = 0x0008,
	Controls = 0x0010,

	Global = 0xFFFF
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
	
	//! \brief pointer to the current LEngine
	static LEngine* s_currentEngine;

	//! \brief accessor for the current LEngine
	static LEngine& GetCurrentEngine();

public:

	//! \brief typedef the templated pause system
	typedef LPauseSystem<EEnginePauseFlag> LEnginePauseSystem;

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

	//! \brief Pause or un pause a specific part of the engine
	static inline bool GetIsPaused(LEnginePauseSystem::TFlags system);

	//! \brief Pause or un pause a specific part of the engine
	static inline void PauseSubSystem(LEnginePauseSystem::TFlags system, bool pause);

	//! \brief get if the engine is quitting
	bool QuitHasBeenRequested();

	//! \brief request an engine quit
	void RequestQuit();

	//! \brief get the renderer
	static inline LRenderer2D&		GetRenderer();
	static inline LUpdatingList&	GetUpdatingList();
	static inline LInput&			GetInputManager();
	static inline LAudio&			GetAudioManager();

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

	//! Wait until a particular subsystem is unpaused
	void WaitIfPaused(LEnginePauseSystem::TFlags system);

	//! \brief The main window
	SDLInterface::Window	m_MainWindow;

	//! \brief The audio manager
	LAudio					m_AudioManager;

	//! \brief The Renderer
	LRenderer2D				m_Renderer;

	//! \brief The UpdatingList
	LUpdatingList			m_UpdatingList;

	//! \brief The InputManager
	LInput					m_InputManager;

	//! \brief The engine event manager
	LEventManager<EEngineEventType, UEngineEventData> m_engineEventManager;

	//! \brief member to show that the engine is quitting
	std::atomic<bool>		m_bQuitting;

	//! \brief The game the engine will be using
	LGameBase&				m_myGame;

	//! Engine pause flags
	LEnginePauseSystem		m_pauseFlags;
};

//===============================================================
// Inline functions

//===============================================================
inline LRenderer2D& LEngine::GetRenderer()
{
	return GetCurrentEngine().m_Renderer;
}

//===============================================================
inline LUpdatingList& LEngine::GetUpdatingList()
{
	return GetCurrentEngine().m_UpdatingList;
}

//===============================================================
inline LInput& LEngine::GetInputManager()
{
	return GetCurrentEngine().m_InputManager;
}

//===============================================================
inline LAudio& LEngine::GetAudioManager()
{
	return GetCurrentEngine().m_AudioManager;
}

//===============================================================
inline void LEngine::PauseSubSystem(LEnginePauseSystem::TFlags system, bool pause)
{
	if (pause)
		GetCurrentEngine().m_pauseFlags.AddNextFlag(system);
	else
		GetCurrentEngine().m_pauseFlags.RemoveNextFlags(system);
}

//===============================================================
inline bool LEngine::GetIsPaused(LEnginePauseSystem::TFlags system)
{
	return GetCurrentEngine().m_pauseFlags.GetCurrentFlag(system);
}

#endif //_LENGINE_H_