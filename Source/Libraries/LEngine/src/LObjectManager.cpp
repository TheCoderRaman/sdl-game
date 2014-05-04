//! \file LObjectManager.cpp
//!
//! \author Owain Davies
//! \date    May 2014
//!
//! Stub for LObjectManager.cpp
//!

#include "LObjectManager.h"
#include "LObject.h"

#include "eError.h"

LObjectManager::LObjectManager( void )
{

}

LObjectManager::~LObjectManager( void )
{

}

eError LObjectManager::RegisterObject( LObject* pObjectToRegister )
{
	return eError::NoErr;
}

eError LObjectManager::Update( ms frameTime )
{
	return eError::NoErr;
}