//! \file FRigidBody.h
//!
//! \author  Marc Di luzio
//! \date    June 2014
//!
//! Header for FRigidBody.cpp
//!
#ifndef _FRIGIDBODY_H_
#define _FRIGIDBODY_H_

#include "FCommon.h"

Ffiseg_namespace_start

class FWorld;

class FRigidBody
{
public:

	FRigidBody();
	~FRigidBody();

	int Create(FWorld* world, const FBodyDef& def);

	int CreateFixture(const FFixtureDef& def);

	int Destroy();

private:

	//! \brief the internal box2d body
	b2Body* m_myBody;

	FWorld* m_myWorld;
};


Ffiseg_namespace_end

#endif // _FRIGIDBODY_H_