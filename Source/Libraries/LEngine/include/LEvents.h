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
#include "debug.h"
#include "map_helpers.h"

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

//! \brief The event type
template< typename TEventType, typename TEventData >
struct LEvent
{
	TEventType type; //! the type of the event
	TEventData data; //! the data for the event
};

//! \brief the event Listener type
template< typename TEventType, typename TEventData >
struct LEventHandler
{	
	std::function< eError( LEvent<TEventType, TEventData>* ) >	function;
};

//! \brief The parent templated event manager
//! This can be used to send and recieve events of a certain type
template< typename TEventType, typename TEventData >
class LEventManager
	: public LEventManagerBase
{
public:

//! Load of typedefs to help readability

	//! \brief typedef for the templated event type 
	typedef LEvent<TEventType, TEventData>			TEvent;

	//! \brief typedef for the event listener used by this event manager
	typedef LEventHandler<TEventType,TEventData>	THandler;

	//! \brief pair of event type and listener
	typedef std::pair< TEventType, THandler* >		TTypeListenerPair;

	//! \brief typedef for the listener map
	typedef std::multimap < TEventType, THandler* > THandlerMap;

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


// Event Sending methods

	//! \brief Send an event by type and data
	eError SendEvent(TEventType type, TEventData& data);


// Event Listening methods

	//! \brief Add a listener to an event type
	eError AddListener(TEventType type, THandler* listener);

	//! \brief Remove a listener from an event type
	eError RemoveListener(TEventType type, THandler* listener);

private:

// Private methods

	//! \brief Add an event to the event queue
	eError AddEventToQueue(TEvent& event);

	//! \brief Pop an event off the queue
	eError PopEventOffQueue(TEvent& event);

	//! \brief Delegate an event to it's listeners
	eError DelegateEvent(TEvent& event);


// Private members

	//! \brief The current list of events
	//! represents the event queue
	std::list<TEvent>			m_Queue;

	//! \brief A mutex for the eventQueue
	SDLInterface::Mutex			m_QueueMutex;

	//! \brief the map of event type to event listeners 
	THandlerMap					m_ListenerMap;

	//! \brief A mutex for the Listener map
	SDLInterface::Mutex			m_ListenerMapMutex;
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
		err |= m_QueueMutex.Create();

	if (!ERROR_HAS_TYPE_FATAL(err))
		err |= m_ListenerMapMutex.Create();

	return err;
}

//===============================================================
template< typename TEventType, typename TEventData >
eError LEventManager< typename TEventType, typename TEventData >::Destroy()
{
	eError err = eError::NoErr;

	if (!ERROR_HAS_TYPE_FATAL(err))
		err |= m_ListenerMapMutex.Destroy();

	if (!ERROR_HAS_TYPE_FATAL(err))
		err |= m_QueueMutex.Destroy();

	return err;
}

//===============================================================
template< typename TEventType, typename TEventData >
eError LEventManager< typename TEventType, typename TEventData >::AddEventToQueue(TEvent& event)
{
	eError err = eError::NoErr;
	err |= m_QueueMutex.Lock();

	if (m_Queue.size() <= eMaxEvents)
	{
		// Push the event onto the queue
		m_Queue.push_back(event);
	}
	else
	{
		// We should never go over the max event limit
		err |= eError::Type_Fatal | eError::Catagory_Events;
		DEBUG_ASSERT(0);
	}



	err |= m_QueueMutex.Unlock();
	return err;
}

//===============================================================
template< typename TEventType, typename TEventData >
eError LEventManager< typename TEventType, typename TEventData >::AddListener(TEventType type, THandler* listener)
{
	eError err = eError::NoErr;
	err |= m_ListenerMapMutex.Lock();

	// TODO: Assert the listener map size
	m_ListenerMap.insert(TTypeListenerPair(type, listener));

	err |= m_ListenerMapMutex.Unlock();
	return err;
}

//===============================================================
template< typename TEventType, typename TEventData >
eError LEventManager< typename TEventType, typename TEventData >::RemoveListener(TEventType type, THandler* listener)
{
	eError err = eError::NoErr;
	err |= m_ListenerMapMutex.Lock();

	// TODO: Assert the listener map size
	multimap_remove_pair(m_ListenerMap, type, listener);

	err |= m_ListenerMapMutex.Unlock();
	return err;
}

//===============================================================
template< typename TEventType, typename TEventData >
eError LEventManager< typename TEventType, typename TEventData >::PopEventOffQueue(TEvent& event)
{
	eError err = eError::NoErr;
	err |= m_QueueMutex.Lock();

	// If the queue does have an event to pop
	if (m_Queue.size() != 0)
	{
		// Set the event memory to 0
		memset(&event, 0, sizeof(TEvent));

		// Grab the front of the queue
		event = m_Queue.front();

		// Pop off the front
		m_Queue.pop_front();
	}
	else
	{
		// Fire off a warning, or assert in debug
		// We shouldn't be trying to pop an event if we have none left
		err |= eError::Event_Warning;
		DEBUG_ASSERT(0);
	}


	err |= m_QueueMutex.Unlock();
	return err;
}

//===============================================================
template< typename TEventType, typename TEventData >
eError LEventManager< typename TEventType, typename TEventData >::DelegateEvent(TEvent& event)
{
	eError err = eError::NoErr;
	err |= m_ListenerMapMutex.Lock();

	// Construct the lambda for each event handler found
	// This simply calls the event handlers function lamba
	std::function<eError(THandler*)> function = 
	[&](THandler* handler)->eError
	{
		return handler->function(&event);
	};
	
	// Visit all the Handlers in the list and call their functions
	err |= multimap_visit_all(m_ListenerMap, event.type, function);

	err |= m_ListenerMapMutex.Unlock();
	return err;
}

//===============================================================
template< typename TEventType, typename TEventData >
eError LEventManager< typename TEventType, typename TEventData >::SendEvent(TEventType type, TEventData& data)
{
	eError err = eError::NoErr;

	// Construct a new event
	TEvent event;
	event.type = type;
	event.data = data;

	// Add the event to the queue
	err |= AddEventToQueue(event);

	return err;
}

//===============================================================
template< typename TEventType, typename TEventData >
eError LEventManager< typename TEventType, typename TEventData >::FlushEvents()
{
	eError err = eError::NoErr;

	// event storage
	TEvent event;

	// While the queue is not empty
	// other possibility here would be to do a foreach on every event
	// But that would probaly need either a full lock around it, or a full copy of the queue
	while ( ( m_Queue.size() > 0 )
		&&	!ERROR_HAS_TYPE_FATAL(err) )
	{
		// Pop the event off the top of the queue
		err |= PopEventOffQueue(event);

		// Delegate that event
		err |= DelegateEvent(event);
	}

	return err; 
}

#endif //_LEVENTS_H_