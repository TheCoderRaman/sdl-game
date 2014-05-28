//! \file LGameBase.h
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Header for LGameBase.cpp
//!
#ifndef _LGAMEBASE_H_
#define _LGAMEBASE_H_

#include "types.h"
#include "LUpdateLoop.h"
#include "LRenderer.h"
#include "LInput.h"
#include "LError.h"


//! \brief Base class for the Game, to be overloaded by the game specific class
class LGameBase
{
public:

	//! \brief Constructor
	LGameBase();
	//! \brief destructor
	~LGameBase();

	//! public interfact methods
	LError Create();
	LError Reset();

	LError PreUpdate();
	LError Update(ms elapsed);
	LError PostUpdate();

	LError Destroy();

	//! \brief get the renderer
	inline LRenderer2D*		GetRenderer();
	inline LUpdateLoop*		GetObjectManager();
	inline LInput*			GetInputManager();

	//! \brief set the renderer
	inline void SetRenderer( LRenderer2D* renderer );
	inline void SetObjectManager( LUpdateLoop* pObjMan );
	inline void SetInputManager( LInput* pInputManager );

protected:


private:

	virtual LError VOnCreate() = 0;
	virtual LError VOnReset() = 0;
	virtual LError VOnPreUpdate() = 0;
	virtual LError VOnUpdate(ms elapsed) = 0;
	virtual LError VOnPostUpdate() = 0;
	virtual LError VOnDestroy() = 0;

	//! \brief pointer to the renderer
	LRenderer2D*	m_Renderer;
	LUpdateLoop*	m_ObjectManager;
	LInput*			m_InputManager;

};

// Inline functions
inline LRenderer2D* LGameBase::GetRenderer()
{
	return m_Renderer;
}

inline LUpdateLoop* LGameBase::GetObjectManager()
{
	return m_ObjectManager;
}

inline LInput* LGameBase::GetInputManager()
{
	return m_InputManager;
}

void LGameBase::SetRenderer(LRenderer2D* renderer)
{
	m_Renderer = renderer;
}

void LGameBase::SetObjectManager( LUpdateLoop* pObjMan )
{
	m_ObjectManager = pObjMan;
}

void LGameBase::SetInputManager( LInput* pInputManager )
{
	m_InputManager = pInputManager;
}

#endif //_LGAMEBASE_H_
