//! \file LInput.cpp
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//!
#include "LInput.h"

#include "LError.h"
#include "debug.h"

#include "SDLEventHandling.h"

//===============================================================
LInput::LInput()
: k_iTotalPlayers( 1 )
{
	ClearThisFrameButtonPresses();
	ClearLastFrameButtonPresses();	
}

//===============================================================
LInput::~LInput()
{
	ClearThisFrameButtonPresses();
	ClearLastFrameButtonPresses();
}

void LInput::StartKeyboardUpdate( void )
{
	//RUNTIME_LOG( "Starting keyboard update in LInput" );

	// flush the keys from intermediate states
	SDLInterface::EventHandling::FlushKeys();

	CopyOverAndResetThisFramesValues();
	
	if( SDLInterface::EventHandling::GetKeyPressed( SDLInterface::eSDLKeyInterface::key_up ) )
	{
		m_abButtonsPressedThisFrame[ ( int ) eInputType::up ] = true;
	}
	if( SDLInterface::EventHandling::GetKeyPressed( SDLInterface::eSDLKeyInterface::key_down ) )
	{
		m_abButtonsPressedThisFrame[ ( int ) eInputType::down ] = true;
	}
	if( SDLInterface::EventHandling::GetKeyPressed( SDLInterface::eSDLKeyInterface::key_left ) )
	{
		m_abButtonsPressedThisFrame[ ( int ) eInputType::left ] = true;
	}
	if( SDLInterface::EventHandling::GetKeyPressed( SDLInterface::eSDLKeyInterface::key_right ) )
	{
		m_abButtonsPressedThisFrame[ ( int ) eInputType::right ] = true;
	}
	if (SDLInterface::EventHandling::GetKeyPressed(SDLInterface::eSDLKeyInterface::key_p))
	{
		m_abButtonsPressedThisFrame[(int)eInputType::pause] = true;
	}
	if( SDLInterface::EventHandling::GetKeyPressed( SDLInterface::eSDLKeyInterface::key_space ) )
	{
		m_abButtonsPressedThisFrame[ ( int ) eInputType::jump ] = true;
	}
}

void LInput::EndKeyboardUpdate( void )
{
	//RUNTIME_LOG( "Ending update in LInput" );
}

//================================================================
bool LInput::GetButtonJustPressed( eInputType eButton )
{
	bool bReturn = false;

	int iIndex = ( int ) eButton;

	bReturn = m_abButtonsPressedThisFrame[ iIndex ] && !m_abButtonsPressedLastFrame[ iIndex ];

	//RUNTIME_LOG( "Button just pressed returning %i for input %i", ( int ) bReturn, iIndex );

	return bReturn;
}

//================================================================
bool LInput::GetButtonHeldDown( eInputType eButton )
{
	bool bReturn = false;

	int iIndex = ( int ) eButton;

	bReturn = m_abButtonsPressedThisFrame[ iIndex ] && m_abButtonsPressedLastFrame[ iIndex ];

	//RUNTIME_LOG( "Button held down returning %i for input %i", ( int ) bReturn, iIndex );

	return bReturn;
}

//================================================================
bool LInput::GetButtonJustReleased( eInputType eButton )
{
	bool bReturn = false;

	int iIndex = ( int ) eButton;

	bReturn = !m_abButtonsPressedThisFrame[ iIndex ] && m_abButtonsPressedLastFrame[ iIndex ];

	return bReturn;
}

//================================================================
void LInput::CopyOverAndResetThisFramesValues( void )
{
	for( int iLoop = 0; iLoop < sk_iTotalInputs; ++iLoop )
	{
		// Copy the value over
		m_abButtonsPressedLastFrame[ iLoop ] = m_abButtonsPressedThisFrame[ iLoop ];

		// Reset the value for this frame
		m_abButtonsPressedThisFrame[ iLoop ] = false;
	} 
}

//================================================================
void LInput::ClearThisFrameButtonPresses( void )
{
	for( auto& bVal : m_abButtonsPressedThisFrame )
	{
		bVal = false;
	}
}

//================================================================
void LInput::ClearLastFrameButtonPresses( void )
{
	for( auto& bVal : m_abButtonsPressedLastFrame )
	{
		bVal = false;
	}
}

