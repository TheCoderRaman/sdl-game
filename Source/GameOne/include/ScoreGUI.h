//! \file  ScoreGUI.h
//!
//! \author  Owain Davies
//! \date    July 2014
//!
//! This is the class that represents the paddle that will be used in the main Pong game
//!

#ifndef _SCORE_GUI_H_
#define _SCORE_GUI_H_

#include "LError.h"
#include "LTextSprite.h"

class ScoreGUI
{
public:

	LError Create( void );
	LError Destroy( void );

	void SetScore( int iNewScore );
	void SetText( const char* strText );

private:

	LTextSprite m_text;
	LTextSprite m_number;

};

#endif