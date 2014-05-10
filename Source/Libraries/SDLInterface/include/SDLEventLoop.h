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

// Forward declare SDL union
union SDL_Event;

// Start the SDLInterface Namespace
namespace SDLInterface
{

	//! \brief Namespace for all SDL_Event related methods
	//! 
	//! Handles the SDL_Event loop and fires off the events to appropriate deligates
	class EventLoop
	{
	public:

		//! \brief Type for the main thread function loop
		typedef std::function<eError()> TMainThreadFunction;

		//! \brief create the event loop
		static eError Create();

		//! \brief destroy the event loop
		static eError Destroy();

		//! \brief Do the event loop
		//!
		//! Handles all SDL_Event types and calls down to deligate methods
		//!
		//! \return Any eError produced
		//! \warning this function will not return until SDL_Quit is sent, or a fatal error is encountered
		//! \warning this function MUST be run on the main thread
		//! \warning this function MUST be running for most other SDLInterface functionality to work
		static eError DoLoop();

		//! \brief Ask the event loop to end
		static void EndLoop();

		//! \brief Handle any event
		//! \return Any eError produced
		static eError HandleEvent(SDL_Event *event);

		//! \brief Handle a custom function event
		static eError HandleCustomFunctionEvent(SDL_Event *event);

		//! \brief sent a custom function event
		static eError PostCustomFunctionEvent(TMainThreadFunction& func);

		//! \brief Run a function on the main thread Syncronously with return value
		//! This function will not return untill the function on the main thread is complete
		static eError RunOnMainThread_Sync(eError& returnVal, TMainThreadFunction func);

		//! \brief Run a function on the main thread ASyncronously
		//! This function will return instantly, with no wait, and give any error code if there was an issue
		static eError RunOnMainThread_ASync(TMainThreadFunction func);

		//! \brief get if the eventloop is quitting
		static bool QuitHasBeenRequested();

	private:

		//! \brief request an eventloop quit
		static void RequestQuit();

		//! \brief get if we are safe to quite
		static bool IsLoopEnding();

	};

}

#endif //_SDLEVENTLOOP_H_