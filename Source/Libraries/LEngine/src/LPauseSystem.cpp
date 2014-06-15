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
	: m_currentFlags( 0 )
	, m_nextFlags( 0 )
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
void LPauseSystem::AddNextFlag(int flag)
{
	m_nextFlags |= flag;
}

//===============================================================
void LPauseSystem::AddNextFlags(int flags)
{
	m_nextFlags |= flags;
}

//===============================================================
void LPauseSystem::RemoveNextFlags(int flags)
{
	m_nextFlags &= ~flags;
}

//===============================================================
bool LPauseSystem::GetCurrentFlag(int flag) const
{
	return m_currentFlags & flag;
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
