//! \file SDLEventLoop.h
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Header for SDLEventLoop.cpp
//!
#ifndef _SDLEVENTLOOP_H_
#define _SDLEVENTLOOP_H_

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
	//! \return Any eError produced
	//! \warning this method will not return until SDL_Quit is sent, or a fatal error is encountered
	eError DoLoop();

	//! \brief Handle any keyboard related event
	//! \return Any eError produced
	eError HandleKeyboardEvent( SDL_Event *event );

	//! \brief Handle any Mouse related event
	//! \return Any eError produced
	eError HandleMouseEvent( SDL_Event *event );

	//! \brief Handle any Window related event
	//! \return Any eError produced
	eError HandleWindowEvent(SDL_Event *event);

	//! \brief Handle any Joystick related event
	//! \return Any eError produced
	//! \sa HandleControllerEvent as these two are pretty related
	eError HandleJoystickEvent( SDL_Event *event );
	eError HandleControllerEvent( SDL_Event *event );
	
}

#endif //_SDLEVENTLOOP_H_