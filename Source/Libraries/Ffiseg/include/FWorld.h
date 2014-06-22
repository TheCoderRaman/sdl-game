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

namespace Ffiseg
{
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

	private:

		b2World* m_myWorld;

	};
}

#endif //_FWORLD_H_