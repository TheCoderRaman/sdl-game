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

#include "FShape.h"

using namespace Ffiseg;

//====================================================
LError Banana::Create(Ffiseg::FWorld* world /* = nullptr */)
{
	RUNTIME_LOG( "Creating Banana..." );

	LError err = LError::NoErr;

	// Must have renderer before creating the sprite
	DEBUG_ASSERT(GetRenderer());

	// Create the banana
	err |= GetSprite()->Create( *GetRenderer(), "Media/banana.png" );

	// Set up the banana
	GetSprite()->SetSourceRect( { 0, 0, 400, 300 } );
	GetSprite()->SetSize( 200, 150 );
	GetSprite()->SetPos( 100, 100 );

	GameSprite::Create(); // Adds it to the renderer

	if (world)
	{
		FBodyDef bdef = FBodyDef();
		FFixtureDef fdef = FFixtureDef();
		FPolygonShape shape;
		fdef.shape = &shape;
		shape.SetAsBox(2.0f, 1.5f);

		CreateBody(*world, bdef, fdef);
	}

	return err;
}

//====================================================
LError Banana::VOnUpdate( ms elapsed )
{

	return LError::NoErr;
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

	return LError::NoErr;
}

//====================================================
LError Banana::Destroy( void )
{
	RUNTIME_LOG( "Destroying Banana..." );

	GameSprite::Destroy();

	return LError::NoErr;
}