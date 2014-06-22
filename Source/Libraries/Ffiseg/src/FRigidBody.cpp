//! \file FRigidBody.cpp
//!
//! \author  Marc Di luzio
//! \date    June 2014
//!
//! Implementation for the b3RigidBody wrapper
//!
#include "FRigidBody.h"
#include "FInternal.h"
#include "Box2D/Box2D.h"

#include "FWorld.h"
#include "FShape.h"

class FShape;

Ffiseg_namespace_start

//========================================================
FRigidBody::FRigidBody()
: m_myWorld( nullptr )
, m_myBody( nullptr )
{

}

//========================================================
FRigidBody::~FRigidBody()
{

}

//========================================================
int FRigidBody::Create(FWorld* world, const FBodyDef& def)
{
	m_myWorld = world;

	b2BodyDef b2def = getb2BodyDef(def);

	m_myBody = m_myWorld->GetBaseWorldPtr()->CreateBody(&b2def);

	return 1;
}

//========================================================
int FRigidBody::CreateFixture(const FFixtureDef& def)
{
	b2FixtureDef b2def = getb2FixtureDef(def);

	switch (def.shape->m_type)
	{
	case FShape::Polygon:
		{
			// Convert our polygon to a b2 polygon
			b2PolygonShape poly = getb2PolygonShape(*dynamic_cast<const FPolygonShape* >(def.shape));
			b2def.shape = &poly;

			// Create the fixture
			m_myBody->CreateFixture(&b2def);
		}

		break;

	default:
		// Not implemented yet
		return 0;
		break;
	}

	return 1;
}

//========================================================
int FRigidBody::Destroy()
{
	if (m_myWorld && m_myWorld->GetBaseWorldPtr())
	{
		m_myWorld->GetBaseWorldPtr()->DestroyBody(m_myBody);
	}

	return 1;
}


Ffiseg_namespace_end