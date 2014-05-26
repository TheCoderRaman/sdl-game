//! \file LObjectManager.cpp
//!
//! \author Owain Davies
//! \date    May 2014
//!
//! Stub for LObjectManager.cpp
//!

#include "LObjectManager.h"
#include "LObject.h"

#include "LError.h"
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

LError LObjectManager::RegisterObject( LObject* pObjectToRegister )
{
	LError toReturn = LError::NoErr;

	if( m_vecObjects.size() <= m_vecObjects.capacity() )
	{
		m_vecObjects.push_back( pObjectToRegister );
	}
	else
	{
		DEBUG_ASSERT( "Trying to add an object into the object manager when it is full" );
		toReturn = LError::Fatal;
	}

	return toReturn;
}

LError LObjectManager::Create( void )
{
	for( LObject* pObj : m_vecObjects )
	{
		if( pObj != nullptr )
		{
			pObj->Create();
		}
	}

	return LError::NoErr;
}

LError LObjectManager::Initialise( void )
{
	for( LObject* pObj : m_vecObjects )
	{
		if( pObj != nullptr )
		{
			pObj->Initialise();
		}
	}

	return LError::NoErr;
}

LError LObjectManager::Update( ms frameTime )
{
	for( LObject* pObj : m_vecObjects )
	{
		if( pObj != nullptr )
		{
			pObj->Update( frameTime );
		}
	}

	return LError::NoErr;
}

LError LObjectManager::Reset( void )
{
	for( LObject* pObj : m_vecObjects )
	{
		if( pObj != nullptr )
		{
			pObj->Reset();
		}
	}

	return LError::NoErr;
}

LError LObjectManager::Destroy( void )
{
	for( LObject* pObj : m_vecObjects )
	{
		if( pObj != nullptr )
		{
			pObj->Destroy();
		}
	}

	return LError::NoErr;
}

