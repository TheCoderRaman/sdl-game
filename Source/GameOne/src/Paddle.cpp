//! \file Paddle.cpp
//!
//! \author  Owain Davies
//! \date    June 2014
//!
//! Main class for the paddle object
//!
#include "Paddle.h"

#include "LError.h"
#include "debug.h"

//====================================================
LError Paddle::Create( void )
{
	RUNTIME_LOG( "Creating Paddle..." );

	LError err = LError::NoErr;

	// Must have renderer before creating the sprite
	DEBUG_ASSERT( GetRenderer() );

	// Create the paddle
	err |= GetSprite()->Create( *GetRenderer(), "Media/paddle.png" );

	// Set up the paddle
	GetSprite()->SetSourceRect( { 0, 0, 255, 42 } );
	GetSprite()->SetSize( 255, 42 );
	GetSprite()->SetPos( 100, 100 );

	GameSprite::Create(); // Adds it to the renderer

	return err;
}

//====================================================
void Paddle::MoveLeft( void )
{
	GetSprite()->SetPos( GetSprite()->GetXPos() - 8, GetSprite()->GetYPos() );
}

//====================================================
void Paddle::MoveRight( void )
{
	GetSprite()->SetPos( GetSprite()->GetXPos() + 8, GetSprite()->GetYPos() );
}

//====================================================
LError Paddle::VOnUpdate( ms elapsed )
{
	return LError::NoErr;
}

//====================================================
LError Paddle::Render( LRenderer2D* renderer )
{
	return LError::NoErr;
}

//====================================================
LError Paddle::VOnReset( void )
{ 
	RUNTIME_LOG( "Resetting Paddle..." );

	return LError::NoErr;
}

//====================================================
LError Paddle::Destroy( void )
{
	RUNTIME_LOG( "Destroying Paddle..." );

	GameSprite::Destroy();

	return LError::NoErr;
}