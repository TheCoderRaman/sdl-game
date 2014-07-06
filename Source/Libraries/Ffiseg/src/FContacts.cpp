#include "FContacts.h"

#include "FInternal.h"
#include "Ffiseg.h"

Ffiseg_namespace_start

class FContactListener_internal 
	: public b2ContactListener
{
public:

	virtual void BeginContact(b2Contact* contact) override;

	virtual void EndContact(b2Contact* contact) override;

	virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override;

	virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override;
};

FContactListener::FContactListener()
	: m_internalListener( nullptr )
{
}

void FContactListener::Create()
{
	m_internalListener = new FContactListener_internal();
}

void FContactListener::Destroy()
{
	delete m_internalListener;
	m_internalListener = nullptr;
}

FContactListener::~FContactListener()
{

}

void FContactListener_internal::BeginContact(b2Contact* contact)
{

}

void FContactListener_internal::EndContact(b2Contact* contact)
{

}

void FContactListener_internal::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{

}

void FContactListener_internal::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{

}


Ffiseg_namespace_end