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
	eError Create(const char* file);

	//! \brief set the source rectangle from the texture
	eError SetSourceRect(SDLInterface::Rect rect);

	//! \brief set the sprite position
	eError SetPos(int x, int y);

	//! \brief set the sprite size
	eError SetSize(int x, int y);

	//! \brief Overload for the base type render function
	virtual eError Render(SDLInterface::Renderer& renderer);

private:

	//! \brief the underlying texture 
	SDLInterface::Texture m_Texture;

	//! \brief the source rectangle within the texture
	SDLInterface::Rect m_srcRect;

	//! \brief the destination rectangle on screen
	SDLInterface::Rect m_destRect;

};

#endif //_LSPRITE_H_