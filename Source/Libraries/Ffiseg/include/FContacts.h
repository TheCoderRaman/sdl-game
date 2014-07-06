//! \file FContacts.h
//!
//! \author  Marc Di luzio
//! \date    June 2014
//!
//! Contact manager for Ffiseg
//!
#ifndef _FCONTACTS_H_
#define _FCONTACTS_H_

#include "FCommon.h"

Ffiseg_namespace_start

class FIContactable;

//! \brief Interface wrapper class for the physics system contact listener
class FContactListener
{
public:
	//! \brief  default ctor
	FContactListener() {}

	//! \brief Create the listener
	void Create();

	//! \brief Destroy the listener
	void Destroy();

	//! \brief default dtor
	~FContactListener() {}

	//! \brief Get the internal collision listener
	inline void* GetInternal();

private:

	//! \brief internal listener pointer
	void* m_internalListener;

};

//! \brief Contact info for any contact
struct FContactInfo
{
	FIContactable* conA;
	FIContactable* conB;
};

//! \brief sub class for any contactable
//! Children of this class are the only classes that should be added as user data to box2d bodies
class FIContactable
{
public:

	virtual void BeginContact(const FContactInfo& info) {}
	virtual void EndContact(const FContactInfo& info) {}
	virtual void PreSolveContact(const FContactInfo& info) {}
	virtual void PostSolveContact(const FContactInfo& info) {}
};

//========================================================
inline void* FContactListener::GetInternal()
{
	return m_internalListener;
}

Ffiseg_namespace_end

#endif //_FCONTACTS_H_