//! \file ScoreGUI.cpp
//!
//! \author  Owain Davies
//! \date    July 2014
//!
//! Score GUI class
//!
#include "ScoreGUI.h"

#include "LEngine.h"
#include "LError.h"
#include "debug.h"


//====================================================
LError ScoreGUI::Create( void )
{
	RUNTIME_LOG( "Creating ScoreGUI..." );

	LError err = LError::NoErr;

	// A method of picking a default font size, based on some variables
	m_playerOne.Create( LEngine::GetRenderer(), "font1", 50, "123" );
	m_playerTwo.Create( LEngine::GetRenderer(), "font1", 50, "123" );

	// A method of sticking text labels to a corner of the screen
	m_playerOne.SetPos( 660, 475 );
	m_playerTwo.SetPos( 660, 75 );

	LEngine::GetRenderer().AddRenderable( &m_playerOne );
	LEngine::GetRenderer().AddRenderable( &m_playerTwo );

	return err;
}

void ScoreGUI::Reset()
{
	iPlayerOneScore = 0;
	iPlayerTwoScore = 0;

	UpdateText();
}

//====================================================
LError ScoreGUI::Destroy( void )
{
	LEngine::GetRenderer().RemoveRenderable( &m_playerOne );
	LEngine::GetRenderer().RemoveRenderable( &m_playerTwo );

	m_playerOne.Destroy();
	m_playerTwo.Destroy();

	return LError::NoErr;
}

//====================================================
void ScoreGUI::AddPoint( LInput::ePlayers player )
{
	if( player = LInput::ePlayer_One )
	{
		++iPlayerOneScore;
	}
	else if( player = LInput::ePlayer_Two )
	{
		++iPlayerTwoScore;
	}	

	UpdateText();
}

//====================================================
void ScoreGUI::UpdateText( void )
{
	m_playerOne.SetText( iPlayerOneScore );
	m_playerTwo.SetText( iPlayerTwoScore );
}