//! \file GameOne.cpp
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Main game class, responsible for managing all game specific stuff
//!
#include "Banana.h"

#include "LError.h"
#include "debug.h"

LError Banana::Create( void )
{
	RUNTIME_LOG( "Creating Banana..." );

	LError err = LError::NoErr;

	// Must have renderer before creating the sprite
	DEBUG_ASSERT(GetRenderer());

	// Create the banana
	err |= GetSprite()->Create( *GetRenderer(), "Media/banana.png" );

	// Set up the banana
	GetSprite()->SetSourceRect( { 0, 0, 400, 300 } );
	GetSprite()->SetSize( 400, 300 );
	GetSprite()->SetPos( 100, 100 );

	GameSprite::Create(); // Adds it to the renderer

	return err;
}

void Banana::MoveBananaDownAFrame( void )
{
	GetSprite()->SetPos( GetSprite()->GetXPos(), GetSprite()->GetYPos() + 20 );
}

void Banana::MoveBananaUpAFrame( void )
{
	GetSprite()->SetPos( GetSprite()->GetXPos(), GetSprite()->GetYPos() - 20 );
}

void Banana::MoveBananaLeftAFrame( void )
{
	GetSprite()->SetPos( GetSprite()->GetXPos() - 20, GetSprite()->GetYPos() );
}

void Banana::MoveBananaRightAFrame( void )
{
	GetSprite()->SetPos( GetSprite()->GetXPos() + 20, GetSprite()->GetYPos() );
}

LError Banana::VOnUpdate( ms elapsed )
{
	//	m_banana.SetPos( m_iTimeElapsed, 100 );

	static int f = 0.0f;
	f += 1.0f;
	GetSprite()->SetRotation( f );

	return LError::NoErr;
}

LError Banana::Render( LRenderer2D* renderer )
{
	return LError::NoErr;
}

LError Banana::VOnReset(void)
{ 
	RUNTIME_LOG( "Resetting Banana..." );

	return LError::NoErr;
}

LError Banana::Destroy( void )
{
	RUNTIME_LOG( "Destroying Banana..." );

	GameSprite::Destroy();

	return LError::NoErr;
}