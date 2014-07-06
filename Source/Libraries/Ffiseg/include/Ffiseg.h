//! \file Ffiseg.h
//!
//! \author  Marc Di luzio
//! \date    July 2014
//!	
//!	Ffiseg 
//!	A physics wrapper for Box2D
//!	
//!	Designed as a helper system to just let box2D do it's thing
//!	Box2D itself already as a simple enough interface, but a level
//!	of indirection - in case we want to swap out to another underlying
//!	physics system, is needed and has the advantage of being able to 
//!	provide helper functions and debug drawing
//!	
#ifndef _FFISEG_H_
#define _FFISEG_H_

#include "FCommon.h"

#include "FRigidBody.h"
#include "FShape.h"
#include "FWorld.h"

#include "FDebugDraw.h"

#endif //_FFISEG_H_