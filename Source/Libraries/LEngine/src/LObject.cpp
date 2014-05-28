//! \file LObject.cpp
//!
//! \author  Marc Di luzio
//! \date    May 2014
//!
//!
#include "LObject.h"

//===============================================================
ObjectID LObject::s_currentObjectID = 0;

//===============================================================
LObject::LObject()
: m_bIsActive ( false )
, m_ID ( s_currentObjectID++ )
{

}

//===============================================================
LObject::~LObject()
{
	
}

//===============================================================
LError LObject::Update(ms elapsed)
{
	// Update if we're active
	if (IsActive())
	{
		return VOnUpdate(elapsed);
	}
	else
	{
		return LError::NoErr;
	}
}

//===============================================================
LError LObject::Reset()
{
	return VOnReset();
}

//===============================================================
LError LObject::Activate()
{
	return VOnActivate();
}

//===============================================================
LError LObject::Deactivate()
{
	return VOnDeactivate();
}

//===============================================================
LError LObject::VOnUpdate(ms elapsed)
{
	return LError::NoErr;
}

//===============================================================
LError LObject::VOnReset()
{
	return LError::NoErr;
}

//===============================================================
LError LObject::VOnActivate()
{
	return LError::NoErr;
}

//===============================================================
LError LObject::VOnDeactivate()
{
	return LError::NoErr;
}