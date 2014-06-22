//! \file FInternal.h
//!
//! \author  Marc Di luzio
//! \date    June 2014
//!
//! Common includes and declarations for the physics system
//!
#ifndef _FINTERNAL_H_
#define _FINTERNAL_H_

#include "FCommon.h"
#include "Box2D/Box2D.h"

#include "FShape.h"

Ffiseg_namespace_start

b2BodyDef getb2BodyDef(const Ffiseg::FBodyDef& def);

b2FixtureDef getb2FixtureDef(const Ffiseg::FFixtureDef& def);

b2Filter getb2Filter(const Ffiseg::FFilter& def);

b2PolygonShape getb2PolygonShape(const Ffiseg::FPolygonShape& def);

Ffiseg_namespace_end
#endif // _FINTERNAL_H_