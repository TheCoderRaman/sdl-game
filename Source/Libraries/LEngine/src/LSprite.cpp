//! \file LSprite.h
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//!
#include "LSprite.h"
#include "SDLError.h"

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
	// Sanity check to make sure we don't create twice
	DEBUG_ASSERT(m_pchFileName == nullptr);

	// Set the internal filename
	m_pchFileName = file;

	// Create the texture
	SDLInterface::Error sdlerr = m_Texture.Create(&renderer.GetBaseRenderer(), file);

	return SDL_ERROR_HAS_TYPE_FATAL(sdlerr) ? eError::Type_Fatal : eError::NoErr;;
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
eError LSprite::SetResetPos( int x, int y )
{
	eError err = eError::NoErr;

	startX = x;
	startY = y;

	m_destRect.x = x;
	m_destRect.y = y;

	return err;
}

//===============================================================
int LSprite::GetXPos()
{
	return m_destRect.x;
}

//===============================================================
int LSprite::GetYPos()
{
	return m_destRect.y;
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
eError LSprite::Render(LRenderer2D* renderer)
{
	// Render the texture
	SDLInterface::Error err = renderer->GetBaseRenderer().RenderTexture(&m_Texture, m_srcRect, m_destRect);

	return SDL_ERROR_HAS_TYPE_FATAL(err) ? eError::Type_Fatal : eError::NoErr;
}

//===============================================================
eError LSprite::Destroy()
{
	// Destroy the texture
	SDLInterface::Error err = m_Texture.Destroy();
		
	return SDL_ERROR_HAS_TYPE_FATAL(err) ? eError::Type_Fatal : eError::NoErr;
}