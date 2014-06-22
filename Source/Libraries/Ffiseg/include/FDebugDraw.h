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

class FDebugDraw
{
	static FDebugDraw s_debugDraw;

public:

	FDebugDraw()
		: m_world(nullptr)
	{

	}

	static void DebugDraw(SDLInterface::Renderer* renderer);

	static void Register(FWorld* world);

	static void UnRegister();
private:

	FWorld* m_world;
};

Ffiseg_namespace_end


#endif // _FDEBUG_DRAW_