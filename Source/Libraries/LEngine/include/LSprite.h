//! \file LSprite.h
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Header for LSprite.cpp
//!
#ifndef _LSPRITE_H_
#define _LSPRITE_H_

#include "types.h"
#include "math_types.h"

#include "LRenderer.h"

#include "SDLRect.h"
#include "SDLTexture.h"

//! \brief the Sprite type
//! represents a single sprite
class LSprite 
	: public LRendereable2D
{
public:

	//! \brief default ctor
	LSprite();

	//! \brief default dtor
	~LSprite();

	//! \brief create the sprite from the file
	LError Create(LRenderer2D& renderer, const char* file);

	//! \brief create the sprite from a surface
	LError Create( LRenderer2D& renderer, SDLInterface::Surface* surface );

	//! \brief set the source rectangle from the texture
	LError SetSourceRect(const SDLInterface::Rect& rect);

	//! \brief set this as the reset location eventually
	LError SetResetPos( int x, int y );

	//! \brief set the sprite position
	LError SetPos(int x, int y);

	int GetXPos();

	int GetYPos();

	//! \brief set the sprite size
	LError SetSize(int w, int h);

	//! \brief set the sprite size
	LError SetRotation(float f);

	//! \brief Overload for the base type render function
	virtual LError Render(LRenderer2D* renderer);

	//! \brief create the sprite from the file
	LError Destroy();

	inline Vector2f GetCentre() const 
	{
		return m_centre;
	}

private:

	//! \brief the underlying texture 
	SDLInterface::Texture m_Texture;

	//! \brief the source rectangle within the texture
	SDLInterface::Rect m_srcRect;

	//! \brief the destination rectangle on screen
	SDLInterface::Rect m_destRect;

	//! \brief the centre of the sprite
	Vector2f	m_centre;

	//! \brief the sprite rotation
	float m_rotation;

	//! \brief the filename
	const char* m_pchFileName;

	//! \brief The reset position of this sprite
	int startX;
	int startY;

};

#endif //_LSPRITE_H_