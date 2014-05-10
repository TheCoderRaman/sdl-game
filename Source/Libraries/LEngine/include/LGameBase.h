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


//! \brief Base class for the Game, to be overloaded by the game specific class
class LGameBase
{
public:

	//! \brief Constructor
	LGameBase();
	//! \brief destructor
	~LGameBase();

	//! \brief Virtual methods, all BASE methods must call down into these
	virtual eError Create();
	virtual eError Initialise();
	virtual eError PreUpdate();
	virtual eError Update(ms elapsed);
	virtual eError PostUpdate();
	virtual eError Reset();
	virtual eError Destroy();

	//! \brief get the renderer
	inline LRenderer2D*		GetRenderer();
	inline LObjectManager*	GetObjectManager();

	//! \brief set the renderer
	inline void SetRenderer( LRenderer2D* renderer );
	inline void SetObjectManager( LObjectManager* pObjMan );

protected:


private:

	//! \brief pointer to the renderer
	LRenderer2D*	m_Renderer;
	LObjectManager* m_ObjectManager;

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

void LGameBase::SetRenderer(LRenderer2D* renderer)
{
	m_Renderer = renderer;
}

void LGameBase::SetObjectManager( LObjectManager* pObjMan )
{
	m_ObjectManager = pObjMan;
}

#endif //_LGAMEBASE_H_
