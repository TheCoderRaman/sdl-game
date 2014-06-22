//! \file FCommon.h
//!
//! \author  Marc Di luzio
//! \date    June 2014
//!
//! Common includes and declarations for the physics system
//!
#ifndef _FCOMMON_H_
#define _FCOMMON_H_

//! Pull in the common math
#include "math_types.h"

// Forward declares of the box2D types
class b2Body;
class b2Joint;
class b2Fixture;
class b2World;

#define FfVecToB2Vec(vec) b2Vec2(vec.x, vec.y)

//! \brief Ffiseg namespace
namespace Ffiseg
{
	//! \brief Immitation enum for b2BodyType
	enum FBodyType
	{
		Static = 0,
		Kinematic,
		Dynamic
	};

	//! \brief Immitation struct for b2BodyDef
	//! \note all comments prepended with a - are taken from Box2D
	struct FBodyDef
	{
		//! - This constructor sets the body definition default values.
		FBodyDef()
		{
			userData = nullptr;
			position = { 0.0f, 0.0f };
			angle = 0.0f;
			linearVelocity = { 0.0f, 0.0f };
			angularVelocity = 0.0f;
			linearDamping = 0.0f;
			angularDamping = 0.0f;
			allowSleep = true;
			awake = true;
			fixedRotation = false;
			bullet = false;
			type = Static;
			active = true;
			gravityScale = 1.0f;
		}

		//! - The body type: static, kinematic, or dynamic.
		//! - Note: if a dynamic body would have zero mass, the mass is set to one.
		FBodyType type;

		//! - The world position of the body. Avoid creating bodies at the origin
		//! - since this can lead to many overlapping shapes.
		Vector2f position;

		//! - The world angle of the body in radians.
		float angle;

		//! - The linear velocity of the body's origin in world co-ordinates.
		Vector2f linearVelocity;

		//! - The angular velocity of the body.
		float angularVelocity;

		//! - Linear damping is use to reduce the linear velocity. The damping parameter
		//! - can be larger than 1.0f but the damping effect becomes sensitive to the
		//! - time step when the damping parameter is large.
		float linearDamping;

		//! - Angular damping is use to reduce the angular velocity. The damping parameter
		//! - can be larger than 1.0f but the damping effect becomes sensitive to the
		//! - time step when the damping parameter is large.
		float angularDamping;

		//! - Set this flag to false if this body should never fall asleep. Note that
		//! - this increases CPU usage.
		bool allowSleep;

		//! - Is this body initially awake or sleeping?
		bool awake;

		//! - Should this body be prevented from rotating? Useful for characters.
		bool fixedRotation;

		//! - Is this a fast moving body that should be prevented from tunneling through
		//! - other moving bodies? Note that all bodies are prevented from tunneling through
		//! - kinematic and static bodies. This setting is only considered on dynamic bodies.
		//! - @warning You should use this flag sparingly since it increases processing time.
		bool bullet;

		//! - Does this body start out active?
		bool active;

		//! - Use this to store application specific body data.
		void* userData;

		//! - Scale the gravity applied to this body.
		float gravityScale;
	};
}

#endif //_FCOMMON_H_
