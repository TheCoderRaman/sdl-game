//! \file SDLEventLoop.cpp
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Description
//! 
#include "SDLEventLoop.h"

#include "SDL.h"

// Do the event loop
eError SDLEventLoop::DoLoop( bool &exit_request )
{
	eError err = eError_noErr;

	//Event handler
    SDL_Event event;

	//Handle events on queue
    while( SDL_PollEvent( &event ) != 0 )
    {
    	switch( event.type )
    	{
    		case SDL_QUIT:
    			exit_request = true;
				DEBUG_LOG("Quit requested\n");
    			break;

    		case SDL_KEYUP:
    		case SDL_KEYDOWN:
    			err = HandleKeyboardEvent(&event);
    			break;

    		case SDL_TEXTEDITING:
    		case SDL_TEXTINPUT:
				DEBUG_LOG("Unhandled SDL Event: SDL_TEXT\n");
    			break;

    		case SDL_MOUSEMOTION:
    		case SDL_MOUSEBUTTONUP:
    		case SDL_MOUSEBUTTONDOWN:
    		case SDL_MOUSEWHEEL:
    			err = HandleMouseEvent(&event);
    			break;

			case SDL_JOYAXISMOTION:
			case SDL_JOYBALLMOTION:
			case SDL_JOYHATMOTION:
			case SDL_JOYBUTTONDOWN:
			case SDL_JOYBUTTONUP:
			case SDL_JOYDEVICEADDED:
			case SDL_JOYDEVICEREMOVED:
    			err = HandleJoystickEvent(&event);
				break;

			case SDL_CONTROLLERAXISMOTION:
			case SDL_CONTROLLERBUTTONDOWN:
			case SDL_CONTROLLERBUTTONUP:
			case SDL_CONTROLLERDEVICEADDED:
			case SDL_CONTROLLERDEVICEREMOVED:
			case SDL_CONTROLLERDEVICEREMAPPED:
    			err = HandleControllerEvent(&event);
				break;

			case SDL_WINDOWEVENT:
				DEBUG_LOG("Unhandled SDL Event: SDL_WINDOWEVENT\n");
				break;

			case SDL_SYSWMEVENT:
				DEBUG_LOG("Unhandled SDL Event: SDL_SYSWMEVENT\n");
				break;

    		default:
    			DEBUG_LOG("Unhandled SDL Event: type %i\n",event.type);
    			break;
    	}
    }

    if ( err != eError_noErr )
    	DEBUG_LOG("DoLoop Failed with ERROR %i\n",err);

    return err;
}

// Handle all keyboard events
eError SDLEventLoop::HandleKeyboardEvent( SDL_Event *event )
{
	eError err = eError_noErr;
	return err;
}

// Handles all mouse events
eError SDLEventLoop::HandleMouseEvent( SDL_Event *event )
{
	eError err = eError_noErr;
	return err;
}

// Handles all Joystick events
eError SDLEventLoop::HandleJoystickEvent( SDL_Event *event )
{
	eError err = eError_noErr;
	return err;
}

// Handles all Controller events
eError SDLEventLoop::HandleControllerEvent( SDL_Event *event )
{
	eError err = eError_noErr;
	return err;
}