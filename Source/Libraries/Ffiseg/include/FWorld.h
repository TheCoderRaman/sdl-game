//! \file FWorld.h
//!
//! \author  Marc Di luzio
//! \date    June 2014
//!
//! Header for FWorld.cpp
//!
#ifndef _FWORLD_H_
#define _FWORLD_H_

#include "FCommon.h"
#include "FContacts.h"

Ffiseg_namespace_start

//! \brief Wrapper for the box 2D world
class FWorld
{
public:

	//! \brief Default ctor
	FWorld();
	~FWorld();

	//! \brief Create the world
	//! \return returns posetive on success
	int Create( Vector2f grav );

	//! \brief Destroy the world
	//! \return returns posetive on success
	int Destroy();

	//! \brief set the simulation
	int Step(float timestep,int velocityIterations,int positionIterations);


	//! \brief get the box2d world
	inline b2World* GetBaseWorldPtr()
	{
		return m_myWorld;
	}

private:

	//! \brief Internal box2d world
	b2World* m_myWorld;

	//! \brief set the contact listener
	void SetContactListener(FContactListener& listener);

	//! \brief the contact listener
	Ffiseg::FContactListener	m_myContactListener;

};

Ffiseg_namespace_end

#endif //_FWORLD_H_