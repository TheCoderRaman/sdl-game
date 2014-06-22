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

namespace Ffiseg
{

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
	return 1;
}

//========================================================
int FWorld::Destroy()
{
	delete m_myWorld;
	m_myWorld = nullptr;

	return 1;
}

}