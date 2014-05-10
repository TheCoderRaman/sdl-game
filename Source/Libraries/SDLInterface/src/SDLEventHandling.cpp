//! \file SDLEventHandling.cpp
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Description
//! 
#include "SDLEventHandling.h"

#include "SDL.h"

#include "debug.h"
#include "eError.h"


//========================================================
eError SDLInterface::EventHandling::HandleEvent(SDL_Event *event)
{
	eError err = eError::NoErr;

	// switch through all the event types
	switch (event->type)
	{

		// Keyboard events
	case SDL_KEYUP:
	case SDL_KEYDOWN:
		err |= HandleKeyboardEvent(event);
		break;

		// Text input events
		// Not really handled yet
	case SDL_TEXTEDITING:
	case SDL_TEXTINPUT:
		break;

		// Mouse events
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONUP:
	case SDL_MOUSEBUTTONDOWN:
	case SDL_MOUSEWHEEL:
		err |= HandleMouseEvent(event);
		break;

		// Joystick events
	case SDL_JOYAXISMOTION:
	case SDL_JOYBALLMOTION:
	case SDL_JOYHATMOTION:
	case SDL_JOYBUTTONDOWN:
	case SDL_JOYBUTTONUP:
	case SDL_JOYDEVICEADDED:
	case SDL_JOYDEVICEREMOVED:
		err |= HandleJoystickEvent(event);
		break;

		// Controller events
	case SDL_CONTROLLERAXISMOTION:
	case SDL_CONTROLLERBUTTONDOWN:
	case SDL_CONTROLLERBUTTONUP:
	case SDL_CONTROLLERDEVICEADDED:
	case SDL_CONTROLLERDEVICEREMOVED:
	case SDL_CONTROLLERDEVICEREMAPPED:
		err |= HandleControllerEvent(event);
		break;

		// Window events
	case SDL_WINDOWEVENT:
		err |= HandleWindowEvent(event);
		break;

		// SysWM events ignored
		// see https://wiki.libsdl.org/SDL_SysWMEvent
	case SDL_SYSWMEVENT:
		break;

	default:
		DEBUG_LOG("Unexpected SDL Event: type %i", event->type);
		break;
	}

	return err;
}

//========================================================
eError SDLInterface::EventHandling::HandleKeyboardEvent(SDL_Event *event)
{
	eError err = eError::NoErr;

	/*
	case SDL_KEYUP:
	case SDL_KEYDOWN:
	*/

	return err;
}

//========================================================
eError SDLInterface::EventHandling::HandleMouseEvent(SDL_Event *event)
{
	eError err = eError::NoErr;
	//	DEBUG_LOG("Unhandled Mouse Event");

	/*
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONUP:
	case SDL_MOUSEBUTTONDOWN:
	case SDL_MOUSEWHEEL:
	*/

	return err;
}

//========================================================
eError SDLInterface::EventHandling::HandleJoystickEvent(SDL_Event *event)
{
	eError err = eError::NoErr;

	/*
	case SDL_JOYAXISMOTION:
	case SDL_JOYBALLMOTION:
	case SDL_JOYHATMOTION:
	case SDL_JOYBUTTONDOWN:
	case SDL_JOYBUTTONUP:
	case SDL_JOYDEVICEADDED:
	case SDL_JOYDEVICEREMOVED:
	*/

	return err;
}

//========================================================
eError SDLInterface::EventHandling::HandleControllerEvent(SDL_Event *event)
{
	eError err = eError::NoErr;

	/*
	case SDL_CONTROLLERAXISMOTION:
	case SDL_CONTROLLERBUTTONDOWN:
	case SDL_CONTROLLERBUTTONUP:
	case SDL_CONTROLLERDEVICEADDED:
	case SDL_CONTROLLERDEVICEREMOVED:
	case SDL_CONTROLLERDEVICEREMAPPED:
	*/
	return err;
}

//========================================================
eError SDLInterface::EventHandling::HandleWindowEvent(SDL_Event *event)
{
	eError err = eError::NoErr;

	// Switch between the window events
	switch (event->window.event)
	{
	case SDL_WINDOWEVENT_SHOWN:
	case SDL_WINDOWEVENT_HIDDEN:
	case SDL_WINDOWEVENT_EXPOSED:
	case SDL_WINDOWEVENT_MOVED:
	case SDL_WINDOWEVENT_RESIZED:
	case SDL_WINDOWEVENT_MINIMIZED:
	case SDL_WINDOWEVENT_MAXIMIZED:
	case SDL_WINDOWEVENT_RESTORED:
	case SDL_WINDOWEVENT_ENTER:
	case SDL_WINDOWEVENT_LEAVE:
	case SDL_WINDOWEVENT_FOCUS_GAINED:
	case SDL_WINDOWEVENT_FOCUS_LOST:
	case SDL_WINDOWEVENT_CLOSE:
		break;
	default:
		DEBUG_LOG("Unexpected SDL Event: SDL_WINDOWEVENT %i", event->window.event);
		break;
	}
	return err;
}
