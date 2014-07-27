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
	GetSprite()->SetSize( 100, 75 );
	GetSprite()->SetPos( 200, 300 );

	GameSprite::Create(); // Adds it to the renderer

	if (world)
	{
		FBodyDef bdef = FBodyDef();
		bdef.type = FBodyType::Dynamic;
		bdef.position = FFISEG_PIX_TO_WORLD(Point2f(200, 300));
	//	bdef.gravityScale = 0.0f;

		FFixtureDef fdef = FFixtureDef();
		fdef.restitution = 0.1f;
		fdef.density = 1000.0f;

		FPolygonShape shape;
		shape.SetAsBox(100.0f / FFISEG_WORLD_TO_PIX_FACTOR, 75.0f / FFISEG_WORLD_TO_PIX_FACTOR);

		fdef.shape = &shape;

		CreateBody(*world, bdef, fdef);
	}

	return err;
}

//====================================================
LError Banana::VOnUpdate( ms elapsed )
{
	return GameSprite::VOnUpdate(elapsed);
;
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