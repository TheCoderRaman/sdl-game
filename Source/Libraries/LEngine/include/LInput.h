//! \file LInput.h
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Header for LInput.cpp
//!
#ifndef _LINPUT_H_
#define _LINPUT_H_

#include "types.h"

//! \brief Base LInput interface type
//! This will hold what buttons are pressed this frame/last frame
//! Allows similarity of interface
class LInput 
{
public:

	// TODO make this a bitfield for speeds
	enum class eInputType
	{
		// System
		quit,
		pause,

		// Gameplay
		up,
		down,
		left,
		right,
		jump,
		interact,
		openMenu,

		// Frontend

		closeMenu,
		menuUp,
		menuDown,
		menuLeft,
		menuRight,

		totalInputTypes
	};

public:

	const int			k_iTotalPlayers;
	static const int	sk_iTotalInputs = ( int ) eInputType::totalInputTypes;

private:

	bool m_abButtonsPressedThisFrame[ ( int ) eInputType::totalInputTypes ];
	bool m_abButtonsPressedLastFrame[ ( int ) eInputType::totalInputTypes ];

public:

	LInput( void );
	~LInput( void );

	// Called at the start of the frame
	void StartKeyboardUpdate( void );

	// Called at the end of the frame to refresh the inputs stored here
	void EndKeyboardUpdate( void );

	// Gets if a button has been pressed this frame but not the last
	bool GetButtonJustPressed	( eInputType eButton );

	// Gets if the button has been held down over both this frame and the last
	bool GetButtonHeldDown		( eInputType eButton );

	// Gets if the button was down last frame but not this one
	bool GetButtonJustReleased	( eInputType eButton );

private:
	void CopyOverAndResetThisFramesValues( void );
	void ClearThisFrameButtonPresses( void );
	void ClearLastFrameButtonPresses( void );
};

#endif //_LOBJECT_H_