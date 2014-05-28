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
LError GameOne::Create()
{
 	LError err = LError::NoErr;

	err |= LGameBase::Create();

	if( !LERROR_HAS_FATAL( err ) )
		err |= m_myEventManager.Create();

	// Setting up the banana object
	m_banana.SetRenderer( GetRenderer() );
	GetObjectManager()->RegisterObject( &m_banana );

	m_myEventHandler.callbackFunction =
		LEVENTHANDLER_CALLBACK_FUNCTION( TGameEventManager )
	{
			return HandleEvent( event );
	};

	m_myEventManager.AddHandler( eGameEventType::GameEvent_pause, &m_myEventHandler );

 	return err;
}

//========================================================
LError GameOne::Initialise()
{
 	LError err = LError::NoErr;

	err |= LGameBase::Initialise();

 	return err;
}

//========================================================
LError GameOne::PreUpdate()
{
	LError err = LError::NoErr;

	err |= LGameBase::PreUpdate();

	return err;
}

//========================================================
LError GameOne::Update(ms elapsed)
{
 	LError err = LError::NoErr;

	err |= LGameBase::Update(elapsed);

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
LError GameOne::PostUpdate()
{
	LError err = LError::NoErr;

	err |= LGameBase::PostUpdate();

	return err;
}

//========================================================
LError GameOne::Reset()
{
 	LError err = LError::NoErr;

	err |= LGameBase::Reset();

 	return err;
}

//========================================================
LError GameOne::Destroy()
{
 	LError err = LError::NoErr;

	// Remove the event handler
	if (!LERROR_HAS_FATAL(err))
		err |= m_myEventManager.RemoveHandler(eGameEventType::GameEvent_pause, &m_myEventHandler);

	// Remove the banana from the renderer
	if (!LERROR_HAS_FATAL(err))
		err |= GetRenderer()->RemoveRenderable(&m_banana);

	if (!LERROR_HAS_FATAL(err))
		err |= m_myEventManager.Destroy();

	err |= LGameBase::Destroy();

 	return err;
}

//========================================================
LError GameOne::HandleEvent(const TGameEventManager::TEvent* event)
{
	// do stuff to handle the events

	return LError::NoErr;
}
