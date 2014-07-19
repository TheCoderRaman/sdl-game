//! \file LTextSprite.cpp
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//!
#include "LTextSprite.h"
#include "SDLError.h"
#include "LEngine.h"
#include "SDLRect.h"

#include "LError.h"
#include "debug.h"

//===============================================================
LTextSprite::LTextSprite()
{
}

//===============================================================
LTextSprite::~LTextSprite()
{

}

LError LTextSprite::Create( LRenderer2D& renderer, const char* fontName, int fontsize, const char* text )
{
	SDLInterface::Rect textureSize;

	LEngine::GetTextManager().DrawText( &mySurface, fontName, fontsize, text, &textureSize );

	LError err = LSprite::Create( renderer, &mySurface );

	SetSourceRect( { 0, 0, textureSize.w, textureSize.h } );
	SetSize( textureSize.w, textureSize.h );
	SetPos( 100, 100 );

	return err;
}

//===============================================================
LError LTextSprite::Render( LRenderer2D* renderer )
{
	return LSprite::Render( renderer );
}

LError LTextSprite::Destroy()
{
	mySurface.Destroy();

	return LSprite::Destroy();


}
