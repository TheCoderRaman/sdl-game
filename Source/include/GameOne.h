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

#include "Banana.h"

#include "types.h"

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

	Banana m_banana;
};


#endif //_GAMEONE_H_