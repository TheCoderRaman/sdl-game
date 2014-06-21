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
: iBananaDirection( 1 )
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
	m_banana.SetRenderer( &LEngine::GetRenderer() );
	m_banana.Create();
	GetUpdatingList().Register(&m_banana);

	// Set up the paddle
	m_paddle.SetRenderer( &LEngine::GetRenderer() );
	m_paddle.Create();

	GetUpdatingList().Register( &m_paddle );

	LEngine::GetAudioManager().LoadMusic( "Media/music.mp3", "song1" );
	LEngine::GetAudioManager().PlayMusic( "song1", true );

	LEngine::GetAudioManager().LoadSound( "Media/hit.wav", "hit" );

 	return err;
}

//========================================================
LError GameOne::VOnPreUpdate()
{
	LError err = LError::NoErr;

	return err;
}

bool GameOne::ShouldBananaSwitchDirections( void )
{
	bool bReturn = false;

	int iBananaY		= m_banana.GetYPos();
	int iBananaHeight	= m_banana.GetHeight();

	int iBananaX		= m_banana.GetXPos();
	int iBananaWidth	= m_banana.GetWidth();

	int iWindowHeight = LEngine::GetWindowHeight(); // bottom of the screen

	int iPaddleY = m_paddle.GetYPos();
	int iPaddleX = m_paddle.GetXPos();

	int iPaddleWidth = m_paddle.GetWidth();

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
LError GameOne::VOnUpdate(ms elapsed)
{
 	LError err = LError::NoErr;

	if( LEngine::GetInputManager().GetButtonHeldDown( LInput::eInputType::left ) )
	{
		m_paddle.MoveLeft();
	}
	if( LEngine::GetInputManager().GetButtonHeldDown( LInput::eInputType::right ) )
	{
		m_paddle.MoveRight();
	}


	if( ShouldBananaSwitchDirections() )
	{
		iBananaDirection *= -1; // Reverse the banana
		LEngine::GetAudioManager().PlaySound( "hit" );
	}

	int iDistToMoveBanana = 5 * iBananaDirection;

	int iBananaY		= m_banana.GetYPos();

	m_banana.SetPos( m_banana.GetXPos(), iBananaY + iDistToMoveBanana );

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

 	return err;
}

//========================================================
LError GameOne::HandleEvent(const TGameEventManager::TEvent* event)
{
	// do stuff to handle the events

	return LError::NoErr;
}
