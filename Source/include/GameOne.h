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

class GameOne
: public LGameBase
{
public:

	GameOne();
	~GameOne();

	// Inherited methods as defined in LObject.h
	virtual eError Create();
	virtual eError Initialise();
	virtual eError Update();
	virtual eError Reset();
	virtual eError Destroy();

private:

};


#endif //_GAMEONE_H_