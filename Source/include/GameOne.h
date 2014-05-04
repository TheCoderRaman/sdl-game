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
	virtual eError Update(ms elapsed);
	virtual eError Reset();
	virtual eError Destroy();

private:

};


#endif //_GAMEONE_H_