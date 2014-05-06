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
#include "debug.h"

LObjectManager::LObjectManager( void )
{
	// Ensure that this vector is reserved
	m_vecObjects.reserve( mk_iMaxObjects );

	// Setting all pointers to be null
	for( LObject* pObj : m_vecObjects )
	{
		pObj = nullptr;
	}
}

LObjectManager::~LObjectManager( void )
{

}

eError LObjectManager::RegisterObject( LObject* pObjectToRegister )
{
	if( m_vecObjects.size() <= m_vecObjects.capacity() )
	{
		m_vecObjects.push_back( pObjectToRegister );
	}
	else
	{
		DEBUG_ASSERT( "Trying to add an object into the object manager when it is full" );
	}


	return eError::NoErr;
}

eError LObjectManager::Update( ms frameTime )
{
	for( LObject* pObj : m_vecObjects )
	{
		if( pObj != nullptr )
		{
			pObj->Update( frameTime );
		}
	}
	
	return eError::NoErr;
}