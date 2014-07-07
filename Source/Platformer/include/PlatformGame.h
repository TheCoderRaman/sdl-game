//! \file PlatformGame.h
//!
//! \author  Marc Di luzio
//! \date    July 2014
//!
//! Header for PlatformGame.cpp
//!
#ifndef _PLATFORMGAME_H_
#define _PLATFORMGAME_H_

#include "LGameBase.h"

//! \brief an Example game, called "One"
class PlatformGame
	: public LGameBase
{
public:

	PlatformGame();
	~PlatformGame();

private:

	// Inherited methods as defined in LUpdatable.h
	virtual LError VOnCreate(void) override;
	virtual LError VOnPreUpdate(void) override;
	virtual LError VOnUpdate(ms elapsed) override;
	virtual LError VOnPostUpdate(void) override;
	virtual LError VOnReset(void) override;
	virtual LError VOnDestroy(void) override;

};

#endif //_PLATFORMGAME_H_