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

	// Add this as the userData. only EVER add FContactables as user data
	b2def.userData = (void*)this;

	m_myBody = m_myWorld->GetBaseWorldPtr()->CreateBody(&b2def);

	return 1;
}

//========================================================
int FRigidBody::CreateFixture(const FFixtureDef& def)
{
	b2FixtureDef b2def = getb2FixtureDef(def);

	// ENSURE SHAPE SIZES ARE POSETIVE

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

//========================================================
void FRigidBody::SetPos(Vector2f vec)
{
	SetPosByRef(vec);
}

//========================================================
void FRigidBody::SetPosByRef(const Vector2f& vec)
{
	m_myBody->SetTransform(FfVecToB2Vec(vec), 0.0f);
}

//========================================================
Vector2f FRigidBody::GetPos() const
{
	return B2VecToFfVec( m_myBody->GetPosition() );
}

//========================================================
void FRigidBody::SetRot(float rotation)
{
	SetRotByRef(rotation);
}

//========================================================
void FRigidBody::SetRotByRef(const float& rotation)
{
	m_myBody->SetTransform(m_myBody->GetPosition(), rotation);
}

//========================================================
float FRigidBody::GetRot() const
{
	return m_myBody->GetAngle();
}


Ffiseg_namespace_end