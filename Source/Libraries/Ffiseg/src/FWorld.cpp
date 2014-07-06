//! \file FWorld.cpp
//!
//! \author  Marc Di luzio
//! \date    June 2014
//!
//! Implementation for the b2World wrapper
//!
#include "FWorld.h"
#include "FInternal.h"
#include "Box2D/Box2D.h"

#include "FDebugDraw.h"

Ffiseg_namespace_start

//========================================================
FWorld::FWorld()
{

}

//========================================================
FWorld::~FWorld()
{

}

//========================================================
int FWorld::Create(Vector2f grav)
{
	m_myWorld = new b2World(FfVecToB2Vec(grav));

	FDebugDraw::Register(this);

	return 1;
}

//========================================================
int FWorld::Step(float timestep, int velocityIterations, int positionIterations)
{
	m_myWorld->Step(timestep, velocityIterations, positionIterations);

	return 1;
}

//========================================================
int FWorld::Destroy()
{
	FDebugDraw::UnRegister();

	delete m_myWorld;
	m_myWorld = nullptr;

	return 1;
}

//========================================================
void FWorld::SetContactListener(FContactListener& listener)
{
	void* internalListener = listener.GetInternal();
	m_myWorld->SetContactListener((b2ContactListener*)internalListener);
}

Ffiseg_namespace_end