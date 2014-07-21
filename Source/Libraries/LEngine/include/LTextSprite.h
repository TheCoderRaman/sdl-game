//! \file LSprite.h
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Header for LSprite.cpp
//!
#ifndef _LTEXTSPRITE_H_
#define _LTEXTSPRITE_H_

#include "types.h"

#include "LRenderer.h"
#include "LSprite.h"
#include "LText.h"


#include "SDLRect.h"
#include "SDLTexture.h"
#include "SDLSurface.h"

//! \brief the Sprite type
//! represents a single sprite
class LTextSprite 
	: public LSprite
{
public:

	//! \brief default ctor
	LTextSprite();

	//! \brief default dtor
	~LTextSprite();

	LError Create( LRenderer2D& renderer, const char* fontName, int fontsize, const char* text );
	void SetText( const char* newText );

	//! \brief Overload for the base type render function
	virtual LError Render( LRenderer2D* renderer );

	virtual LError Destroy();

private:
	void ChangeText( const char* text );

	const char*				strMyText;
	SDLInterface::Surface	mySurface;
	LRenderer2D*			pMyRenderer;
	const char*				strMyFontName;
	int						iMyFontSize;
	bool					bCreated;
};

#endif //_LTEXTSPRITE_H_