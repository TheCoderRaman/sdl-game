//! \file LEvents.h
//!
//! \author  Marc Di luzio
//! \date    May 2014
//!
//! Header for LEvents.cpp
//!
#ifndef _LEVENTS_H_
#define _LEVENTS_H_

#include "types.h"
#include "eError.h"

// SDL functions needed 
#include "SDLThread.h"	// For the EventLoop thread, if wanted
#include "SDLMutex.h"	// For the Mutexes to guard the events

// A while load of STD library things used here
// Sorry
#include <atomic>		// For atomic boolean values
#include <list>			// For the event queues
#include <functional>	// For the function that the event listener will call
#include <map>			// For the event type -> listener map
#include <vector>		// For the map, to map type -> vector of listeners

// Maximum numbers here
// Lowball for now to help debug

//! \brief The maximum number of events to be allowed in the queue
enum { eMaxEvents = 32 };

//! \brief The maximum number of listerners to a single event type
enum { eMacListeners = 8 };


//! \brief the base untyped LEventManager
//! This allows a set of private functions to be defined in a cpp file
//! Most of eveything here is protected, to ensure that only the subclass can use it
//! Put any EventManager function that is generic and does not need to be templated here
class LEventManagerBase
{
protected:

	LEventManagerBase();
	~LEventManagerBase();

};

//! \brief the event Listener type
template< typename TEventData >
struct LEventListener
{	
	std::function<eError(TEventData*)>	function;
};

//! \brief The event type
template< typename TEventType, typename TEventData >
struct LEvent
{
	TEventType type; //! the type of the event
	TEventData data; //! the data for the event
};

//! \brief The parent templated event manager
//! This can be used to send and recieve events of a certain type
template< typename TEventType, typename TEventData >
class LEventManager
	: public LEventManagerBase
{
public:

	//! \brief typedef for the event type 
	typedef LEvent<TEventType, TEventData>	TEvent;

	//! \brief typedef for the event listener used by this event manager
	typedef LEventListener<TEventData>		TListener;

public:

// Creation and Destruction

	//! \brief Default constructor
	LEventManager();

	//! \brief Create the Event Manager
	eError Create();

	//! \brief Destroy the Event Manager
	eError Destroy();

	//! \brief Default destructor
	~LEventManager();


// Event Handling methods

	//! \brief Flush the events
	//! will delegate all events down to thier listeners
	eError FlushEvents();

	//! \brief Get the next event from the queue
	eError GetEvent(TEvent& event);

	//! \brief Get the number of events in the current queue
	int GetNumEvents();

// Event Sending methods

	//! \brief Send an event by event
	eError SendEvent(TEvent& event);

	//! \brief Send an event by type and data
	eError SendEvent(TEventType type, TEventData& data);


// Event Listening methods

	//! \brief Add a listener to an event type
	eError AddListener(TEventType type, TListener* listener);

	//! \brief Remove a listener from an event type
	eError RemoveListener(TEventType type, TListener* listener);

private:

// Private methods

	//! \brief Add an event to the event queue
	eError AddEventToQueue(TEvent& event);

	//! \brief Delegate an event to it's listeners
	eError DelegateEvent(TEvent& event);


// Private members

	//! \brief The current list of events
	//! represents the event queue
	std::list<TEvent>									m_Queue;

	//! \brief A mutex for the eventQueue
	SDLInterface::Mutex									m_QueueMutex;

	//! \brief the map of event type to event listeners 
	std::map < TEventType, std::vector<TListener*> >	m_ListenerMap;

	//! \brief A mutex for the Listener map
	SDLInterface::Mutex									m_ListenerMapMutex;
};

//===============================================================
template< typename TEventType, typename TEventData >
LEventManager< typename TEventType, typename TEventData >::LEventManager()
{

}

//===============================================================
template< typename TEventType, typename TEventData >
LEventManager< typename TEventType, typename TEventData >::~LEventManager()
{

}

//===============================================================
template< typename TEventType, typename TEventData >
eError LEventManager< typename TEventType, typename TEventData >::Create()
{
	eError err = eError::NoErr;

	if (!ERROR_HAS_TYPE_FATAL(err))
		m_QueueMutex.Create();

	if (!ERROR_HAS_TYPE_FATAL(err))
		m_ListenerMapMutex.Create();

	return err;
}

//===============================================================
template< typename TEventType, typename TEventData >
eError LEventManager< typename TEventType, typename TEventData >::Destroy()
{
	eError err = eError::NoErr;

	if (!ERROR_HAS_TYPE_FATAL(err))
		m_ListenerMapMutex.Destroy();

	if (!ERROR_HAS_TYPE_FATAL(err))
		m_QueueMutex.Destroy();

	return err;
}


#endif //_LEVENTS_H_