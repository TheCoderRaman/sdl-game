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

#include "FShape.h"

using namespace Ffiseg;

//====================================================
LError Paddle::Create( int iXPos, int iYPos, Ffiseg::FWorld* world /*= nullptr*/ )
{
	RUNTIME_LOG( "Creating Paddle..." );

	LError err = LError::NoErr;

	// Must have renderer before creating the sprite
	DEBUG_ASSERT( GetRenderer() );

	// Create the paddle
	err |= GetSprite()->Create( *GetRenderer(), "Media/paddle.png" );

	// Set up the paddle
	GetSprite()->SetSourceRect( { 0, 0, 255, 42 } );
	GetSprite()->SetSize(200, 30);
	GetSprite()->SetPos( iXPos, iYPos );
	Vector2f centre = GetSprite()->GetCentre();

	GameSprite::Create(); // Adds it to the renderer

	iBorderAtEdgeOfScreen = 50;
	iDistToMove = 1;

	if (world)
	{
		FBodyDef bdef = FBodyDef();
		bdef.type = FBodyType::Static;
		Point2f pos = FFISEG_PIX_TO_WORLD( Point2f( iXPos, iYPos ) );
		bdef.position = pos;
		bdef.gravityScale = 0.0f;

		FFixtureDef fdef = FFixtureDef();
		fdef.restitution = 0.1f;
		fdef.density = 1000.0f;

		FPolygonShape shape;
		Vector2f box = Vector2f( 200.0f*0.5f / FFISEG_WORLD_TO_PIX_FACTOR, 
								 30.0f*0.5f / FFISEG_WORLD_TO_PIX_FACTOR );
		shape.SetAsBox( box.x, box.y );

		fdef.shape = &shape;

		CreateBody(*world, bdef, fdef);
	}

	return err;
}

//====================================================
void Paddle::MoveLeft( void )
{
	if( CanMoveLeft() )
	{
		Vector2f p = GetBody()->GetPos();
		p.x -= iDistToMove;
		GetBody()->SetPos( p );
	}
}

//====================================================
void Paddle::MoveRight( void )
{
	if( CanMoveRight() )
	{
		Vector2f p = GetBody()->GetPos();
		p.x += iDistToMove;
		GetBody()->SetPos( p );
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