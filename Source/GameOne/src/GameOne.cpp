//! \file GameOne.cpp
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Main game class, responsible for managing all game specific stuff
//!
#include "GameOne.h"

#include "LUpdatingList.h"
#include "LInput.h"
#include "LEngine.h"

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

	m_myWorld.Create(Vector2f( 0.0f, -9.81f ));
	m_myContactListener.Create();
	m_myWorld.SetContactListener(m_myContactListener);

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
	m_banana.SetRenderer(&LEngine::GetRenderer());
	m_banana.Create(&m_myWorld);
	GetUpdatingList().Register(&m_banana);
	// Set up the paddle
	m_paddle.SetRenderer( &LEngine::GetRenderer() );
	m_paddle.Create(&m_myWorld);
	GetUpdatingList().Register( &m_paddle );

	LEngine::GetAudioManager().LoadMusic( "Media/music.mp3", "song1" );
	//LEngine::GetAudioManager().PlayMusic( "song1", true );

	LEngine::GetAudioManager().LoadSound( "Media/hit.wav", "hit" );

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

	m_myWorld.Step(elapsed/1000.0f, 8, 3);

	if( LEngine::GetInputManager().GetButtonHeldDown( LInput::eInputType::left ) )
	{
		m_paddle.MoveLeft();
	}
	if( LEngine::GetInputManager().GetButtonHeldDown( LInput::eInputType::right ) )
	{
		m_paddle.MoveRight();
	}

	if( LEngine::GetInputManager().GetButtonJustPressed( LInput::eInputType::jump ) )
	{
 		LEngine::GetAudioManager().PlaySound( "hit" );
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
	m_paddle.Destroy();

	// Remove the event handler
	if (!LERROR_HAS_FATAL(err))
		err |= m_myEventManager.RemoveHandler(eGameEventType::GameEvent_pause, &m_myEventHandler);

	// Remove the banana from the renderer
	if (!LERROR_HAS_FATAL(err))
		err |= LEngine::GetRenderer().RemoveRenderable(&m_banana);

	if (!LERROR_HAS_FATAL(err))
		err |= m_myEventManager.Destroy();

	m_myContactListener.Destroy();
	m_myWorld.Destroy();

 	return err;
}

//========================================================
LError GameOne::HandleEvent(const TGameEventManager::TEvent* event)
{
	// do stuff to handle the events

	return LError::NoErr;
}
