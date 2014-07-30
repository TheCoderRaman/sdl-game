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
: strMyText( "" )
, bCreated( false )
{
}

//===============================================================
LTextSprite::~LTextSprite()
{

}

//===============================================================
LError LTextSprite::Create( LRenderer2D& renderer, const char* fontName, int fontSize, const char* text )
{
	pMyRenderer = &renderer;
	strMyFontName = fontName;
	iMyFontSize = fontSize;

	strMyText = text;

	ChangeText( strMyText );

	bCreated = true;

	return LError::NoErr;
}

//===============================================================
void LTextSprite::SetText( const char* text )
{
	ChangeText( text );
}

//===============================================================
void LTextSprite::SetText( int iNum )
{
	char buf[ 16 ];

	sprintf_s( buf, "%i", iNum );

	const char* temp = buf;

	ChangeText( temp );
}

//===============================================================
void LTextSprite::ChangeText( const char* text )
{
	strMyText = text;

	if( bCreated )
	{
		Destroy();
	}

	SDLInterface::Rect textureSize;

	LEngine::GetTextManager().DrawText( &mySurface, strMyFontName, iMyFontSize, strMyText, &textureSize );

	LError err = LSprite::Create( *pMyRenderer, &mySurface );

	SetSourceRect( { 0, 0, textureSize.w, textureSize.h } );
	SetSize( textureSize.w, textureSize.h );
}

//===============================================================
LError LTextSprite::Render( LRenderer2D* renderer )
{
	return LSprite::Render( renderer );
}

//===============================================================
LError LTextSprite::Destroy()
{
	mySurface.Destroy();

	return LSprite::Destroy();


}
