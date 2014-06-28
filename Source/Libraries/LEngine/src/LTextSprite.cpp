//! \file LTextSprite.cpp
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//!
#include "LTextSprite.h"
#include "SDLError.h"
#include "LEngine.h"

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
	SDLInterface::Surface* tempSurf = LEngine::GetTextManager().DrawText( fontName, fontsize, text );

	LError err = LSprite::Create( renderer, tempSurf );

	SetSourceRect( { 0, 0, 100, 150 } );
	SetSize( 100, 150 );

	return err;
}

//===============================================================
LError LTextSprite::Render( LRenderer2D* renderer )
{
	return LSprite::Render( renderer );
}
