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

class FContactable;

//! \brief Interface wrapper class for the physics system contact listener
class FContactListener
{
public:

	//! \brief Create the listener
	void Create();

	//! \brief Destroy the listener
	void Destroy();

	//! \brief Get the internal collision listener
	inline void* GetInternal();

private:

	//! \brief internal listener pointer
	void* m_internalListener;

};

//========================================================
inline void* FContactListener::GetInternal()
{
	return m_internalListener;
}

//! \brief contact info for all contacts detected by this system
//! When passed this type, do not expect any memory stored at the 
//! pointer locations to be valid after the function call
struct FContactInfo
{
	FContactable* conA;
	FContactable* conB;
};

//! \brief Contactable class
//! children of this class are the only type of class that should ever 
//! be set as user data on any box2D body
class FContactable
{
public:

	//! brief internal type
	enum Type
	{
		RigidBody
	};

	//! \brief constructor must pass down the type
	FContactable(Type t) : m_type(t) {}

	//! \brief methods for callbacks from different stages of collision 
	virtual void BeginContact(const FContactInfo& info) {}
	virtual void EndContact(const FContactInfo& info) {}
	virtual void PreSolveContact(const FContactInfo& info) {}
	virtual void PostSolveContact(const FContactInfo& info) {}

	//! \brief Get the child type of this class
	template< typename TChildClass >
	inline TChildClass* TGetAsChildType();

	//! \brief get the Contactable type
	inline Type GetType() const
	{
		return m_type;
	}

private:

	//! \brief private base ctor to prevent usage
	FContactable();

	//! \brief internal type
	Type m_type;
};

//========================================================
template< typename TChildClass >
TChildClass* FContactable::TGetAsChildType()
{
	// Ugly cast, but needed
	return dynamic_cast<TChildClass*>(this);
}

Ffiseg_namespace_end

#endif //_FCONTACTS_H_