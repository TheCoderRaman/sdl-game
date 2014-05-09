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

#include <atomic>

//! \brief the custom function event type
Uint32 s_iCustomFunctionEventType = 0;

//! \brief boolean to check if we're currently event handling
THREAD_LOCAL bool s_isCurrentlyEventHandling(false);

//! \brief param to check if it is safe to quit
std::atomic<bool> s_bEventLoopEnding(false);

//! \brief member to show that the eventloop is quitting
std::atomic<bool> s_bEventLoopQuitRequested(false);

//! \brief parameter to see if the eventloop is running
std::atomic<bool> s_bEventLoopRunning(false);

//========================================================
bool SDLInterface::EventLoop::IsLoopEnding()
{
	return s_bEventLoopEnding;
}

//========================================================
void SDLInterface::EventLoop::EndLoop()
{
	s_bEventLoopEnding = true;
}

//========================================================
bool SDLInterface::EventLoop::QuitHasBeenRequested()
{
	return s_bEventLoopQuitRequested;
}

//========================================================
void SDLInterface::EventLoop::RequestQuit()
{
	s_bEventLoopQuitRequested = true;
}

//========================================================
eError SDLInterface::EventLoop::Create()
{
	eError err = eError::NoErr;

	// Register the custom event
	if (s_iCustomFunctionEventType == 0)
	{
		s_iCustomFunctionEventType = SDL_RegisterEvents(1);
	}
	else
	{
		err |= eError::SDL_Fatal;
		DEBUG_LOG("ERROR Possible EventLoop::Create called twice?")
	}

	return err;
}

//========================================================
eError SDLInterface::EventLoop::Destroy()
{
	eError err = eError::NoErr;

	return err;
}

//========================================================
eError SDLInterface::EventLoop::DoLoop()
{
	eError err = eError::NoErr;

	//Event handler
    SDL_Event event;

	s_bEventLoopRunning = true;

	// Handle events on queue
	// End if there's a fatal error, or we've been told it's safe to quit
	while (!(ERROR_HAS_TYPE_FATAL(err) || IsLoopEnding()))
    {
		// Wait for an event with a timout of 10
		// timeout ensures we can quit
		const int ret = SDL_WaitEventTimeout(&event,10);

		// Handle the event
		if (ret > 0)
			err |= HandleEvent(&event);
    }

	REMOVE_ERR(err, eError::QuitRequest);

    if ( err != eError::NoErr )
    	DEBUG_LOG("DoLoop Dropped out with eError %i",err);

	s_bEventLoopRunning = false;

    return err;
}

//========================================================
eError SDLInterface::EventLoop::HandleEvent(SDL_Event *event)
{
	eError err = eError::NoErr;

	// Set we're currently event handling
	s_isCurrentlyEventHandling = true;

	// switch through all the event types
	switch (event->type)
	{
		case SDL_QUIT:
			DEBUG_LOG("SDL_QUIT recieved");
			RequestQuit();
			break;

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
			{
				if (event->type == s_iCustomFunctionEventType)
				{
					err |= HandleCustomFunctionEvent(event);
				}
				else
				{
					DEBUG_LOG("Unexpected SDL Event: type %i", event->type);
				}
			}
			break;
	}

	// Turn off current event handline
	s_isCurrentlyEventHandling = false;

	return err;
}

//========================================================
eError SDLInterface::EventLoop::HandleKeyboardEvent(SDL_Event *event)
{
	eError err = eError::NoErr;

	/*
		case SDL_KEYUP:
		case SDL_KEYDOWN:
	*/

	return err;
}

//========================================================
eError SDLInterface::EventLoop::HandleMouseEvent(SDL_Event *event)
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
eError SDLInterface::EventLoop::HandleJoystickEvent(SDL_Event *event)
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
eError SDLInterface::EventLoop::HandleControllerEvent(SDL_Event *event)
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
eError SDLInterface::EventLoop::HandleWindowEvent(SDL_Event *event)
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

//========================================================
eError SDLInterface::EventLoop::HandleCustomFunctionEvent(SDL_Event *event)
{
	eError err = eError::NoErr;

	// Grab  the function
	TMainThreadFunction* function = static_cast<TMainThreadFunction*>(event->user.data1);

	// Call the function
	err |= function->operator()();

	// delete the function ( it was newed in PostCustomFunctionEvent )
	delete function;

	return err;
}

//========================================================
eError SDLInterface::EventLoop::PostCustomFunctionEvent(TMainThreadFunction& func)
{
	eError err = eError::NoErr;

	// NEW the function, to be deleted after the function is called
	// This is because whatever function was passed in may be out of scope by the time it gets called
	TMainThreadFunction* tempFunc = new TMainThreadFunction(func);

	// Create a custom event
	SDL_Event customEvent;
	SDL_zero(customEvent);

	// Set the custom event type and data
	customEvent.type = s_iCustomFunctionEventType;
	customEvent.user.code = 0; /* dunno */
	customEvent.user.data1 = tempFunc;
	customEvent.user.data2 = 0; /* anything else? */

	// push the event into the SDL event queue
	SDL_PushEvent(&customEvent);

	return err;
}

//========================================================
eError SDLInterface::EventLoop::RunOnMainThread_Sync(eError& returnVal, TMainThreadFunction func)
{
	eError err = eError::NoErr;

	// We must be running at this point
	// Any functions that call into here before or after we're running the event loop
	// expose serious issues in call order
	DEBUG_ASSERT(s_bEventLoopRunning);

	// s_isCurrentlyEventHandling is thread local
	// That means if this is true then we're on the main thread AND we're alread handling an event
	// This means we may as well just call the function to prevent deadlocks
	if ( s_isCurrentlyEventHandling )
	{
		returnVal = func();
	}
	else
	{
		// Create a temporary semaphore
		Semaphore* tempSem = new Semaphore();
		tempSem->Create();

		// Create a new temporary function that will post the semaphore and grab the return value
		TMainThreadFunction newTempFunc = [&]()->eError {

			eError err = eError::NoErr;

			// Call the custom function and grab it's return value
			returnVal |= func();

			// Post the semaphore to show it has finished
			err |= tempSem->Post();
			
			return err;
		};

		// run it async for now until semaphore is implemented
		err |= PostCustomFunctionEvent(newTempFunc);

		// Wait for the semaphore to be posted
		tempSem->Wait();

		// Destroy the temporary semaphore
		tempSem->Destroy();
		delete tempSem;
	}

	return err;
}

//========================================================
eError SDLInterface::EventLoop::RunOnMainThread_ASync(TMainThreadFunction func)
{
	eError err = eError::NoErr;

	// Post the custom function event
	err |= PostCustomFunctionEvent(func);

	return err;
}