//! \file LSprite.h
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//!
#include "LSprite.h"

#include "eError.h"
#include "debug.h"

//===============================================================
LSprite::LSprite()
: m_pchFileName( nullptr )
{

}

//===============================================================
LSprite::~LSprite()
{
	
}

//===============================================================
eError LSprite::Create(LRenderer2D& renderer, const char* file)
{
	eError err = eError::NoErr;

	// Sanity check to make sure we don't create twice
	DEBUG_ASSERT(m_pchFileName == nullptr);

	// Set the internal filename
	m_pchFileName = file;

	// Create the texture
	err |= m_Texture.Create(&renderer.GetBaseRenderer(), file);

	return err;
}

//===============================================================
eError LSprite::SetSourceRect(const SDLInterface::Rect& rect)
{
	eError err = eError::NoErr;

	// Set the internal rectangle
	m_srcRect = rect;

	return err;
}

//===============================================================
eError LSprite::SetPos(int x, int y)
{
	eError err = eError::NoErr;

	// set the destination position
	m_destRect.x = x;
	m_destRect.y = y;

	return err;
}

//===============================================================
eError LSprite::SetSize(int w, int h)
{
	eError err = eError::NoErr;

	// Set the destination sizes
	m_destRect.w = w;
	m_destRect.h = h;

	return err;
}

//===============================================================
eError LSprite::Render(SDLInterface::Renderer& renderer)
{
	eError err = eError::NoErr;

	// Render the texture
	err |= renderer.RenderTexture(&m_Texture, m_srcRect, m_destRect);

	return err;
}

//===============================================================
eError LSprite::Destroy()
{
	eError err = eError::NoErr;

	// Destroy the texture
	err |= m_Texture.Destroy();
		
	return err;
}