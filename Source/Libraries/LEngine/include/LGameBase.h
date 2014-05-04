//! \file LGameBase.h
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Header for LGameBase.cpp
//!
#ifndef _LGAMEBASE_H_
#define _LGAMEBASE_H_

#include "types.h"
#include "LObject.h"

//! \brief Base class for the Game, to be overloaded by the game specific class
class LGameBase
: public LObject
{
public:

	//! \brief Constructor
	LGameBase();
	//! \brief destructor
	~LGameBase();

	//! \brief Inherited methods as defined in LObject.h
	virtual eError Create();
	virtual eError Initialise();
	virtual eError Update(ms elapsed);
	virtual eError Reset();
	virtual eError Destroy();

	//! \brief static method to be declared in base class
	static LGameBase* GetGame();

protected:


private:

};

#endif //_LGAMEBASE_H_
