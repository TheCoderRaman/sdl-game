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

#include "FShape.h"

using namespace Ffiseg;

//====================================================
LError Paddle::Create(Ffiseg::FWorld* world /*= nullptr*/)
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

	if (world)
	{
		FBodyDef bdef = FBodyDef();
		bdef.type = FBodyType::Static;
		FFixtureDef fdef = FFixtureDef();
		fdef.restitution = 0.1f;
		fdef.density = 1000.0f;
		FPolygonShape shape;
		fdef.shape = &shape;
		shape.SetAsBox(3.0f, 1.0f);

		CreateBody(*world, bdef, fdef);
		GetBody()->SetPos(FFISEG_PIX_TO_WORLD(Vector2f(100, 200)));
	}

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
	return GameSprite::VOnUpdate(elapsed);
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

	return GameSprite::VOnReset();
}

//====================================================
LError Paddle::Destroy( void )
{
	RUNTIME_LOG( "Destroying Paddle..." );

	GameSprite::Destroy();

	return LError::NoErr;
}