//! \file LObject.h
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Header for LObject.cpp
//!
#ifndef _LOBJECT_H_
#define _LOBJECT_H_

#include "types.h"
#include "LError.h"

//! \brief Base LObject interface type
//! Designed as a base type for all LEngine parts
//! Allows similarity of interface
class LObject 
{
public:

	LError Update(ms elapsed);

	LError Reset();

	LError Activate();

	LError Deactivate();

	inline bool IsActive();

private:

	virtual LError VOnUpdate(ms elapsed);

	virtual LError VOnReset();

	virtual LError VOnActivate();

	virtual LError VOnDeactivate();

	bool m_bIsActive;
};

//===============================================================
bool LObject::IsActive()
{
	return m_bIsActive;
}

#endif //_LOBJECT_H_