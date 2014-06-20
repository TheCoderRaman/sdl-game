//! \file 
//!
//! \author  
//! \date    
//!
//! blarg
//!
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

private:

	virtual LError VOnUpdate(ms elapsed);

	virtual LError VOnReset(void);
};