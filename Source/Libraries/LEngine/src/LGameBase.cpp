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
	LError err = LError::NoErr;
	return err;
}

//===============================================================
LError LGameBase::PreUpdate()
{
	LError err = LError::NoErr;
	return err;
}

//===============================================================
LError LGameBase::Update(ms elapsed)
{
	LError err = LError::NoErr;
	return err;
}

//===============================================================
LError LGameBase::PostUpdate()
{
	LError err = LError::NoErr;
	return err;
}

//===============================================================
LError LGameBase::Reset()
{
	LError err = LError::NoErr;
	return err;
}

//===============================================================
LError LGameBase::Destroy()
{
	LError err = LError::NoErr;
	return err;
}

