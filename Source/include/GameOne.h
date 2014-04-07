#ifndef _GAMEONE_H_
#define _GAMEONE_H_

#include "GameBase.h"

class GameOne
: public GameBase
{
public:

	GameOne();
	~GameOne();

	// Inherited methods as defined in Object.h
	virtual eError Create();
	virtual eError Initialise();
	virtual eError Update();
	virtual eError Reset();
	virtual eError Destroy();

private:

};


#endif //_GAMEONE_H_