//! \file LGameBase.cpp
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Description
//! 
#include "LGameBase.h"
#include "LEngine.h"
#include "LError.h"

//===============================================================
LGameBase::LGameBase()
{

}

//===============================================================
LGameBase::~LGameBase()
{

}

//===============================================================
LError LGameBase::Create()
{
	return VOnCreate();
}

//===============================================================
LError LGameBase::PreUpdate()
{
	if (!LEngine::GetIsPaused(EEnginePauseFlag::Game) )
	{
		m_UpdatingList.PreUpdate();

		return VOnPreUpdate();
	}
	else
	{
		return LError::NoErr;
	}
}

//===============================================================
LError LGameBase::Update(ms elapsed)
{
	if (!LEngine::GetIsPaused(EEnginePauseFlag::Game))
	{
		m_UpdatingList.Update(elapsed);

		return VOnUpdate(elapsed);
	}
	else
	{
		return LError::NoErr;
	}
}

//===============================================================
LError LGameBase::PostUpdate()
{
	if (!LEngine::GetIsPaused(EEnginePauseFlag::Game))
	{
		m_UpdatingList.PostUpdate();

		return VOnPostUpdate();
	}
	else
	{
		return LError::NoErr;
	}
}

//===============================================================
LError LGameBase::Reset()
{
	m_UpdatingList.Reset();

	return VOnReset();
}

//===============================================================
LError LGameBase::Destroy()
{
	return VOnDestroy();
}

