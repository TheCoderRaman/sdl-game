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
// hmmmm
#include "SDLEventHandling.h"

//! \brief Base LInput interface type
//! This will hold what buttons are pressed this frame/last frame
//! Allows similarity of interface
class LInput 
{
public:

	// TODO make this a bitfield for speeds
	enum class eInputType
	{
		// default
		null = 0,

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

		// max
		totalInputTypes
	};

	enum ePlayers
	{
		ePlayer_One = 0,
		ePlayer_Two,
		ePlayer_Three,
		ePlayer_Four,

		ePlayer_MAX
	};

public:

	const int			k_iTotalPlayers;
	
	static const int	sk_iMAX_PLAYERS = 1;
	static const int	sk_iTotalInputs = ( int ) eInputType::totalInputTypes;

private:




	struct sPlayerInputs
	{
		eInputType m_aEMappedKeys[ ( int ) SDLInterface::eSDLKeyInterface::total_keys ];

		bool m_abButtonsPressedThisFrame[ ( int ) eInputType::totalInputTypes ];
		bool m_abButtonsPressedLastFrame[ ( int ) eInputType::totalInputTypes ];
	};

	sPlayerInputs m_aSPlayerInputMappings[ sk_iMAX_PLAYERS ];

public:

	LInput( void );
	~LInput( void );

	void SetPlayerMappings( void );

	void SetDefaultPlayerMappings( void );

	void SetPlayerInputMap( ePlayers ePlayer, SDLInterface::eSDLKeyInterface eInput, eInputType eToMapTo );
	void SetCommonMapping( SDLInterface::eSDLKeyInterface eInput, eInputType eToMapTo );

	void ClearMappings( void );

	// Called at the start of the frame
	void StartKeyboardUpdate( void );

	// Called at the end of the frame to refresh the inputs stored here
	void EndKeyboardUpdate( void );

	// Gets if a button has been pressed this frame but not the last
	bool GetButtonJustPressed( eInputType eButton, ePlayers eWhichPlayer );

	// Gets if the button has been held down over both this frame and the last
	bool GetButtonHeldDown( eInputType eButton, ePlayers eWhichPlayer );

	// Gets if the button was down last frame but not this one
	bool GetButtonJustReleased( eInputType eButton, ePlayers eWhichPlayer );

private:
	void CopyOverAndResetThisFramesValues( void );
	void ClearThisFrameButtonPresses( void );
	void ClearLastFrameButtonPresses( void );
};

#endif //_LOBJECT_H_