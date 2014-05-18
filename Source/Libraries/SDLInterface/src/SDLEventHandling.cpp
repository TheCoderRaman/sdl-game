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


// what is even happen
SDLInterface::SDLKeyboardEvents SDLInterface::EventHandling::sm_KeyboardStruct;

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
eError SDLInterface::EventHandling::HandleKeyboardEvent( SDL_Event *event )
{
	eError err = eError::NoErr;

	eSDLKeyInterface eKeyPressed = eSDLKeyInterface::key_invalid;

	// Converts input from SDL-data to engine-data
	switch( event->key.keysym.sym )
	{
		// Numbahs
		case SDLK_0:
			eKeyPressed = eSDLKeyInterface::key_0;
			break;
		case SDLK_1:
			eKeyPressed = eSDLKeyInterface::key_1;
			break;
		case SDLK_2:
			eKeyPressed = eSDLKeyInterface::key_2;
			break;
		case SDLK_3:
			eKeyPressed = eSDLKeyInterface::key_3;
			break;
		case SDLK_4:
			eKeyPressed = eSDLKeyInterface::key_4;
			break;
		case SDLK_5:
			eKeyPressed = eSDLKeyInterface::key_5;
			break;
		case SDLK_6:
			eKeyPressed = eSDLKeyInterface::key_6;
			break;
		case SDLK_7:
			eKeyPressed = eSDLKeyInterface::key_7;
			break;
		case SDLK_8:
			eKeyPressed = eSDLKeyInterface::key_8;
			break;
		case SDLK_9:
			eKeyPressed = eSDLKeyInterface::key_9;
			break;

		// Speshul
		case SDLK_ESCAPE:
			eKeyPressed = eSDLKeyInterface::key_escape;
			break;
		case SDLK_RETURN:
			eKeyPressed = eSDLKeyInterface::key_return;
			break;
		case SDLK_SPACE:
			eKeyPressed = eSDLKeyInterface::key_space;
			break;

		// Movan
		case SDLK_UP:
			eKeyPressed = eSDLKeyInterface::key_up;
			RUNTIME_LOG( "Registering an UP key event from SDL" );
			break;
		case SDLK_DOWN:
			eKeyPressed = eSDLKeyInterface::key_down;
			RUNTIME_LOG( "Registering a DOWN key event from SDL" );
			break;
		case SDLK_LEFT:
			eKeyPressed = eSDLKeyInterface::key_left;
			break;
		case SDLK_RIGHT:
			eKeyPressed = eSDLKeyInterface::key_right;
			break;
	}

	sm_KeyboardStruct.AddKeyboardEvent( eKeyPressed );

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

bool SDLInterface::EventHandling::GetKeyboardEvent( eSDLKeyInterface eKey )
{
	bool bReturn = false;

	if( sm_KeyboardStruct.m_abKeyboardEvents[ ( unsigned ) eKey ] )
	{
		bReturn = true;
		sm_KeyboardStruct.m_abKeyboardEvents[ ( unsigned ) eKey ] = false;
	}

	return bReturn;
}

void SDLInterface::EventHandling::ResetStructValues()
{
	sm_KeyboardStruct.ResetValues();
}
