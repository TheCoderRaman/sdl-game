//! \file SDLEventLoop.cpp
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Description
//! 
#include "SDLEventLoop.h"

#include "SDL.h"

#include "debug.h"

// Do the event loop
eError SDLEventLoop::DoLoop( bool &exit_request )
{
	eError err = eError::noErr;

	//Event handler
    SDL_Event event;

	//Handle events on queue
    while( SDL_PollEvent( &event ) != 0 
			&& !ERROR_TYPE_IS_FATAL(err) )
    {
    	switch( event.type )
    	{
    		case SDL_QUIT:
    			exit_request = true;
				DEBUG_LOG("Quit requested\n");
    			break;

			// Keyboard events
    		case SDL_KEYUP:
    		case SDL_KEYDOWN:
    			err |= HandleKeyboardEvent(&event);
    			break;

			// Text input events
    		case SDL_TEXTEDITING:
    		case SDL_TEXTINPUT:
				DEBUG_LOG("Unhandled SDL Event: SDL_TEXT\n");
    			break;

			// Mouse events
    		case SDL_MOUSEMOTION:
    		case SDL_MOUSEBUTTONUP:
    		case SDL_MOUSEBUTTONDOWN:
    		case SDL_MOUSEWHEEL:
    			err |= HandleMouseEvent(&event);
    			break;

			// Joystick events
			case SDL_JOYAXISMOTION:
			case SDL_JOYBALLMOTION:
			case SDL_JOYHATMOTION:
			case SDL_JOYBUTTONDOWN:
			case SDL_JOYBUTTONUP:
			case SDL_JOYDEVICEADDED:
			case SDL_JOYDEVICEREMOVED:
    			err |= HandleJoystickEvent(&event);
				break;

			// Controller events
			case SDL_CONTROLLERAXISMOTION:
			case SDL_CONTROLLERBUTTONDOWN:
			case SDL_CONTROLLERBUTTONUP:
			case SDL_CONTROLLERDEVICEADDED:
			case SDL_CONTROLLERDEVICEREMOVED:
			case SDL_CONTROLLERDEVICEREMAPPED:
    			err |= HandleControllerEvent(&event);
				break;

			// Window events
			case SDL_WINDOWEVENT:
				DEBUG_LOG("Unhandled SDL Event: SDL_WINDOWEVENT\n");
				break;

			// SysWM events?
			case SDL_SYSWMEVENT:
				DEBUG_LOG("Unhandled SDL Event: SDL_SYSWMEVENT\n");
				break;

    		default:
    			DEBUG_LOG("Unhandled SDL Event: type %i\n",event.type);
    			break;
    	}
    }

    if ( err != eError::noErr )
    	DEBUG_LOG("DoLoop Dropped out with eError %i\n",err);

    return err;
}

// Handle all keyboard events
eError SDLEventLoop::HandleKeyboardEvent( SDL_Event *event )
{
	eError err = eError::noErr;
	return err;
}

// Handles all mouse events
eError SDLEventLoop::HandleMouseEvent( SDL_Event *event )
{
	eError err = eError::noErr;
	return err;
}

// Handles all Joystick events
eError SDLEventLoop::HandleJoystickEvent( SDL_Event *event )
{
	eError err = eError::noErr;
	return err;
}

// Handles all Controller events
eError SDLEventLoop::HandleControllerEvent( SDL_Event *event )
{
	eError err = eError::noErr;
	return err;
}