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
	eError toReturn = eError::NoErr;

	if( m_vecObjects.size() <= m_vecObjects.capacity() )
	{
		m_vecObjects.push_back( pObjectToRegister );
	}
	else
	{
		DEBUG_ASSERT( "Trying to add an object into the object manager when it is full" );
		toReturn = eError::Fatal;
	}

	return toReturn;
}

eError LObjectManager::Create( void )
{
	for( LObject* pObj : m_vecObjects )
	{
		if( pObj != nullptr )
		{
			pObj->Create();
		}
	}

	return eError::NoErr;
}

eError LObjectManager::Initialise( void )
{
	for( LObject* pObj : m_vecObjects )
	{
		if( pObj != nullptr )
		{
			pObj->Initialise();
		}
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

eError LObjectManager::Reset( void )
{
	for( LObject* pObj : m_vecObjects )
	{
		if( pObj != nullptr )
		{
			pObj->Reset();
		}
	}

	return eError::NoErr;
}

eError LObjectManager::Destroy( void )
{
	for( LObject* pObj : m_vecObjects )
	{
		if( pObj != nullptr )
		{
			pObj->Destroy();
		}
	}

	return eError::NoErr;
}

