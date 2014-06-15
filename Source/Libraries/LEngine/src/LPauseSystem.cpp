//! \file LPauseSystem.cpp
//!
//! \author  Marc Di luzio
//! \date    Jun 2014
//!
//! Implementation for the pause system
//!
#include "LPauseSystem.h"

//===============================================================
LPauseSystem::LPauseSystem()
{

}

//===============================================================
LPauseSystem::~LPauseSystem()
{

}

//===============================================================
int LPauseSystem::GetCurrentFlags() const
{
	return m_currentFlags;
}

//===============================================================
void LPauseSystem::SetNextFlags(int flags)
{
	m_nextFlags = flags;
}

//===============================================================
void LPauseSystem::FlushNextFlags()
{
	int flags = m_nextFlags;
	m_currentFlags = flags;
}
