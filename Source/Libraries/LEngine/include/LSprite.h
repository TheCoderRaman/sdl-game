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
	eError Create(LRenderer2D& renderer, const char* file);

	//! \brief set the source rectangle from the texture
	eError SetSourceRect(const SDLInterface::Rect& rect);

	//! \brief set this as the reset location eventually
	eError SetResetPos( int x, int y );

	//! \brief set the sprite position
	eError SetPos(int x, int y);

	int GetXPos();

	int GetYPos();

	//! \brief set the sprite size
	eError SetSize(int w, int h);

	//! \brief Overload for the base type render function
	virtual eError Render(LRenderer2D* renderer);

	//! \brief create the sprite from the file
	eError Destroy();

private:

	//! \brief the underlying texture 
	SDLInterface::Texture m_Texture;

	//! \brief the source rectangle within the texture
	SDLInterface::Rect m_srcRect;

	//! \brief the destination rectangle on screen
	SDLInterface::Rect m_destRect;

	//! \brief the filename
	const char* m_pchFileName;

	//! \brief The reset position of this sprite
	int startX;
	int startY;

};

#endif //_LSPRITE_H_