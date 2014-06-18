//! \file LGameBase.cpp
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Description
//! 
#include "LGameBase.h"

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
	m_UpdatingList.PreUpdate();

	return VOnPreUpdate();
}

//===============================================================
LError LGameBase::Update(ms elapsed)
{
	m_UpdatingList.Update(elapsed);

	return VOnUpdate(elapsed);
}

//===============================================================
LError LGameBase::PostUpdate()
{
	m_UpdatingList.PostUpdate();

	return VOnPostUpdate();
}

//===============================================================
LError LGameBase::Reset()
{
	return VOnReset();
}

//===============================================================
LError LGameBase::Destroy()
{
	return VOnDestroy();
}

