//! \file LUpdatable.cpp
//!
//! \author  Marc Di luzio
//! \date    May 2014
//!
//!
#include "LUpdatable.h"

//===============================================================
ObjectID LUpdatable::s_updatableID = 0;

//===============================================================
LUpdatable::LUpdatable()
: m_bIsActive ( false )
, m_ID ( s_updatableID++ )
{

}

//===============================================================
LUpdatable::~LUpdatable()
{
	
}

//===============================================================
LError LUpdatable::Update(ms elapsed)
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
LError LUpdatable::Reset()
{
	return VOnReset();
}

//===============================================================
LError LUpdatable::Activate()
{
	return VOnActivate();
}

//===============================================================
LError LUpdatable::Deactivate()
{
	return VOnDeactivate();
}

//===============================================================
LError LUpdatable::VOnUpdate(ms elapsed)
{
	return LError::NoErr;
}

//===============================================================
LError LUpdatable::VOnReset()
{
	return LError::NoErr;
}

//===============================================================
LError LUpdatable::VOnActivate()
{
	return LError::NoErr;
}

//===============================================================
LError LUpdatable::VOnDeactivate()
{
	return LError::NoErr;
}