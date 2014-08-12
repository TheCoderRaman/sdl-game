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
#include "LInput.h"

class ScoreGUI
{
public:

	LError Create( void );
	LError Destroy( void );

	void Reset( void );

	void AddPoint( LInput::ePlayers player );
	void SetText( const char* strText );
	
	void UpdateText();

private:

	LTextSprite m_playerOne;
	LTextSprite m_playerTwo;

	int iPlayerOneScore;
	int iPlayerTwoScore;

};

#endif