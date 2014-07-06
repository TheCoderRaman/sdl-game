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

//! \brief a b2BodyDef from a Ffiseg type
b2BodyDef getb2BodyDef(const Ffiseg::FBodyDef& def);

//! \brief get a b2FixtureDef from a Ffiseg type
b2FixtureDef getb2FixtureDef(const Ffiseg::FFixtureDef& def);

//! \brief Get a b2Filter from the Ffiseg type
b2Filter getb2Filter(const Ffiseg::FFilter& def);

//! \brief Get a b2PolygonShape from the Ffiseg type
b2PolygonShape getb2PolygonShape(const Ffiseg::FPolygonShape& def);

Ffiseg_namespace_end

#endif // _FINTERNAL_H_