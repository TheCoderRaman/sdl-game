//! \file GameOne.cpp
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Main game class, responsible for managing all game specific stuff
//!
#include "GameOne.h"

#include "eError.h"

//========================================================
LGameBase* LGameBase::GetGame()
{
	// Lazy initialisation, 
	static GameOne game;
	return &game;
}

//========================================================
GameOne::GameOne()
{
	// Note, game is lazily initialised, so do nothing non POD here
}

//========================================================
GameOne::~GameOne()
{
	
}

//========================================================
eError GameOne::Create()
{
 	eError err = eError::NoErr;
 	return err;
}

//========================================================
eError GameOne::Initialise()
{
 	eError err = eError::NoErr;
 	return err;
}

//========================================================
eError GameOne::Update()
{
 	eError err = eError::NoErr;
 	return err;
}

//========================================================
eError GameOne::Reset()
{
 	eError err = eError::NoErr;
 	return err;
}

//========================================================
eError GameOne::Destroy()
{
 	eError err = eError::NoErr;
 	return err;
}