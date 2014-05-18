//! \file GameOne.cpp
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Main game class, responsible for managing all game specific stuff
//!
#include "GameOne.h"

#include "LObjectManager.h"
#include "LInput.h"

#include "eError.h"

//========================================================
GameOne::GameOne()
{
	// Note, game is lazily initialised, so do nothing non POD here
}

//========================================================
GameOne::~GameOne()
{
	
}

//========================================================
eError GameOne::Create()
{
 	eError err = eError::NoErr;

	err |= LGameBase::Create();

	// Setting up the banana object
	m_banana.SetRenderer( GetRenderer() );
	GetObjectManager()->RegisterObject( &m_banana );

 	return err;
}

//========================================================
eError GameOne::Initialise()
{
 	eError err = eError::NoErr;

	err |= LGameBase::Initialise();

 	return err;
}

//========================================================
eError GameOne::PreUpdate()
{
	eError err = eError::NoErr;

	err |= LGameBase::PreUpdate();

	return err;
}

//========================================================
eError GameOne::Update(ms elapsed)
{
 	eError err = eError::NoErr;

	err |= LGameBase::Update(elapsed);

	if( LGameBase::GetInputManager() )
	{
		if( LGameBase::GetInputManager()->GetButtonJustPressed( LInput::eInputType::up ) )
		{
			m_banana.MoveBananaUpAFrame();
		}
		if( LGameBase::GetInputManager()->GetButtonHeldDown( LInput::eInputType::down ) )
		{
			m_banana.MoveBananaDownAFrame();
		}
		if( LGameBase::GetInputManager()->GetButtonJustPressed( LInput::eInputType::left ) )
		{
			m_banana.MoveBananaLeftAFrame();
		}
		if( LGameBase::GetInputManager()->GetButtonJustPressed( LInput::eInputType::right ) )
		{
			m_banana.MoveBananaRightAFrame();
		}
	}

 	return err;
}

//========================================================
eError GameOne::PostUpdate()
{
	eError err = eError::NoErr;

	err |= LGameBase::PostUpdate();

	return err;
}

//========================================================
eError GameOne::Reset()
{
 	eError err = eError::NoErr;

	err |= LGameBase::Reset();

 	return err;
}

//========================================================
eError GameOne::Destroy()
{
 	eError err = eError::NoErr;

	err |= LGameBase::Destroy();

 	return err;
}