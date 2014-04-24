//! \file SDLFunctionQueue.h
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! 
//!
#ifndef _SDLFUNCTIONQUEUE_H_
#define _SDLFUNCTIONQUEUE_H_

// std library includes
#include <functional> // for std::function
#include <vector> // for std::vector
#include <thread> // for thread_local

#include "SDLMutex.h"
#include "SDLTimer.h"

#include "eError.h"

//! \brief a class to manage a function queue
template< class TFunctionType >
class SDLFunctionQueue
{
public:

	// ctor and dtor
	SDLFunctionQueue();
	~SDLFunctionQueue();

	typedef std::function<TFunctionType> TFunction;

	//! \brief Run a function on the main thread Syncronously with return value
	//! This function will not return until the function on the main thread is complete
	eError AddToQueue_Sync(TFunction, eError& returnVal);

	//! \brief Run a function on the main thread ASyncronously
	//! This function will return instantly, with no wait, and give any error code if there was an issue
	eError AddToQueue_ASync(TFunction);

	//! \brief Run the main thread queue
	//! \warning will not return until StopMainThreadQueue has been called
	eError Run(void);

	//! \brief stop the main thread queue 
	//! will wait till all functions on the queue are finished
	//! can specify to force, and will drop out as soon as the current function has returned
	eError Stop(bool force /* = false */);

private:

	//! \brief The queue of functions
	std::vector< TFunction > m_functionQueue;

	//! \brief the mutex for the function queue
	//! \note in the future, the queue itself could be atomic
	SDLMutex m_myMutex;

	//! \brief integer representing stop priority
	//! 1 for stop (stop when it can, 2 for stop ASAP)
	//! both stops are safe
	//! should probs be an enum...
	int m_bStopRequestPriority;

	//! \brief boolean to check if we're currently event handling
	static THREAD_LOCAL bool isCurrentlyEventHandling;
};

template< class TFunctionType >
THREAD_LOCAL bool SDLFunctionQueue<TFunctionType>::isCurrentlyEventHandling = false;

//========================================================
// fnQueue::fnQueue
//========================================================
template< class TFunctionType >
SDLFunctionQueue<TFunctionType>::SDLFunctionQueue()
: m_bStopRequestPriority(0)
{
	m_myMutex.Create();
}

//========================================================
// fnQueue::~fnQueue
//========================================================
template< class TFunctionType >
SDLFunctionQueue<TFunctionType>::~SDLFunctionQueue()
{
	// TODO: check the current list of functions

	m_myMutex.Destroy();
}


//========================================================
// fnQueue::Run
//========================================================
template< class TFunctionType >
eError SDLFunctionQueue<TFunctionType>::Run()
{
	eError err = eError::noErr;

	// Local variables
	int bStop = 0;
	TFunction funcToPerform = nullptr;

	// Loop untill error is fatal or a quit was requested
	while (!ERROR_HAS_TYPE_FATAL(err)
		&& !ERROR_HAS(err, eError::quitRequest)
		&& ( bStop == 0 ) )
	{
		// TODO: Better solution to this while waiting for functions to be given
		SDLTimer::GlobalDelay(10);

		// Lock the mutex while grabbing members
		m_myMutex.Lock();

		// grab if we need to stop
		bStop = m_bStopRequestPriority;

		int NumInQueue = m_functionQueue.size();

		// Lock the mutex while grabbing members
		m_myMutex.Unlock();

		// if we have a function to do
		while ( ( NumInQueue != 0 ) 
			&& (bStop <= 1) ) // AND no forced stop is requested
		{
			// Lock the mutex while grabbing members
			m_myMutex.Lock();

			// grab if we need to stop again
			bStop = m_bStopRequestPriority;

			// Grab the action to perform
			funcToPerform = m_functionQueue.back();
			m_functionQueue.pop_back();

			m_myMutex.Unlock();

			// We can now call the function outside of the mutex
			if (funcToPerform != nullptr)
			{
				// Set we're currently event handling
				isCurrentlyEventHandling = true;

				// Perform the function
				err |= funcToPerform();

				// turn off event handling
				isCurrentlyEventHandling = false;

				funcToPerform = nullptr;
			}

			// Lock the mutex while grabbing members
			m_myMutex.Lock();
			NumInQueue = m_functionQueue.size();
			m_myMutex.Unlock();
		}
	}

	bStop = 0;

	return err;
}

//========================================================
// fnQueue::AddToQueue_Sync
//========================================================
template< class TFunctionType >
eError SDLFunctionQueue<TFunctionType>::AddToQueue_Sync(TFunction func, eError& returnVal)
{
	// We can safely just call the event here if we're in the middle of event handling on this thread
	if (isCurrentlyEventHandling)
	{
		returnVal = func();
	}

	// For now, without a clever way of doing this, we can just do the async one
	AddToQueue_ASync(func);

	returnVal |= eError::noErr;
	return eError::noErr;
}

//========================================================
// fnQueue::AddToQueue_ASync
//========================================================
template< class TFunctionType >
eError SDLFunctionQueue<TFunctionType>::AddToQueue_ASync(TFunction func)
{
	m_myMutex.Lock();

	m_functionQueue.push_back(func);

	m_myMutex.Unlock();

	return eError::noErr;
}

//========================================================
// fnQueue::Stop
//========================================================
template< class TFunctionType >
eError SDLFunctionQueue<TFunctionType>::Stop(bool force = false)
{
	m_myMutex.Lock();

	m_bStopRequestPriority = 1;
	if (force)
	{
		m_bStopRequestPriority = 2;
	}

	m_myMutex.Unlock();
}
#endif //_SDLFUNCTIONQUEUE_H_