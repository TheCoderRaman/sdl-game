//! \file LUpdateLoop.cpp
//!
//! \author Owain Davies
//! \date    May 2014
//!
//! Stub for LUpdateLoop.cpp
//!

#include "LUpdateLoop.h"
#include "LUpdatable.h"

#include "LError.h"
#include "debug.h"

LUpdateLoop::LUpdateLoop( void )
{
	// Ensure that this vector is reserved
	m_vecObjects.reserve( mk_iMaxObjects );

	// Setting all pointers to be null
	for( LUpdatable* pObj : m_vecObjects )
	{
		pObj = nullptr;
	}
}

LUpdateLoop::~LUpdateLoop( void )
{

}

LError LUpdateLoop::RegisterObject( LUpdatable* pObjectToRegister )
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

LError LUpdateLoop::Update( ms frameTime )
{
	for( LUpdatable* pObj : m_vecObjects )
	{
		if( pObj != nullptr )
		{
			pObj->Update( frameTime );
		}
	}

	return LError::NoErr;
}

LError LUpdateLoop::Reset( void )
{
	for( LUpdatable* pObj : m_vecObjects )
	{
		if( pObj != nullptr )
		{
			pObj->Reset();
		}
	}

	return LError::NoErr;
}
