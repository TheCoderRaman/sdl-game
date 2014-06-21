//! \file  Paddle.h
//!
//! \author  Owain Davies
//! \date    June 2014
//!
//! This is the class that represents the paddle that will be used in the main Pong game
//!

#ifndef _PADDLE_H_
#define _PADDLE_H_

#include "GameSprite.h"

#include "LError.h"

class Paddle : public GameSprite
{
public:

	LError Create( void );
	LError Destroy( void );

	virtual LError Render( LRenderer2D* renderer );

	void MoveLeft();
	void MoveRight();
	bool CanMoveLeft();
	bool CanMoveRight();

private:

	int iDistToMove;
	int iBorderAtEdgeOfScreen;

	virtual LError VOnUpdate(ms elapsed);
	virtual LError VOnReset(void);
};

#endif