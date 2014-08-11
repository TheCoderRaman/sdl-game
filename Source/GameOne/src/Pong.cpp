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
: iBananaDirection( 1 )
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
	m_banana.SetRenderer(&LEngine::GetRenderer());
	m_banana.Create(&m_myWorld);
	GetUpdatingList().Register(&m_banana);

	// Set up the first player's paddle
	m_paddleOne.SetRenderer( &LEngine::GetRenderer() );
	m_paddleOne.Create( 200, 100, LInput::ePlayer_One, &m_myWorld );
	GetUpdatingList().Register( &m_paddleOne );

	// Set up the second player's paddle
	m_paddleTwo.SetRenderer( &LEngine::GetRenderer() );
	m_paddleTwo.Create( 200, 400, LInput::ePlayer_Two, &m_myWorld );
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

bool Pong::ShouldBananaSwitchDirections( void )
{
	bool bReturn = false;

	int iBananaY		= m_banana.GetYPos();
	int iBananaHeight	= m_banana.GetHeight();

	int iBananaX		= m_banana.GetXPos();
	int iBananaWidth	= m_banana.GetWidth();

	int iWindowHeight = LEngine::GetWindowHeight(); // bottom of the screen

	int iPaddleY = m_paddleOne.GetYPos();
	int iPaddleX = m_paddleOne.GetXPos();

	int iPaddleWidth = m_paddleOne.GetWidth();

	if( ( iBananaY + iBananaHeight > iPaddleY )
		&& ( iBananaX + iBananaWidth > iPaddleX ) )
	{
		bReturn = true;
	}
	else if( iBananaY + iBananaHeight > iWindowHeight )
	{
		bReturn = true;
	}
	else if( iBananaY < 0 )
	{
		bReturn = true;
	}

	return bReturn;
}

//========================================================
LError Pong::VOnUpdate( ms elapsed )
{
 	LError err = LError::NoErr;

	m_myWorld.Step( elapsed / 1000.0f, 8, 3);

	if( LEngine::GetInputManager().GetButtonJustPressed( LInput::eInputType::jump, LInput::ePlayer_One ) )
	{
		iCurrentScore++;
		m_score.SetScore( iCurrentScore );
	}

	if( ShouldBananaSwitchDirections() )
	{
		iBananaDirection *= -1; // Reverse the banana
	//	LEngine::GetAudioManager().PlaySound( "hit" );
	}

	int iDistToMoveBanana = 5 * iBananaDirection;

	int iBananaY		= m_banana.GetYPos();

//	m_banana.SetPos( m_banana.GetXPos(), iBananaY + iDistToMoveBanana );

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

	iCurrentScore = 0;
	m_score.SetScore( iCurrentScore );

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
