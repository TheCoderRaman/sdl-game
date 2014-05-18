//! \file LEvents.h
//!
//! \author  Marc Di luzio
//! \date    May 2014
//!
//! Definition for the templated LEvents system
//! At first, this may look massively complicated, but I've tried to comment
//! as much as possible, and at it's heart it's really just a very simple system
//!
//!	The user can create an event system with their own event types and event data
//! ie. 
//! typedef LEventManager<typeEnum,dataType> TMyEventSystem;
//! TMyEventSystem m_EventSystem;
//!	
//!	The user can then add "Handlers" to this system
//!	TMyEventSystem::THandler m_EventHandler;
//! m_EventHandler.function = [](TMyEventSystem::TEvent*)->eError 
//! {
//!		// DO STUFF
//!		return eError::Error_Val;
//! };
//!
//! m_EventSystem.AddHandler(typeEnum::Event_Basic,&m_EventHandler);
//!
//! m_EventSystem.SendEvent(typeEnum::Event_Basic,dataType);
//!
//! Then, when the user needs to, they can call FlushEvents and that will delegate all events 
//! calling all the event handlers functions that are listening to that event type
//!
#ifndef _LEVENTS_H_
#define _LEVENTS_H_

#include "types.h"		// For basic types
#include "eError.h"		// For eError types
#include "debug.h"		// For Debug Asserts
#include "map_helpers.h"// For multimap helper functions

// SDL functions needed 
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


//! \brief The parent templated event manager
//! This can be used to send and recieve events of a certain type
template< typename TEventType, typename TEventData >
class LEventManager
{
public:

// Internal types

	//! \brief typedef for the templated event type 
	struct TEvent
	{
		TEventType type; //! the type of the event
		TEventData data; //! the data of the event
	};

	//! \brief The event Handler
	struct THandler
	{
		//! \brief internal function that will be called on event handling
		std::function< eError(TEvent*) >	callbackFunction;
	};


//! couple of typedefs to help readability

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
	eError AddHandler(TEventType type, THandler* listener);

	//! \brief Remove a listener from an event type
	eError RemoveHandler(TEventType type, THandler* listener);

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
eError LEventManager< typename TEventType, typename TEventData >::AddHandler(TEventType type, THandler* listener)
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
eError LEventManager< typename TEventType, typename TEventData >::RemoveHandler(TEventType type, THandler* listener)
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
		return handler->callbackFunction(&event);
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