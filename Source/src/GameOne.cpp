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

	if( LGameBase::GetInputManager() )
	{
		if( LGameBase::GetInputManager()->GetButtonHeldDown( LInput::eInputType::up ) )
		{
			m_banana.MoveBananaUpAFrame();
		}
		if (LGameBase::GetInputManager()->GetButtonJustPressed(LInput::eInputType::down))
		{
			m_banana.MoveBananaDownAFrame();
		}
	}

	// Send a pause event FOR SOME REASON I DON'T KNOW MAN
	uGameEventData data;
	data.pause.pause_level = 1;
	m_myEventManager.SendEvent(eGameEventType::GameEvent_pause, data);

	// flush the events
	err |= m_myEventManager.FlushEvents();

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

	// Remove the event handler
	if (!ERROR_HAS_TYPE_FATAL(err))
		err |= m_myEventManager.RemoveHandler(eGameEventType::GameEvent_pause, &m_myEventHandler);

	// Remove the banana from the renderer
	if (!ERROR_HAS_TYPE_FATAL(err))
		err |= GetRenderer()->RemoveRenderable(&m_banana);

	// Destroy the banana
	if (!ERROR_HAS_TYPE_FATAL(err))
		err |= m_banana.Destroy();

	if (!ERROR_HAS_TYPE_FATAL(err))
		err |= m_myEventManager.Destroy();

	err |= LGameBase::Destroy();

 	return err;
}

//========================================================
eError GameOne::HandleEvent(const TGameEventManager::TEvent* event)
{
	// do stuff to handle the events

	return eError::NoErr;
}
