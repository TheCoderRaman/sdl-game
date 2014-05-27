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

#include "LError.h"

class Banana : public LObject, public LRendereable2D
{

public:

	virtual LError Create( void );

	virtual LError Update( ms elapsed );

	virtual LError Reset( void );

	virtual LError Destroy( void );

	virtual LError Render( LRenderer2D* renderer );

	void MoveBananaUpAFrame();
	void MoveBananaLeftAFrame();
	void MoveBananaRightAFrame();
	void MoveBananaDownAFrame();

	void SetPos( int x, int y );

private:

	//! \brief The Banana
	LSprite		m_banana;

	int			m_iTimeElapsed;
};