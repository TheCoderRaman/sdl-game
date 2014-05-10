//! \file GameOne.cpp
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Main game class, responsible for managing all game specific stuff
//!
#include "LObject.h"
#include "LRenderer.h"
#include "LSprite.h"

#include "eError.h"

class Banana : public LObject, public LRendereable2D
{

public:

	virtual eError Create( void );

	virtual eError Initialise( void );

	virtual eError Update( ms elapsed );

	virtual eError Reset( void );

	virtual eError Destroy( void );

	virtual eError Render( LRenderer2D* renderer );

private:

	//! \brief The Banana
	LSprite					m_banana;
};