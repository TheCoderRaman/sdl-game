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

//===============================================================
LUpdateLoop::LUpdateLoop( void )
{

}

//===============================================================
LUpdateLoop::~LUpdateLoop( void )
{

}

//===============================================================
LError LUpdateLoop::Register(LUpdatable* pToRegister)
{
	// Ensure we're not Registering a null object
	DEBUG_ASSERT(pToRegister != nullptr);

	m_vecObjects.push_back(pToRegister);
	return LError::NoErr;
}

//===============================================================
LError LUpdateLoop::UnRegister(LUpdatable* pToRegister)
{
	// Ensure we're not UnRegistering a null object
	DEBUG_ASSERT(pToRegister != nullptr);

	m_vecObjects.remove(pToRegister);
	return LError::NoErr;
}

//===============================================================
LError LUpdateLoop::VOnUpdate(ms frameTime)
{
	for( LUpdatable* pObj : m_vecObjects )
	{
		// Ensure we're not updating a null object
		DEBUG_ASSERT(pObj != nullptr);
		pObj->Update( frameTime );
	}

	return LError::NoErr;
}
