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
	m_text.Create( LEngine::GetRenderer(), "font1", 50, "I like tamale" );
	m_number.Create( LEngine::GetRenderer(), "font1", 50, "123" );

	// A method of sticking text labels to a corner of the screen
	m_text.SetPos( 20, 75 ); 
	m_number.SetPos( 600, 75 );

	LEngine::GetRenderer().AddRenderable( &m_text );
	LEngine::GetRenderer().AddRenderable( &m_number );

	return err;
}


//====================================================
LError ScoreGUI::Destroy( void )
{
	LEngine::GetRenderer().RemoveRenderable( &m_text );
	LEngine::GetRenderer().RemoveRenderable( &m_number );

	m_text.Destroy();
	m_number.Destroy();

	return LError::NoErr;
}

//====================================================
void ScoreGUI::SetScore( int iNewScore )
{
	m_number.SetText( iNewScore );
}

//====================================================
void ScoreGUI::SetText( const char* strText )
{
	m_text.SetText( strText );
}