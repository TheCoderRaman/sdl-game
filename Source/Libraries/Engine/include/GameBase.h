#ifndef _GAMEBASE_H_
#define _GAMEBASE_H_

#include "types.h"
#include "Object.h"

// Base class for the Game, to be overloaded by the game specific class
class GameBase
: public Object
{
public:

	// Constructor and destructor
	GameBase();
	~GameBase();

	// Inherited methods as defined in Object.h
	virtual eError Create();
	virtual eError Initialise();
	virtual eError Update();
	virtual eError Reset();
	virtual eError Destroy();

	// static method to be declared in base class
	static GameBase* GetGame();

protected:


private:

};

#endif //_GAMEBASE_H_
