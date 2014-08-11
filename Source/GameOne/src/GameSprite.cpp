//! \file GameOne.cpp
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Main game class, responsible for managing all game specific stuff
//!
#include "GameSprite.h"

#include "LError.h"
#include "debug.h"

#include "FShape.h"

using namespace Ffiseg;

//====================================================
LError GameSprite::Create( void )
{
	RUNTIME_LOG( "Creating GameSprite..." );

	LError err = LError::NoErr;

	// Adds the sprite to the render loop
	if( !LERROR_HAS_FATAL( err ) )
		err |= GetRenderer()->AddRenderable( GetSprite() );

	return err;
}

//====================================================
void GameSprite::CreatePhysicsBody( Ffiseg::FWorld* world, int x, int y, float w, float h )
{
	FBodyDef bdef = FBodyDef();
	bdef.type = FBodyType::Dynamic;
	bdef.position = FFISEG_PIX_TO_WORLD( Point2f( x, y ) );
	bdef.allowSleep = false;
	bdef.gravityScale = 0.0f;

	FFixtureDef fdef = FFixtureDef();
	fdef.restitution = 0.1f;
	fdef.density = 1000.0f;

	FPolygonShape shape;
	shape.SetAsBox( w / FFISEG_WORLD_TO_PIX_FACTOR, h / FFISEG_WORLD_TO_PIX_FACTOR );

	fdef.shape = &shape;

	CreateBody( *world, bdef, fdef );
}

//====================================================
void GameSprite::SetPos( int x, int y )
{
	m_sprite.SetPos( x, y );
}

//====================================================
LError GameSprite::VOnUpdate( ms elapsed )
{
	Vector2f pos = GetBody()->GetPos();
	pos = FFISEG_WORLD_TO_PIX(pos);

	float rot = GetBody()->GetRot();

	Vector2f centre = GetSprite()->GetCentre();
	GetSprite()->SetPos( (float)(pos.x - centre.x), (float)(pos.y + centre.y));
	GetSprite()->SetRotation(-rot*(360/(2*3.14159f)));


	return LError::NoErr;
}

//====================================================
LError GameSprite::Render( LRenderer2D* renderer )
{
	return LError::NoErr;
}

//====================================================
LError GameSprite::VOnReset( void )
{ 
	RUNTIME_LOG( "Resetting GameSprite..." );

	return LError::NoErr;
}

//====================================================
LError GameSprite::Destroy( void )
{
	RUNTIME_LOG( "Destroying GameSprite..." );

	GetRenderer()->RemoveRenderable( &m_sprite );

	m_sprite.Destroy();

	m_rigidBody.Destroy();

	// Removing our reference to the renderer
	SetRenderer( nullptr );

	return LError::NoErr;
}

//====================================================
void GameSprite::CreateBody(Ffiseg::FWorld& world, Ffiseg::FBodyDef &bdef, Ffiseg::FFixtureDef& fdef)
{
	bdef.userData = this;
	m_rigidBody.Create(&world, bdef);
	m_rigidBody.CreateFixture(fdef);
}