//! \file FRigidBody.cpp
//!
//! \author  Marc Di luzio
//! \date    June 2014
//!
//! Implementation for the b3RigidBody wrapper
//!
#include "FRigidBody.h"
#include "FCommon.h"
#include "Box2D/Box2D.h"

Ffiseg_namespace_start

//========================================================
FRigidBody::FRigidBody()
{

}

//========================================================
FRigidBody::~FRigidBody()
{

}

//========================================================
int FRigidBody::Create(FWorld* world)
{
	return 1;
}

//========================================================
int FRigidBody::Destroy()
{
	return 1;
}


Ffiseg_namespace_end