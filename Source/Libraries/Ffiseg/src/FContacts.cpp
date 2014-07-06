//! \file FContacts.cpp
//!
//! \author  Marc Di luzio
//! \date    June 2014
//!
//! Contact manager for Ffiseg
//!
#include "FContacts.h"

#include "FInternal.h"
#include "Ffiseg.h"

Ffiseg_namespace_start

//========================================================
class FContactListener_internal 
	: public b2ContactListener
{
public:

	//! \brief Called when a contact begins
	virtual void BeginContact(b2Contact* contact) override;

	//! \brief Called when a contact ends
	virtual void EndContact(b2Contact* contact) override;

	//! \brief called before contacts have been solved
	//! Gives an oppertunity to filter out or negate the contact
	//! As well as a time to make calculations based on initial velocities
	virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override;

	//! \brief called after the contact has been solved
	//! Allows for find out the final result of a collision
	virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override;
};

//========================================================
void FContactListener::Create()
{
	m_internalListener = new FContactListener_internal();
}

//========================================================
void FContactListener::Destroy()
{
	delete m_internalListener;
	m_internalListener = nullptr;
}

//========================================================
void FContactListener_internal::BeginContact(b2Contact* contact)
{

}

//========================================================
void FContactListener_internal::EndContact(b2Contact* contact)
{

}

//========================================================
void FContactListener_internal::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{

}

//========================================================
void FContactListener_internal::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{

}


Ffiseg_namespace_end