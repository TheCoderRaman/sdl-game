//! \file FDebugDraw.h
//!
//! \author  Marc Di luzio
//! \date    June 2014
//!
//! Header for FDebugDraw.cpp
//!
#ifndef _FDEBUG_DRAW_
#define _FDEBUG_DRAW_

#include "FCommon.h"
#include "FWorld.h"

#include "SDLRenderer.h"

Ffiseg_namespace_start

//! \brief Debug draw class, used to register and draw the box2D world
class FDebugDraw
{
	//! \brief Static class member
	static FDebugDraw s_debugDraw;

public:

	//! \brief Constructor
	FDebugDraw()
		: m_world(nullptr)
	{

	}

	//! \brief Draw the world
	static void DebugDraw(SDLInterface::Renderer* renderer);

	//! \brief Register a world to draw
	static void Register(FWorld* world);

	//! \brief Unregister the current world
	static void UnRegister();

private:

	//! \brief Pointer to the physics world to draw
	FWorld* m_world;
};

Ffiseg_namespace_end


#endif // _FDEBUG_DRAW_