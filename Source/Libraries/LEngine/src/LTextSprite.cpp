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
	LEngine::GetTextManager().DrawText( &mySurface, fontName, fontsize, text );

	LError err = LSprite::Create( renderer, &mySurface );

	SetSourceRect( { 0, 0, 100, 150 } );
	SetSize( 100, 150 );

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
