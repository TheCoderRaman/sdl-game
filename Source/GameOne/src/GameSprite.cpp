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
void GameSprite::SetPos( int x, int y )
{
	m_sprite.SetPos( x, y );
}

//====================================================
LError GameSprite::VOnUpdate( ms elapsed )
{
	Vector2f pos = GetBody()->GetPos();
	pos = FFISEG_WORLD_TO_PIX(pos);

	Vector2f centre = GetSprite()->GetCentre();
	GetSprite()->SetPos( (float)(pos.x - centre.x), (float)(pos.y + centre.y));

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
	m_rigidBody.Create(&world, bdef);
	m_rigidBody.CreateFixture(fdef);
}