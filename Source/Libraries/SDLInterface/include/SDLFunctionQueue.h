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

#include "SDLMutex.h"

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
};

//========================================================
// fnQueue::fnQueue
//========================================================
template< class TFunctionType >
SDLFunctionQueue<TFunctionType>::SDLFunctionQueue()
{

}

//========================================================
// fnQueue::~fnQueue
//========================================================
template< class TFunctionType >
SDLFunctionQueue<TFunctionType>::~SDLFunctionQueue()
{

}


//========================================================
// fnQueue::fnQueue
//========================================================
template< class TFunctionType >
eError SDLFunctionQueue<TFunctionType>::Run()
{
	eError err = eError::noErr;

	return err;
}

#endif //_SDLFUNCTIONQUEUE_H_