//! \file GameOne.h
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Header for GameOne.cpp
//!
#ifndef _GAMEONE_H_
#define _GAMEONE_H_

#include "LGameBase.h"
#include "LUpdatable.h"
#include "LSprite.h"

#include "Banana.h"

#include "types.h"

#include "LEvents.h"

enum class eGameEventType
{
	GameEvent_pause,
	GameEvent_Num,
};

union uGameEventData
{
	struct
	{
		int pause_level;
	} pause;
};

typedef LEventManager<eGameEventType, uGameEventData> TGameEventManager;

//! \brief an Example game, called "One"
class GameOne
: public LGameBase
{
public:

	// Default ctor and dtor
	GameOne();
	~GameOne();

private:

	// Inherited methods as defined in LUpdatable.h
	virtual LError VOnCreate(void) override;
	virtual LError VOnPreUpdate(void) override;
	virtual LError VOnUpdate(ms elapsed) override;
	virtual LError VOnPostUpdate(void) override;
	virtual LError VOnReset(void) override;
	virtual LError VOnDestroy(void) override;

	//! \brief internal event handler
	LError HandleEvent(const TGameEventManager::TEvent* event);

	//! \brief the Banana
	Banana m_banana;

	//! \brief The Game Event Manager
	TGameEventManager m_myEventManager;

	//! \brief the event handler for the main game class
	TGameEventManager::THandler m_myEventHandler;
};


#endif //_GAMEONE_H_