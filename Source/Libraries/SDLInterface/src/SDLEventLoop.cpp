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

#include "SDLMutex.h"

//! \brief the custom function event type
Uint32 s_kCustomFunctionEventType = -1;

//! \brief boolean to check if we're currently event handling
THREAD_LOCAL bool s_isCurrentlyEventHandling = false;

//! \brief boolean to store if the SDLEvent loop has finished
bool s_hasFinished = false;

//========================================================
eError SDLEventLoop::GetHasFinished()
{
	eError err = eError::noErr;

	if (s_hasFinished)
		err = eError::quitRequest;

	return err;
}

//========================================================
eError SDLEventLoop::Create()
{
	eError err = eError::noErr;

	// Reset to ensure HadFinished is false
	s_hasFinished = false;

	// Register the custom event
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

//========================================================
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

		err = HandleEvent(&event);

		s_isCurrentlyEventHandling = false;

		toEnd = ( ERROR_HAS_TYPE_FATAL(err)				// Fatal errors
			|| ERROR_HAS(err, eError::quitRequest));	// Quit requests
    }

    if ( err != eError::noErr )
    	DEBUG_LOG("DoLoop Dropped out with eError %i",err);

	// Set that the eventloop has finished
	s_hasFinished = true;

    return err;
}

//========================================================
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

//========================================================
eError SDLEventLoop::HandleKeyboardEvent( SDL_Event *event )
{
	eError err = eError::noErr;
	return err;
}

//========================================================
eError SDLEventLoop::HandleMouseEvent( SDL_Event *event )
{
	eError err = eError::noErr;
	return err;
}

//========================================================
eError SDLEventLoop::HandleJoystickEvent( SDL_Event *event )
{
	eError err = eError::noErr;
	return err;
}

//========================================================
eError SDLEventLoop::HandleControllerEvent( SDL_Event *event )
{
	eError err = eError::noErr;
	return err;
}

//========================================================
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

//========================================================
eError SDLEventLoop::HandleCustomFunctionEvent(SDL_Event *event)
{
	eError err = eError::noErr;

	// Grab  the function
	TMainThreadFunction* function = static_cast<TMainThreadFunction*>(event->user.data1);

	// Call the function
	function->operator()();

	// delete the function ( it was newed in PostCustomFunctionEvent )
	delete function;

	return err;
}

//========================================================
eError SDLEventLoop::PostCustomFunctionEvent(TMainThreadFunction func)
{
	eError err = eError::noErr;

	// NEW the function, to be deleted after the function is called
	// This is because whatever function was passed in may be out of scope by the time it gets called
	TMainThreadFunction* tempFunc = new TMainThreadFunction(func);

	// Create a custom event
	SDL_Event customEvent;
	SDL_zero(customEvent);

	// Set the custom event type and data
	customEvent.type = s_kCustomFunctionEventType;
	customEvent.user.code = 0; /* dunno */
	customEvent.user.data1 = tempFunc;
	customEvent.user.data2 = 0; /* anything else? */

	SDL_PushEvent(&customEvent);

	return err;
}

//========================================================
eError SDLEventLoop::RunOnMainThread_Sync(eError& returnVal, TMainThreadFunction func)
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
		SDLSemaphore* tempSem = new SDLSemaphore();
		tempSem->Create();

		// Create a new temporary function that will post the semaphore and grab the return value
		TMainThreadFunction newTempFunc = [&]()->eError {
			returnVal = func();
			tempSem->Post();
			
			return eError::noErr;
		};

		// run it async for now until semaphore is implemented
		err = PostCustomFunctionEvent(newTempFunc);

		// Wait for the semaphore to be posted
		tempSem->Wait();

		tempSem->Destroy();
		delete tempSem;
	}

	return err;
}

//========================================================
eError SDLEventLoop::RunOnMainThread_ASync(TMainThreadFunction func)
{
	eError err = eError::noErr;

	// Post the custom function event
	PostCustomFunctionEvent(func);

	return err;
}