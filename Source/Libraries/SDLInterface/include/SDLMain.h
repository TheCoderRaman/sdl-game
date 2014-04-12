//! \file SDLEventLoop.h
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Header for SDLEventLoop.cpp
//!
#pragma once

#include "types.h"

namespace SDLMain
{
	// Initialise SDL
	eError Init();

	// Quit SDL
	eError Quit();
}