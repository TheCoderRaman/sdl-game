//! \file GameOne.cpp
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Main game class, responsible for managing all game specific stuff
//!
#include "MyFirstGameObject.h"

#include "eError.h"
#include "debug.h"

eError MyFirstGameObject::Create( void )
{
	RUNTIME_LOG( "Creating Obj1..." );

	return eError::NoErr;
}

eError MyFirstGameObject::Initialise( void )
{ 
	RUNTIME_LOG( "Initialising Obj1..." );

	return eError::NoErr;
}

eError MyFirstGameObject::Update( ms elapsed )
{

	RUNTIME_LOG( "Updating obj1..." );

	return eError::NoErr;
}

eError MyFirstGameObject::Reset( void )
{ 
	RUNTIME_LOG( "Resetting obj1..." );

	return eError::NoErr;
}

eError MyFirstGameObject::Destroy( void )
{
	RUNTIME_LOG( "Destroying obj1..." );

	return eError::NoErr;
}