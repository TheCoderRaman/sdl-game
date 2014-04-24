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
#include <functional>

union SDL_Event;


//! \brief Namespace for all SDL_Event related methods
//! 
//! Handles the SDL_Event loop and fires off the events to appropriate deligates
namespace SDLEventLoop
{
	//! \brief Type for the main thread function loop
	typedef std::function<eError()> TMainThreadFunction;

	//! \brief create the event loop
	eError Create();

	//! \brief Do the event loop
	//!
	//! Handles all SDL_Event types and calls down to deligate methods
	//!
	//! \return Any eError produced
	//! \warning this method will not return until SDL_Quit is sent, or a fatal error is encountered
	eError DoLoop();

	//! \brief Handle any event
	//! \return Any eError produced
	eError HandleEvent(SDL_Event *event);

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

	//! \brief Handle a custom function event
	eError HandleCustomFunctionEvent( SDL_Event *event );

	//! \brief sent a custom function event
	eError PostCustomFunctionEvent(TMainThreadFunction func);

	//! \brief Run a function on the main thread Syncronously with return value
	//! This function will not return untill the function on the main thread is complete
	eError RunOnMainThread_Sync(eError& returnVal, TMainThreadFunction func);

	//! \brief Run a function on the main thread ASyncronously
	//! This function will return instantly, with no wait, and give any error code if there was an issue
	eError RunOnMainThread_ASync(TMainThreadFunction func);

	//! \brief accessor method to check if the SDLEventLoop has finished
	eError GetHasFinished();
	
}

#endif //_SDLEVENTLOOP_H_