//! \file LInput.cpp
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//!
#include "LInput.h"

#include "LError.h"
#include "debug.h"

//===============================================================
LInput::LInput()
: k_iTotalPlayers( 1 )
{
	SetPlayerMappings();

	ClearThisFrameButtonPresses();
	ClearLastFrameButtonPresses();	
}

//===============================================================
LInput::~LInput()
{
	ClearThisFrameButtonPresses();
	ClearLastFrameButtonPresses();
}

//===============================================================
void LInput::SetPlayerMappings( void )
{
	// Eventually will allow for custom mappings to come from somewhere (file presumably!)
	ClearMappings();
	SetDefaultPlayerMappings();
}

//===============================================================
void LInput::SetDefaultPlayerMappings( void )
{
	SetPlayerInputMap( ePlayer_One, SDLInterface::eSDLKeyInterface::key_up, eInputType::up );
	SetPlayerInputMap( ePlayer_One, SDLInterface::eSDLKeyInterface::key_down, eInputType::down );
	SetPlayerInputMap( ePlayer_One, SDLInterface::eSDLKeyInterface::key_left, eInputType::left );
	SetPlayerInputMap( ePlayer_One, SDLInterface::eSDLKeyInterface::key_right, eInputType::right );
	SetPlayerInputMap( ePlayer_One, SDLInterface::eSDLKeyInterface::key_space, eInputType::jump );

	SetPlayerInputMap( ePlayer_One, SDLInterface::eSDLKeyInterface::key_w, eInputType::up );
	SetPlayerInputMap( ePlayer_One, SDLInterface::eSDLKeyInterface::key_s, eInputType::down );
	SetPlayerInputMap( ePlayer_One, SDLInterface::eSDLKeyInterface::key_a, eInputType::left );
	SetPlayerInputMap( ePlayer_One, SDLInterface::eSDLKeyInterface::key_d, eInputType::right );

	SetCommonMapping( SDLInterface::eSDLKeyInterface::key_escape, eInputType::quit );
	SetCommonMapping( SDLInterface::eSDLKeyInterface::key_p, eInputType::pause );
}

//===============================================================
void LInput::SetPlayerInputMap( ePlayers ePlayer, SDLInterface::eSDLKeyInterface eInput, eInputType eToMapTo )
{
	m_aSPlayerInputMappings[ ( int ) ePlayer ].m_aEMappedKeys[ ( int ) eInput ] = eToMapTo;
}

//===============================================================
void LInput::SetCommonMapping( SDLInterface::eSDLKeyInterface eInput, eInputType eToMapTo )
{
	for( sPlayerInputs& thisPlayer : m_aSPlayerInputMappings )
	{
		thisPlayer.m_aEMappedKeys[ ( int ) eInput ] = eToMapTo;
	}
}

//===============================================================
void LInput::StartKeyboardUpdate( void )
{
	//RUNTIME_LOG( "Starting keyboard update in LInput" );

	// flush the keys from intermediate states
	SDLInterface::EventHandling::FlushKeys();

	CopyOverAndResetThisFramesValues();

	// For every player
	for( auto& thisPlayer : m_aSPlayerInputMappings )
	{
		// for all their possible raw key inputs
		for( int iKey = 0; iKey < ( int ) SDLInterface::eSDLKeyInterface::key_invalid; ++iKey )
		{
			// if this raw input is pressed
			if( SDLInterface::EventHandling::GetKeyPressed( ( SDLInterface::eSDLKeyInterface ) iKey ) )
			{
				// Get the mapped key
				int iIndex = ( int ) thisPlayer.m_aEMappedKeys[ iKey ];

				// set the mapped key to be true
				thisPlayer.m_abButtonsPressedThisFrame[ iIndex ] = true;
			}
		}
	}
}

void LInput::EndKeyboardUpdate( void )
{
	//RUNTIME_LOG( "Ending update in LInput" );
}

//================================================================
bool LInput::GetButtonJustPressed( eInputType eButton, ePlayers eWhichPlayer )
{
	bool bReturn = false;

	int iIndex = ( int ) eButton;

	bReturn = m_aSPlayerInputMappings[ ( int ) eWhichPlayer ].m_abButtonsPressedThisFrame[ iIndex ]
		&& !m_aSPlayerInputMappings[ ( int ) eWhichPlayer ].m_abButtonsPressedLastFrame[ iIndex ];

	
	return bReturn;
}

//================================================================
bool LInput::GetButtonHeldDown( eInputType eButton, ePlayers eWhichPlayer )
{
	bool bReturn = false;

	int iIndex = ( int ) eButton;

	ePlayers eThisPlayer = ePlayer_One;

	bReturn = m_aSPlayerInputMappings[ ( int ) eThisPlayer ].m_abButtonsPressedThisFrame[ iIndex ]
		&& m_aSPlayerInputMappings[ ( int ) eThisPlayer ].m_abButtonsPressedLastFrame[ iIndex ];

	return bReturn;
}

//================================================================
bool LInput::GetButtonJustReleased( eInputType eButton, ePlayers eWhichPlayer )
{
	bool bReturn = false;

	int iIndex = ( int ) eButton;

	ePlayers eThisPlayer = ePlayer_One;

	bReturn = !m_aSPlayerInputMappings[ ( int ) eThisPlayer ].m_abButtonsPressedThisFrame[ iIndex ]
		&& m_aSPlayerInputMappings[ ( int ) eThisPlayer ].m_abButtonsPressedLastFrame[ iIndex ];

	
	return bReturn;
}

//================================================================
void LInput::CopyOverAndResetThisFramesValues( void )
{
	// For every player
	for( sPlayerInputs& thisPlayer : m_aSPlayerInputMappings )
	{
		for( int iLoop = 0; iLoop < sk_iTotalInputs; ++iLoop )
		{
			// Copy the value over
			thisPlayer.m_abButtonsPressedLastFrame[ iLoop ] = thisPlayer.m_abButtonsPressedThisFrame[ iLoop ];

			// Reset the value for this frame
			thisPlayer.m_abButtonsPressedThisFrame[ iLoop ] = false;
		}
	}
}

//================================================================
void LInput::ClearThisFrameButtonPresses( void )
{
	// For every player
	for( sPlayerInputs& thisPlayer : m_aSPlayerInputMappings )
	{
		for( auto& bVal : thisPlayer.m_abButtonsPressedThisFrame )
		{
			bVal = false;
		}
	}
}

//================================================================
void LInput::ClearLastFrameButtonPresses( void )
{
	// For every player
	for( sPlayerInputs& thisPlayer : m_aSPlayerInputMappings )
	{
		for( auto& bVal : thisPlayer.m_abButtonsPressedLastFrame )
		{
			bVal = false;
		}
	}
}

//================================================================
void LInput::ClearMappings( void )
{
	// For every player
	for( sPlayerInputs& thisPlayer : m_aSPlayerInputMappings )
	{
		for( auto& bVal : thisPlayer.m_aEMappedKeys )
		{
			bVal = eInputType::null;
		}
	}
}

