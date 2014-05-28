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
	return VOnPreUpdate();
}

//===============================================================
LError LGameBase::Update(ms elapsed)
{
	return VOnUpdate(elapsed);
}

//===============================================================
LError LGameBase::PostUpdate()
{
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

