//! \file GameOne.cpp
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Main game class, responsible for managing all game specific stuff
//!
#include "GameOne.h"

//========================================================
// LGameBase::GetGame
//========================================================
LGameBase* LGameBase::GetGame()
{
	static GameOne game;
	return &game;
}

//========================================================
// GameOne::
//========================================================
GameOne::GameOne()
{

}

//========================================================
// GameOne::
//========================================================
GameOne::~GameOne()
{
	
}

//========================================================
// GameOne::
//========================================================
eError GameOne::Create()
{
 	eError err = eError::noErr;
 	return err;
}

//========================================================
// GameOne::
//========================================================
eError GameOne::Initialise()
{
 	eError err = eError::noErr;
 	return err;
}

//========================================================
// GameOne::
//========================================================
eError GameOne::Update()
{
 	eError err = eError::noErr;
 	return err;
}

//========================================================
// GameOne::
//========================================================
eError GameOne::Reset()
{
 	eError err = eError::noErr;
 	return err;
}

//========================================================
// GameOne::
//========================================================
eError GameOne::Destroy()
{
 	eError err = eError::noErr;
 	return err;
}