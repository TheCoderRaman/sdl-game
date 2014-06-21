//! \file Paddle.cpp
//!
//! \author  Owain Davies
//! \date    June 2014
//!
//! Main class for the paddle object
//!
#include "Paddle.h"

#include "LEngine.h"
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
	GetSprite()->SetPos( ( LEngine::GetWindowWidth() / 2 ) - ( GetWidth() / 2 ), 400 );

	GameSprite::Create(); // Adds it to the renderer

	iDistToMove				= 8;
	iBorderAtEdgeOfScreen	= 50;

	return err;
}

//====================================================
void Paddle::MoveLeft( void )
{
	if( CanMoveLeft() )
	{
		SetPos( GetXPos() - iDistToMove, GetYPos() );
	}
}

//====================================================
void Paddle::MoveRight( void )
{
	if( CanMoveRight() )
	{
		SetPos( GetXPos() + iDistToMove, GetYPos() );
	}
}

//====================================================
bool Paddle::CanMoveLeft( void )
{
	bool bReturn = false;

	int x		= GetXPos();
	int minXVal = iBorderAtEdgeOfScreen;

	if( x > minXVal )
	{
		bReturn = true;
	}

	return bReturn;
}

//====================================================
bool Paddle::CanMoveRight( void )
{
	bool bReturn = false;

	int x		= GetXPos() + GetWidth();
	int maxXVal = LEngine::GetWindowWidth() - iBorderAtEdgeOfScreen;

	if( x < maxXVal )
	{
		bReturn = true;
	}

	return bReturn;
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