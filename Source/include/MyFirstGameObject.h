//! \file GameOne.cpp
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Main game class, responsible for managing all game specific stuff
//!
#include "LObject.h"

#include "eError.h"

class MyFirstGameObject : public LObject
{
	virtual eError Create( void );

	virtual eError Initialise( void );

	virtual eError Update( ms elapsed );

	virtual eError Reset( void );

	virtual eError Destroy( void );
};