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
LError Paddle::Create( LRenderer2D* renderer, int iXPos, int iYPos, LInput::ePlayers ePlayerInControl, Ffiseg::FWorld* world /*= nullptr*/ )
{
	RUNTIME_LOG( "Creating Paddle..." );

	LError err = LError::NoErr;

	SetRenderer( renderer );

	// Must have renderer before creating the sprite
	DEBUG_ASSERT( GetRenderer() );

	// Create the paddle
	err |= GetSprite()->Create( *GetRenderer(), "Media/paddle.png" );

	int w = 200;
	int h = 30;

	// Set up the paddle
	GetSprite()->SetSourceRect( { 0, 0, 255, 42 } );
	GetSprite()->SetSize( w, h );
	GetSprite()->SetPos( iXPos, iYPos );

	GameSprite::Create(); // Adds it to the renderer

	iBorderAtEdgeOfScreen = 50;
	iDistToMove = 1;

	if( world )
	{
		FBodyDef bdef = FBodyDef();
		bdef.type = FBodyType::Static;
		bdef.position = FFISEG_PIX_TO_WORLD( Point2f( iXPos, iYPos ) );
		bdef.fixedRotation = true;
		bdef.linearDamping = 0.0f;

		FFixtureDef fdef = FFixtureDef();
		fdef.restitution = 0.1f;
		fdef.density = 1.0f;
		fdef.restitution = 1.0f;

		FPolygonShape shape;
		shape.SetAsBox( w * 0.5f / FFISEG_WORLD_TO_PIX_FACTOR, h * 0.5f / FFISEG_WORLD_TO_PIX_FACTOR );

		fdef.shape = &shape;

		CreateBody( *world, bdef, fdef );
	}

	m_myPlayer = ePlayerInControl;

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
	if( LEngine::GetInputManager().GetButtonHeldDown( LInput::eInputType::left, m_myPlayer ) )
	{
		MoveLeft();
	}
	if( LEngine::GetInputManager().GetButtonHeldDown( LInput::eInputType::right, m_myPlayer ) )
	{
		MoveRight();
	}

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