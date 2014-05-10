//! \file GameOne.cpp
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Main game class, responsible for managing all game specific stuff
//!
#include "GameOne.h"

#include "LObjectManager.h"

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


	// Create the banana
	if (!ERROR_HAS_TYPE_FATAL(err))
		err |= m_banana.Create(*GetRenderer(), "Media/banana.png");

	// Set up the banana
	m_banana.SetSourceRect({ 0, 0, 400, 300 });
	m_banana.SetSize(400,300);
	m_banana.SetPos(100,100);

	// Add said banana to the renderer
	if (!ERROR_HAS_TYPE_FATAL(err))
		err |= GetRenderer()->AddRenderable(&m_banana);

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

	// Remove the banana from the renderer
	if (!ERROR_HAS_TYPE_FATAL(err))
		err |= GetRenderer()->RemoveRenderable(&m_banana);

	// Destroy the banana
	if (!ERROR_HAS_TYPE_FATAL(err))
		err |= m_banana.Destroy();


	err |= LGameBase::Destroy();

 	return err;
}