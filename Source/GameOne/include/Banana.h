//! \file 
//!
//! \author  
//! \date    
//!
//! blarg
//!

#ifndef _BANANA_H_
#define _BANANA_H_

#include "GameSprite.h"

#include "LError.h"

class Banana : public GameSprite
{

public:

	LError Create( LRenderer2D* renderer, Ffiseg::FWorld* world = nullptr );
	LError Destroy( void );

	virtual LError Render( LRenderer2D* renderer );

	void GiveShove( Vector2f direction );

private:

	virtual LError VOnUpdate(ms elapsed);

	virtual LError VOnReset(void);
};

#endif