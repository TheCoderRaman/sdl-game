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
#include "LObject.h"
#include "LObjectManager.h"
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

	//! \brief Virtual methods, all BASE methods must call down into these
	virtual LError Create();
	virtual LError Initialise();
	virtual LError PreUpdate();
	virtual LError Update(ms elapsed);
	virtual LError PostUpdate();
	virtual LError Reset();
	virtual LError Destroy();

	//! \brief get the renderer
	inline LRenderer2D*		GetRenderer();
	inline LObjectManager*	GetObjectManager();
	inline LInput*			GetInputManager();

	//! \brief set the renderer
	inline void SetRenderer( LRenderer2D* renderer );
	inline void SetObjectManager( LObjectManager* pObjMan );
	inline void SetInputManager( LInput* pInputManager );

protected:


private:

	//! \brief pointer to the renderer
	LRenderer2D*	m_Renderer;
	LObjectManager* m_ObjectManager;
	LInput*			m_InputManager;

};

// Inline functions
inline LRenderer2D* LGameBase::GetRenderer()
{
	return m_Renderer;
}

inline LObjectManager* LGameBase::GetObjectManager()
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

void LGameBase::SetObjectManager( LObjectManager* pObjMan )
{
	m_ObjectManager = pObjMan;
}

void LGameBase::SetInputManager( LInput* pInputManager )
{
	m_InputManager = pInputManager;
}

#endif //_LGAMEBASE_H_
