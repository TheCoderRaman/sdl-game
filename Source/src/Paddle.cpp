//! \file GameOne.cpp
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Main game class, responsible for managing all game specific stuff
//!
#include "Paddle.h"

#include "LError.h"
#include "debug.h"

LError Paddle::Create( void )
{
	RUNTIME_LOG( "Creating Banana..." );

	LError err = LError::NoErr;

	// Must have renderer before creating the sprite
	DEBUG_ASSERT(GetRenderer());

	// Create the banana
	err |= GetSprite()->Create( *GetRenderer(), "Media/paddle.png" );

	// Set up the banana
	GetSprite()->SetSourceRect( { 0, 0, 255, 42 } );
	GetSprite()->SetSize( 255, 42 );
	GetSprite()->SetPos( 100, 100 );

	GameSprite::Create(); // Adds it to the renderer

	return err;
}


void Paddle::MoveLeft( void )
{
	GetSprite()->SetPos( GetSprite()->GetXPos() - 8, GetSprite()->GetYPos() );
}

void Paddle::MoveRight( void )
{
	GetSprite()->SetPos( GetSprite()->GetXPos() + 8, GetSprite()->GetYPos() );
}

LError Paddle::VOnUpdate( ms elapsed )
{
	//	m_banana.SetPos( m_iTimeElapsed, 100 );

	return LError::NoErr;
}

LError Paddle::Render( LRenderer2D* renderer )
{
	return LError::NoErr;
}

LError Paddle::VOnReset( void )
{ 
	RUNTIME_LOG( "Resetting Banana..." );

	return LError::NoErr;
}

LError Paddle::Destroy( void )
{
	RUNTIME_LOG( "Destroying Banana..." );

	GameSprite::Destroy();

	return LError::NoErr;
}