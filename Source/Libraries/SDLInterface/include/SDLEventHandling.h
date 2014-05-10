//! \file SDLEventHandling.h
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Header for SDLEventHandling.cpp
//!
#ifndef _SDLEVENTHANDLING_H_
#define _SDLEVENTHANDLING_H_

#include "types.h"

// Forward declare SDL union
union SDL_Event;

// Start the SDLInterface Namespace
namespace SDLInterface
{
	class EventHandling
	{
	public:

		//! \brief Handle any event
		//! \return Any eError produced
		static eError HandleEvent(SDL_Event *event);

		//! \brief Handle any keyboard related event
		//! \return Any eError produced
		static eError HandleKeyboardEvent(SDL_Event *event);

		//! \brief Handle any Mouse related event
		//! \return Any eError produced
		static eError HandleMouseEvent(SDL_Event *event);

		//! \brief Handle any Window related event
		//! \return Any eError produced
		static eError HandleWindowEvent(SDL_Event *event);

		//! \brief Handle any Joystick related event
		//! \return Any eError produced
		//! \sa HandleControllerEvent as these two are pretty related
		static eError HandleJoystickEvent(SDL_Event *event);

		//! \brief Handle any Controller related event
		//! \return Any eError produced
		//! \sa HandleJoystickEvent as these two are pretty related
		static eError HandleControllerEvent(SDL_Event *event);


	private:

	};
}

#endif //_SDLEVENTHANDLING_H_