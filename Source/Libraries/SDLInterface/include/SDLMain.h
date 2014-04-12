#ifndef _SDLMAIN_H_
#define _SDLMAIN_H_

#include "types.h"

namespace SDLMain
{
	// Initialise SDL
	eError Init();

	// Quit SDL
	eError Quit();
}

#endif //_SDLMAIN_H_