//! \file GameOne.h
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Header for Pong.cpp
//!
#ifndef _GAMEONE_H_
#define _GAMEONE_H_

#include "LGameBase.h"
#include "LUpdatable.h"
#include "LSprite.h"
#include "ScoreGUI.h"

#include "Banana.h"
#include "Paddle.h"

#include "types.h"

#include "LEvents.h"

#include "FWorld.h"
#include "FContacts.h"

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
class Pong
: public LGameBase
{
public:

	// Default ctor and dtor
	Pong();
	~Pong();

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
	Paddle m_paddleOne;
	Paddle m_paddleTwo;
	ScoreGUI m_score;

	int iCurrentScore;

	//! \brief The Game Event Manager
	TGameEventManager m_myEventManager;

	//! \brief the event handler for the main game class
	TGameEventManager::THandler m_myEventHandler;

	Ffiseg::FWorld				m_myWorld;
};


#endif //_GAMEONE_H_