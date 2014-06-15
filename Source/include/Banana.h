//! \file GameOne.cpp
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Main game class, responsible for managing all game specific stuff
//!
#include "LUpdatable.h"
#include "LRenderer.h"
#include "LSprite.h"

#include "LError.h"

class Banana : public LUpdatable, public LRendereable2D
{

public:

	LError Create(void);
	LError Destroy(void);

	virtual LError Render(LRenderer2D* renderer);

	void MoveBananaUpAFrame();
	void MoveBananaLeftAFrame();
	void MoveBananaRightAFrame();
	void MoveBananaDownAFrame();

	void SetPos( int x, int y );

private:


	virtual LError VOnUpdate(ms elapsed);

	virtual LError VOnReset(void);



	//! \brief The Banana
	LSprite		m_banana;

	int			m_iTimeElapsed;
};