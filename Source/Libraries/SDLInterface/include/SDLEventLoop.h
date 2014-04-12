//! \file SDLEventLoop.h
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Header for SDLEventLoop.cpp
//!
#pragma once

#include "types.h"

union SDL_Event;

//! \brief Namespace for all SDL_Event related methods
//! 
//! Handles the SDL_Event loop and fires off the events to appropriate deligates
namespace SDLEventLoop
{
	//! \brief Do the event loop
	//!
	//! Handles all SDL_Event types and calls down to deligate methods
	//!
	//! \return Any error produced
	//! \warning Calling this method will not allow an exit until SDL_Quit sent
	eError DoLoop( bool &exit );

	//! \brief Handle any keyboard related event
	//! \return Any error produced
	eError HandleKeyboardEvent( SDL_Event *event );

	//! \brief Handle any Mouse related event
	//! \return Any error produced
	eError HandleMouseEvent( SDL_Event *event );

	//! \brief Handle any Joystick related event
	//! \return Any error produced
	//! \sa HandleControllerEvent as these two are pretty related
	eError HandleJoystickEvent( SDL_Event *event );

	//! \brief Handle any Controller related event
	//! \return Any error produced
	//! \sa HandleJoystickEvent as these two are pretty related
	eError HandleControllerEvent( SDL_Event *event );
	
}