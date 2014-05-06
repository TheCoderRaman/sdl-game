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
#include <vector>

#include "LObject.h"

//! \brief Manages all LObject types
//! Designed as a base type for all LEngine parts
//! Is a subclass of LObject to gain its interface.
class LObjectManager : public LObject
{
public:
	
	LObjectManager( void );
	~LObjectManager( void );

	//! \brief Register an object with this manager
	eError RegisterObject( LObject* pObjectToRegister );

	eError Create( void );

	eError Initialise( void );

	//! \brief Update the LObject's state
	//! To be used to update the object
	//! Not nessasarily once per frame or on a timestamp
	eError Update( ms frameTime );

	eError Reset( void );

	eError Destroy( void );

private:

	const int mk_iMaxObjects = 256;

	std::vector< LObject* > m_vecObjects;
};

#endif //_LOBJECTMANAGER_H_