//! \file GameSprite.h
//!
//! \author  Owain Davies
//! \date    June 2014
//!
//! This class is the basetype for all updating and rendering sprite objects that might
//! be used in the game
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
	int  GetXPos( void ) { return m_sprite.GetXPos(); }
	int	 GetYPos( void ) { return m_sprite.GetYPos(); }

	int GetHeight( void ) { return m_sprite.GetHeight(); }
	int GetWidth( void ) { return m_sprite.GetWidth(); }

protected:

	LSprite*	GetSprite( void ) { return &m_sprite; }

private:

	virtual LError VOnUpdate( ms elapsed );

	virtual LError VOnReset( void );

	//! \brief The Sprite
	LSprite		m_sprite;
};

#endif