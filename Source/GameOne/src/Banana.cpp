//! \file Banana.cpp
//!
//! \author  Owain Davies
//! \date    June 2014
//!
//! A banana
//!
#include "Banana.h"

#include "LError.h"
#include "debug.h"

//====================================================
LError Banana::Create( LRenderer2D* renderer, Ffiseg::FWorld* world /* = nullptr */ )
{
	RUNTIME_LOG( "Creating Banana..." );

	LError err = LError::NoErr;

	SetRenderer( renderer );

	// Must have renderer before creating the sprite
	DEBUG_ASSERT(GetRenderer());

	// Create the banana
	err |= GetSprite()->Create( *GetRenderer(), "Media/banana.png" );

	int x = 200;
	int y = 300;
	int w = 50;
	int h = 38;

	// Set up the banana
	GetSprite()->SetSourceRect( { 0, 0, 400, 300 } );
	GetSprite()->SetSize( w, h );
	GetSprite()->SetPos( x, y );

	GameSprite::Create(); // Adds it to the renderer

	if ( world )
	{
		GameSprite::CreatePhysicsBody( world, x, y, w, h );
	}

	return err;
}

//====================================================
LError Banana::VOnUpdate( ms elapsed )
{
	return GameSprite::VOnUpdate(elapsed);
}

//====================================================
LError Banana::Render( LRenderer2D* renderer )
{
	return LError::NoErr;
}

//====================================================
LError Banana::VOnReset(void)
{ 
	RUNTIME_LOG( "Resetting Banana..." );

	return GameSprite::VOnReset();
}

//====================================================
LError Banana::Destroy( void )
{
	RUNTIME_LOG( "Destroying Banana..." );

	GameSprite::Destroy();

	return LError::NoErr;
}