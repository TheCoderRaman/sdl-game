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

Ffiseg_namespace_start

//! \brief Wrapper for the box 2D world
class FWorld
{
public:

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

	b2World* m_myWorld;

};

Ffiseg_namespace_end

#endif //_FWORLD_H_