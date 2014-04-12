#ifndef _SDLEVENTLOOP_H_
#define _SDLEVENTLOOP_H_

#include "types.h"

union SDL_Event;

namespace SDLEventLoop
{
	// Do the event loop (horrible function name, feel free to rename)
	eError DoLoop( bool &exit );

	// Event handling
	eError HandleKeyboardEvent( SDL_Event *event );
	eError HandleJoystickEvent( SDL_Event *event );
	eError HandleMouseEvent( SDL_Event *event );
	eError HandleControllerEvent( SDL_Event *event );
	
}

#endif //_SDLEVENTLOOP_H_