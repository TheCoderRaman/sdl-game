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
#include "LObject.h"
#include "LSprite.h"

#include "MyFirstGameObject.h"

#include "types.h"

#include "LEvents.h"

enum class eGameEventType
{
	Event_One,
	Event_Two,
	Event_Three,
};

union uGameEventData
{
	struct
	{
		int x;
		int y;
	} one;

	struct 
	{
		float i;
		float y;
	} two;

	struct 
	{
		int array[4];
		float value;
	} three;
};

//! \brief an Example game, called "One"
class GameOne
: public LGameBase
{
public:

	// Default ctor and dtor
	GameOne();
	~GameOne();

	// Inherited methods as defined in LObject.h
	virtual eError Create();
	virtual eError Initialise();
	virtual eError PreUpdate();
	virtual eError Update(ms elapsed);
	virtual eError PostUpdate();
	virtual eError Reset();
	virtual eError Destroy();

private:

	MyFirstGameObject m_myFirstObject;

	//! \brief The Banana
	LSprite					m_banana;

	//! \brief The Game Event Manager
	LEventManager<eGameEventType, uGameEventData> m_EventManager;

	LEventHandler<eGameEventType,uGameEventData> m_eventHandler;
};


#endif //_GAMEONE_H_