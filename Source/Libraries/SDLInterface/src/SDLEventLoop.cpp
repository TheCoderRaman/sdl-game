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
#include "eError.h"

//! \brief the custom function event type
Uint32 s_kCustomFunctionEventType = -1;

//! \brief boolean to check if we're currently event handling
static THREAD_LOCAL bool s_isCurrentlyEventHandling = false;

// Create the loop
eError SDLEventLoop::Create()
{
	eError err = eError::noErr;

	if (s_kCustomFunctionEventType == -1)
	{
		s_kCustomFunctionEventType = SDL_RegisterEvents(1);
	}
	else
	{
		err = eError::SDL_Fatal;
	}

	return err;
}

// Do the event loop
eError SDLEventLoop::DoLoop()
{
	eError err = eError::noErr;

	//Event handler
    SDL_Event event;

	// Boolean to store the end
	bool toEnd = false;

	//Handle events on queue
	while ( !toEnd )
    {
		// Peep into the events. SDL_PeepEvents is thread safe, unlike wait or 
		SDL_WaitEvent(&event);
		
		s_isCurrentlyEventHandling = true;

		HandleEvent(&event);

		s_isCurrentlyEventHandling = false;

		toEnd = ( ERROR_HAS_TYPE_FATAL(err)				// Fatal errors
			|| ERROR_HAS(err, eError::quitRequest));	// Quit requests
    }

    if ( err != eError::noErr )
    	DEBUG_LOG("DoLoop Dropped out with eError %i",err);

    return err;
}

// Handle all events
eError SDLEventLoop::HandleEvent(SDL_Event *event)
{
	eError err = eError::noErr;

	switch (event->type)
	{
	case SDL_QUIT:
		DEBUG_LOG("Quit requested");
		err |= eError::quitRequest;
		break;

		// Keyboard events
	case SDL_KEYUP:
	case SDL_KEYDOWN:
		err |= HandleKeyboardEvent(event);
		break;

		// Text input events
	case SDL_TEXTEDITING:
	case SDL_TEXTINPUT:
		DEBUG_LOG("Unhandled SDL Event: SDL_TEXT");
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
		HandleWindowEvent(event);
		break;

		// SysWM events?
	case SDL_SYSWMEVENT:
		DEBUG_LOG("Unhandled SDL Event: SDL_SYSWMEVENT");
		break;

	default:
	{
			   if (event->type == s_kCustomFunctionEventType)
			   {
				   HandleCustomFunctionEvent(event);
			   }
			   else
			   {
				   DEBUG_LOG("Unhandled SDL Event: type %i", event->type);
			   }
	}
		break;
	}

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

// Handles all Controller events
eError SDLEventLoop::HandleWindowEvent(SDL_Event *event)
{
	eError err = eError::noErr;

	switch (event->window.event)
	{
		case SDL_WINDOWEVENT_SHOWN:
			DEBUG_LOG("SDL_WINDOWEVENT_SHOWN");
			break;
		default:
			DEBUG_LOG("Unhandled SDL Event: SDL_WINDOWEVENT %i", event->window.event);
			break;
	}
	return err;
}

//! \brief Handle a custom function event
eError SDLEventLoop::HandleCustomFunctionEvent(SDL_Event *event)
{
	eError err = eError::noErr;

	// Call the function
	TMainThreadFunction* function = static_cast<TMainThreadFunction*>(event->user.data1);

	// Call the function
	function->operator()();

	// trigger the semaphore

	// delete the function ( it was newed in PostCustomFunctionEvent )
	delete function;

	return err;
}

//! \brief Handle a custom function event
eError SDLEventLoop::PostCustomFunctionEvent(TMainThreadFunction func)
{
	eError err = eError::noErr;

	// NEW the function, to be deleted after the function is called
	// This is because whatever function was passed in may be out of scope by the time it gets called
	TMainThreadFunction* tempFunc = new TMainThreadFunction(func);

	SDL_Event customEvent;
	SDL_zero(customEvent);
	customEvent.type = s_kCustomFunctionEventType;
	customEvent.user.code = 0; /* dunno */
	customEvent.user.data1 = tempFunc;
	customEvent.user.data2 = 0; /* semaphore */

	SDL_PushEvent(&customEvent);

	return err;
}

//! \brief Run a function on the main thread Syncronously with return value
//! This function will not return untill the function on the main thread is complete
eError SDLEventLoop::RunOnMainThread_Sync(TMainThreadFunction func, eError& returnVal)
{
	eError err = eError::noErr;

	// s_isCurrentlyEventHandling is thread local
	// That means if this is true then we're on the main thread AND we're alread handling an event
	// This means we may as well just call the function to prevent deadlocks
	if (s_isCurrentlyEventHandling)
	{
		returnVal = func();
	}
	else
	{
		// run it async for now until semaphore is implemented
		returnVal = err;
		err = RunOnMainThread_ASync(func);
	}

	return err;
}

//! \brief Run a function on the main thread ASyncronously
//! This function will return instantly, with no wait, and give any error code if there was an issue
eError SDLEventLoop::RunOnMainThread_ASync(TMainThreadFunction func)
{
	eError err = eError::noErr;

	// Post the custom function event
	PostCustomFunctionEvent(func);

	return err;
}