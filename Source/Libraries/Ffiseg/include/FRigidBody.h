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

//! \brief Forward declare
class FWorld;

//! \brief Ffiseg rigid body class
class FRigidBody
{
public:

	//! \brief Default ctor and dtor
	FRigidBody();
	~FRigidBody();

	//! \brief Create the rigid body itself
	int Create(FWorld* world, const FBodyDef& def);

	//! \brief Create a fixture on the body
	int CreateFixture(const FFixtureDef& def);

	//! \brief Set the position
	void SetPos(Vector2f vec);
	void SetPosByRef(const Vector2f& vec);
	//! \brief Get the position
	Vector2f GetPos() const;

	//! \brief Get the rotation
	void SetRot(float rotation);
	void SetRotByRef(const float& rotation);
	//! \brief Get the rotation
	float GetRot() const;

	//! \brief Destroy the body
	int Destroy();

private:

	//! \brief the internal box2d body
	b2Body* m_myBody;

	//! \brief Physics world the body belongs too
	FWorld* m_myWorld;
};


Ffiseg_namespace_end

#endif // _FRIGIDBODY_H_