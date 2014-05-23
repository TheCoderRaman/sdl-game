//! \file SDLCommon.h
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Header for various forward common declares for SDL
//!
#ifndef _SDLCOMMON_H_
#define _SDLCOMMON_H_

#include "types.h"

namespace SDLInterface
{
	enum class Error : int;

	class	EventLoop;
	class	Helper;
	class	Mutex;
	struct	Rect;
	class	Renderer;
	class	Surface;
	class	Texture;
	class	Thread;
	class	Timer;
	class	Window;

}

#endif //_SDLCOMMON_H_