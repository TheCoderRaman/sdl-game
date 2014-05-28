//! \file LUpdateLoop.h
//!
//! \author  Owain Davies
//! \date    May 2014
//!
//! Header for LUpdateLoop.cpp
//!
#ifndef _LOBJECTMANAGER_H_
#define _LOBJECTMANAGER_H_

#include "types.h"
#include <vector>

#include "LUpdatable.h"

//! \brief Manages all LUpdatable types
//! Designed as a base type for all LEngine parts
//! Is a subclass of LUpdatable to gain its interface.
class LUpdateLoop
{
public:
	
	LUpdateLoop( void );
	~LUpdateLoop( void );

	//! \brief Register an object with this manager
	LError RegisterObject( LUpdatable* pObjectToRegister );

	//! \brief Update the LUpdatable's state
	//! To be used to update the object
	//! Not nessasarily once per frame or on a timestamp
	LError Update( ms frameTime );

	LError Reset( void );

private:

	const int mk_iMaxObjects = 256;

	std::vector< LUpdatable* > m_vecObjects;
};

#endif //_LOBJECTMANAGER_H_