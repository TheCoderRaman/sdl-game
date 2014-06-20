//! \file 
//!
//! \author  
//! \date    
//!
//! blarg
//!
#include "GameSprite.h"

#include "LError.h"

class Banana : public GameSprite
{

public:

	LError Create( void );
	LError Destroy( void );

	virtual LError Render( LRenderer2D* renderer );

	void MoveBananaUpAFrame();
	void MoveBananaLeftAFrame();
	void MoveBananaRightAFrame();
	void MoveBananaDownAFrame();

private:

	virtual LError VOnUpdate(ms elapsed);

	virtual LError VOnReset(void);
};