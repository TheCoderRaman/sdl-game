//! \file LObject.h
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Header for LObject.cpp
//!
#ifndef _LOBJECT_H_
#define _LOBJECT_H_

#include "types.h"

//! \brief Base LObject interface type
//! Designed as a base type for all LEngine parts
//! Allows similarity of interface
class LObject 
{
public:

	//! \brief Create the LObject
	//! Memory should be allocated here 
	//! Contructor simply for POD
	virtual LError Create() = 0;

	//! \brief Initialise the LObject
	//! Set object into it's initial state
	virtual LError Initialise() = 0;

	//! \brief Update the LObject's state
	//! To be used to update the object
	//! Not nessasarily once per frame or on a timestamp
	virtual LError Update(ms elapsed) = 0;

	//! \brief Reset the object
	//! Should the LObject back in it's original state
	virtual LError Reset() = 0;

	//! \brief Destroy the object 
	//! Should de-allocate all memory
	//! And perform needed LError checking
	virtual LError Destroy() = 0;
};

#endif //_LOBJECT_H_