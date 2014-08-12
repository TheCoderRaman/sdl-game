//! \file LUpdatingList.cpp
//!
//! \author Owain Davies
//! \date    May 2014
//!
//! Stub for LUpdatingList.cpp
//!

#include "LUpdatingList.h"
#include "LUpdatable.h"

#include "LError.h"
#include "debug.h"

//===============================================================
LUpdatingList::LUpdatingList( void )
{

}

//===============================================================
LUpdatingList::~LUpdatingList( void )
{

}

//===============================================================
LError LUpdatingList::Register(LUpdatable* pToRegister)
{
	// Ensure we're not Registering a null object
	DEBUG_ASSERT(pToRegister != nullptr);

	m_vecObjects.push_back(pToRegister);
	return LError::NoErr;
}

//===============================================================
LError LUpdatingList::UnRegister(LUpdatable* pToRegister)
{
	// Ensure we're not UnRegistering a null object
	DEBUG_ASSERT(pToRegister != nullptr);

	m_vecObjects.remove(pToRegister);
	return LError::NoErr;
}

//===============================================================
LError LUpdatingList::VOnPreUpdate()
{
	for( LUpdatable* pObj : m_vecObjects )
	{
		// Ensure we're not updating a null object
		DEBUG_ASSERT(pObj != nullptr);
		pObj->PreUpdate();
	}

	return LError::NoErr;
}

//===============================================================
LError LUpdatingList::VOnUpdate(ms frameTime)
{
	for (LUpdatable* pObj : m_vecObjects)
	{
		// Ensure we're not updating a null object
		DEBUG_ASSERT(pObj != nullptr);
		pObj->Update(frameTime);
	}

	return LError::NoErr;
}

//===============================================================
LError LUpdatingList::VOnPostUpdate()
{
	for (LUpdatable* pObj : m_vecObjects)
	{
		// Ensure we're not updating a null object
		DEBUG_ASSERT(pObj != nullptr);
		pObj->PostUpdate();
	}

	return LError::NoErr;
}


//===============================================================
LError LUpdatingList::VOnReset()
{
	for( LUpdatable* pObj : m_vecObjects )
	{
		// Ensure we're not updating a null object
		DEBUG_ASSERT( pObj != nullptr );
		pObj->Reset();
	}

	return LError::NoErr;
}
