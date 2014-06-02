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
	: m_uCurrentStatus(LUpdateableStatus::Inactive)
	, m_uNextStatus(LUpdateableStatus::Active)
	, m_ID(s_updatableID++)
{

}

//===============================================================
LUpdatable::~LUpdatable()
{
	
}

//===============================================================
LError LUpdatable::Update(ms elapsed)
{
	ProgressStatus();

	// Update if we're active
	if (GetCurrentStatus() == LUpdateableStatus::Active)
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
	m_uCurrentStatus = LUpdateableStatus::Active;
	return VOnActivate();
}

//===============================================================
LError LUpdatable::Deactivate()
{
	m_uCurrentStatus = LUpdateableStatus::Inactive;
	return VOnDeactivate();
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

//===============================================================
void LUpdatable::ProgressStatus()
{
	if (m_uCurrentStatus != m_uNextStatus)
	{
		switch (m_uNextStatus)
		{
		case LUpdateableStatus::Active:
			Activate();
			break;
		case LUpdateableStatus::Inactive:
			Deactivate();
			break;
		}
	}
}
