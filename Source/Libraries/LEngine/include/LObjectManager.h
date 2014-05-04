//! \file LObjectManager.h
//!
//! \author  Owain Davies
//! \date    May 2014
//!
//! Header for LObjectManager.cpp
//!
#ifndef _LOBJECTMANAGER_H_
#define _LOBJECTMANAGER_H_

#include "types.h"

class LObject;

//! \brief Manages all LObject types
//! Designed as a base type for all LEngine parts
//! Allows similarity of interface
class LObjectManager
{
public:
	
	LObjectManager( void );
	~LObjectManager( void );

	//! \brief Register an object with this manager
	eError RegisterObject( LObject* pObjectToRegister );

	//! \brief Update the LObject's state
	//! To be used to update the object
	//! Not nessasarily once per frame or on a timestamp
	eError Update( ms frameTime );

};

#endif //_LOBJECTMANAGER_H_