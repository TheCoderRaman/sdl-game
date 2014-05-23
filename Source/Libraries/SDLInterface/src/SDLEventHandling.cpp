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
#include "SDLError.h"

#define INPUT_DEBUGGING 0

#if INPUT_DEBUGGING
#define INPUT_DEBUG(...) DEBUG_LOG(__VA_ARGS__)
#else
#define INPUT_DEBUG(...)
#endif



// what is even happen
SDLInterface::SDLKeyboardEvents SDLInterface::EventHandling::sm_KeyboardStruct;

//========================================================
SDLInterface::Error SDLInterface::EventHandling::HandleEvent(SDL_Event *event)
{
	Error err = Error::None;

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
SDLInterface::Error SDLInterface::EventHandling::HandleKeyboardEvent( SDL_Event *event )
{
	Error err = Error::None;

	eSDLKeyInterface eKeyPressed = eSDLKeyInterface::key_invalid;

	bool keyDown = (event->key.state == SDL_PRESSED);
	bool held = event->key.repeat;

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
			break;
		case SDLK_DOWN:
			eKeyPressed = eSDLKeyInterface::key_down;
			break;
		case SDLK_LEFT:
			eKeyPressed = eSDLKeyInterface::key_left;
			break;
		case SDLK_RIGHT:
			eKeyPressed = eSDLKeyInterface::key_right;
			break;
	}

	eKeyState& state = sm_KeyboardStruct.m_abKeyboardEvents[(unsigned)eKeyPressed];

	// For key down events
	if (keyDown)
	{
		if (state == eKeyState::released || state == eKeyState::being_released)
		{
			INPUT_DEBUG("setting %i from released > being_pressed", (unsigned)eKeyPressed);
			state = eKeyState::being_pressed;
		}
	
	}
	// for key up events
	else
	{
		if (state == eKeyState::pressed || state == eKeyState::being_pressed )
		{
			INPUT_DEBUG("setting %i from pressed|being_pressed> being_released", (unsigned)eKeyPressed);
			state = eKeyState::being_released;
		}
	}

	return err;
}

//========================================================
SDLInterface::Error SDLInterface::EventHandling::HandleMouseEvent(SDL_Event *event)
{
	Error err = Error::None;
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
SDLInterface::Error SDLInterface::EventHandling::HandleJoystickEvent(SDL_Event *event)
{
	Error err = Error::None;

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
SDLInterface::Error SDLInterface::EventHandling::HandleControllerEvent(SDL_Event *event)
{
	Error err = Error::None;

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
SDLInterface::Error SDLInterface::EventHandling::HandleWindowEvent(SDL_Event *event)
{
	Error err = Error::None;

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

bool SDLInterface::EventHandling::GetKeyPressed( eSDLKeyInterface eKey )
{
	eKeyState state = sm_KeyboardStruct.m_abKeyboardEvents[(unsigned)eKey];

	// Return true as long as we're not currently released
	return (state != eKeyState::released);
}

void SDLInterface::EventHandling::FlushKeys()
{
	for (int i = 0; i < (int)eSDLKeyInterface::total_keys; i++)
	{
		eKeyState& state = sm_KeyboardStruct.m_abKeyboardEvents[i];

		// Progress the events past the intermediate stage
		switch (state)
		{
		case eKeyState::being_released:
			INPUT_DEBUG("flushing %i from being_released >> released",i);
			state = eKeyState::released;
			break;

		case eKeyState::being_pressed:
			INPUT_DEBUG("flushing %i from being_pressed >> pressed",i);
			state = eKeyState::pressed;
			break;
		}
	}
}
