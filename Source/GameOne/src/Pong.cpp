//! \file GameOne.cpp
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Main game class, responsible for managing all game specific stuff
//!
#include "Pong.h"

#include "LUpdatingList.h"
#include "LInput.h"
#include "LEngine.h"

#include "LError.h"

//========================================================
Pong::Pong()
{

}

//========================================================
Pong::~Pong()
{
	
}

//========================================================
LError Pong::VOnCreate()
{
 	LError err = LError::NoErr;

	m_myWorld.Create(Vector2f( 0.0f, -9.81f ));

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
	m_banana.Create( &LEngine::GetRenderer(), &m_myWorld );
	GetUpdatingList().Register(&m_banana);

	// Set up the first player's paddle

	m_paddleOne.Create( &LEngine::GetRenderer(), 200, 100, LInput::ePlayer_One, &m_myWorld );
	GetUpdatingList().Register( &m_paddleOne );

	// Set up the second player's paddle
	m_paddleTwo.Create( &LEngine::GetRenderer(), 200, 400, LInput::ePlayer_Two, &m_myWorld );
	GetUpdatingList().Register( &m_paddleTwo );

	LEngine::GetAudioManager().LoadMusic( "Media/music.mp3", "song1" );
	//LEngine::GetAudioManager().PlayMusic( "song1", true );

	LEngine::GetAudioManager().LoadSound( "Media/hit.wav", "hit" );

	// A method of loading a suite of fonts and sizes based on the game
	LEngine::GetTextManager().LoadFont( "Media/font.ttf", "font1", 10 );
	LEngine::GetTextManager().LoadFont( "Media/font.ttf", "font1", 50 );
	LEngine::GetTextManager().LoadFont( "Media/font.ttf", "font1", 72 );

	m_score.Create();

 	return err;
}

//========================================================
LError Pong::VOnPreUpdate()
{
	LError err = LError::NoErr;

	return err;
}


//========================================================
LError Pong::VOnUpdate( ms elapsed )
{
 	LError err = LError::NoErr;

	m_myWorld.Step( elapsed / 1000.0f, 8, 3);

	if( LEngine::GetInputManager().GetButtonJustPressed( LInput::eInputType::jump, LInput::ePlayer_One ) )
	{
		m_score.AddPoint( LInput::ePlayer_One );
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
LError Pong::VOnPostUpdate()
{
	LError err = LError::NoErr;

	return err;
}

//========================================================
LError Pong::VOnReset()
{
 	LError err = LError::NoErr;

	m_banana.SetPos( 200, 350 );

	m_banana.GiveShove( Vector2f( 0.0, 1500.0f ) );

	m_score.Reset();

 	return err;
}

//========================================================
LError Pong::VOnDestroy()
{
 	LError err = LError::NoErr;

	m_banana.Destroy();
	m_paddleOne.Destroy();
	m_paddleTwo.Destroy();

	m_score.Destroy();

	// Remove the event handler
	if (!LERROR_HAS_FATAL(err))
		err |= m_myEventManager.RemoveHandler(eGameEventType::GameEvent_pause, &m_myEventHandler);


	if (!LERROR_HAS_FATAL(err))
		err |= m_myEventManager.Destroy();

	m_myWorld.Destroy();

 	return err;
}

//========================================================
LError Pong::HandleEvent( const TGameEventManager::TEvent* event )
{
	// do stuff to handle the events

	return LError::NoErr;
}
