//! \file GameOne.cpp
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Main game class, responsible for managing all game specific stuff
//!

#ifndef _GAMESPRITE_H_
#define _GAMESPRITE_H_

#include "LUpdatable.h"
#include "LRenderer.h"
#include "LSprite.h"

#include "LError.h"

class GameSprite : public LUpdatable, public LRendereable2D
{
public:

	virtual LError Create( void );
	virtual LError Destroy( void );

	virtual LError Render( LRenderer2D* renderer );

	void SetPos( int x, int y );

protected:

	LSprite*	GetSprite( void ) { return &m_sprite; }

private:

	virtual LError VOnUpdate( ms elapsed );

	virtual LError VOnReset( void );

	//! \brief The Sprite
	LSprite		m_sprite;
};

#endif