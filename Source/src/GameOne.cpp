//! \file GameOne.cpp
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Main game class, responsible for managing all game specific stuff
//!
#include "GameOne.h"

#include "LUpdateLoop.h"
#include "LInput.h"

#include "LError.h"

//========================================================
GameOne::GameOne()
{

}

//========================================================
GameOne::~GameOne()
{
	
}

//========================================================
LError GameOne::VOnCreate()
{
 	LError err = LError::NoErr;

	// Set up the event handler
	if( !LERROR_HAS_FATAL( err ) )
		err |= m_myEventManager.Create();

	m_myEventHandler.callbackFunction =
		LEVENTHANDLER_CALLBACK_FUNCTION( TGameEventManager )
	{
			return HandleEvent( event );
	};

	m_myEventManager.AddHandler( eGameEventType::GameEvent_pause, &m_myEventHandler );

	// Set up the banana
	m_banana.Create();
	m_banana.SetRenderer(GetRenderer());
	GetObjectManager()->Register(&m_banana);

 	return err;
}

//========================================================
LError GameOne::VOnPreUpdate()
{
	LError err = LError::NoErr;

	return err;
}

//========================================================
LError GameOne::VOnUpdate(ms elapsed)
{
 	LError err = LError::NoErr;

	if( LGameBase::GetInputManager() )
	{
		if( LGameBase::GetInputManager()->GetButtonHeldDown( LInput::eInputType::up ) )
		{
			m_banana.MoveBananaUpAFrame();
		}
		if (LGameBase::GetInputManager()->GetButtonJustPressed(LInput::eInputType::down))
		{
			m_banana.MoveBananaDownAFrame();
		}
	}

	// Send a pause event FOR SOME REASON I DON'T KNOW MAN
	uGameEventData data;
	data.pause.pause_level = 1;
	m_myEventManager.SendEvent( eGameEventType::GameEvent_pause, data );

	// flush the events
	err |= m_myEventManager.FlushEvents();

 	return err;
}

//========================================================
LError GameOne::VOnPostUpdate()
{
	LError err = LError::NoErr;

	return err;
}

//========================================================
LError GameOne::VOnReset()
{
 	LError err = LError::NoErr;

 	return err;
}

//========================================================
LError GameOne::VOnDestroy()
{
 	LError err = LError::NoErr;

	m_banana.Destroy();

	// Remove the event handler
	if (!LERROR_HAS_FATAL(err))
		err |= m_myEventManager.RemoveHandler(eGameEventType::GameEvent_pause, &m_myEventHandler);

	// Remove the banana from the renderer
	if (!LERROR_HAS_FATAL(err))
		err |= GetRenderer()->RemoveRenderable(&m_banana);

	if (!LERROR_HAS_FATAL(err))
		err |= m_myEventManager.Destroy();

 	return err;
}

//========================================================
LError GameOne::HandleEvent(const TGameEventManager::TEvent* event)
{
	// do stuff to handle the events

	return LError::NoErr;
}
