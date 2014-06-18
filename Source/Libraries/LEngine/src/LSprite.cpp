//! \file LSprite.h
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//!
#include "LSprite.h"
#include "SDLError.h"

#include "LError.h"
#include "debug.h"

//===============================================================
LSprite::LSprite()
: m_pchFileName( nullptr )
, m_rotation( 0.0f )
{

}

//===============================================================
LSprite::~LSprite()
{
	
}

//===============================================================
LError LSprite::Create(LRenderer2D& renderer, const char* file)
{
	// Sanity check to make sure we don't create twice
	DEBUG_ASSERT(m_pchFileName == nullptr);

	// Set the internal filename
	m_pchFileName = file;

	// Create the texture
	SDLInterface::Error sdlerr = m_Texture.Create(&renderer.GetBaseRenderer(), file);

	return SDL_ERROR_HAS_FATAL(sdlerr) ? LError::Fatal : LError::NoErr;;
}

//===============================================================
LError LSprite::SetSourceRect(const SDLInterface::Rect& rect)
{
	LError err = LError::NoErr;

	// Set the internal rectangle
	m_srcRect = rect;

	// Set the internal rotational centre
	m_rotCentre = { rect.w, rect.h };

	return err;
}



//===============================================================
LError LSprite::SetPos(int x, int y)
{
	LError err = LError::NoErr;

	// set the destination position
	m_destRect.x = x;
	m_destRect.y = y;

	return err;
}

//===============================================================
LError LSprite::SetRotation(float f)
{
	LError err = LError::NoErr;

	// set the destination position
	m_rotation = f;

	return err;
}


//===============================================================
LError LSprite::SetResetPos( int x, int y )
{
	LError err = LError::NoErr;

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
LError LSprite::SetSize(int w, int h)
{
	LError err = LError::NoErr;

	// Set the destination sizes
	m_destRect.w = w;
	m_destRect.h = h;

	return err;
}

//===============================================================
LError LSprite::Render(LRenderer2D* renderer)
{
	// Render the texture
	SDLInterface::Error err = renderer->GetBaseRenderer().RenderTexture(&m_Texture, m_srcRect, m_destRect, m_rotation, m_rotCentre, 0);

	return SDL_ERROR_HAS_FATAL(err) ? LError::Fatal : LError::NoErr;
}

//===============================================================
LError LSprite::Destroy()
{
	// Destroy the texture
	SDLInterface::Error err = m_Texture.Destroy();
		
	return SDL_ERROR_HAS_FATAL(err) ? LError::Fatal : LError::NoErr;
}