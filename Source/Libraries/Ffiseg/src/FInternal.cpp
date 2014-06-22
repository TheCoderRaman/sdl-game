//! \file FInternal.cpp
//!
//! \author  Marc Di luzio
//! \date    June 2014
//!
//! Implementation for the internal Ffyseg functions
//!
#include "FInternal.h"

Ffiseg_namespace_start

b2BodyDef getb2BodyDef(const Ffiseg::FBodyDef& def)
{
	b2BodyDef b2def = b2BodyDef();

	b2def.active = def.active;
	b2def.allowSleep = def.allowSleep;
	b2def.angle = def.angle;
	b2def.angularDamping = def.angularDamping;
	b2def.angularVelocity = def.angularVelocity;
	b2def.awake = def.awake;
	b2def.bullet = def.bullet;
	b2def.fixedRotation = def.fixedRotation;
	b2def.gravityScale = def.gravityScale;
	b2def.linearDamping = def.linearDamping;
	b2def.linearVelocity = FfVecToB2Vec(def.linearVelocity);
	b2def.position = FfVecToB2Vec(def.position);
	b2def.type = (b2BodyType)def.type;
	b2def.userData = def.userData;
	return b2def;
}


b2Filter getb2Filter(const Ffiseg::FFilter& def)
{
	b2Filter b2fix = b2Filter();
	b2fix.categoryBits = def.categoryBits;
	b2fix.groupIndex = def.groupIndex;
	b2fix.maskBits = def.maskBits;

	return b2fix;
}

b2FixtureDef getb2FixtureDef(const Ffiseg::FFixtureDef& def)
{
	b2FixtureDef b2def = b2FixtureDef();

	b2def.density = def.density;
	b2def.filter = getb2Filter(def.filter);
	b2def.friction = def.friction;
	b2def.isSensor = def.isSensor;
	b2def.restitution = def.restitution;
	b2def.userData = def.userData;

	b2def.shape = nullptr;

	return b2def;
}


b2PolygonShape getb2PolygonShape(const Ffiseg::FPolygonShape& def)
{
	b2PolygonShape shape = b2PolygonShape();

	shape.SetAsBox(def.m_size.x, def.m_size.y, FfVecToB2Vec(def.m_centre), def.m_angle);

	return shape;
}

Ffiseg_namespace_end