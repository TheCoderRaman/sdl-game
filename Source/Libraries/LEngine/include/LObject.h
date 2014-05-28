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
#include "LError.h"

//! \brief type to identify objects by ID
typedef int ObjectID;

//! \brief Base LObject interface type
//! Not currently thread-safe at all
class LObject 
{
public:

	//! \brief Default contructor
	LObject();

	//! \brief Default destructor
	virtual ~LObject();

	//! \brief Update the object to a new state based on a timestamp
	LError Update(ms elapsed);

	//! \brief Reset the object to it's initial state
	LError Reset();

	//! \brief Activate the object
	LError Activate();

	//! \brief De-activate the object
	LError Deactivate();

	//! \brief Check if the object is currently active
	inline bool IsActive();

		//! \brief Check if the object is currently active
	inline ObjectID GetID();

private:

	//! \brief virtual update delegate method to be overloaded
	virtual LError VOnUpdate(ms elapsed);

	//! \brief virtual reset delegate method to be overloaded
	virtual LError VOnReset();

	//! \brief virtual activate delegate method to be overloaded
	virtual LError VOnActivate();

	//! \brief virtual deactivate delegate method to be overloaded
	virtual LError VOnDeactivate();

	//! \brief if the object is currently active
	bool m_bIsActive;

	//! \brief static variable for current object ID
	static ObjectID s_currentObjectID;

	//! \brief the object's unique ID
	ObjectID m_ID;
};

//===============================================================
bool LObject::IsActive()
{
	return m_bIsActive;
}

//===============================================================
ObjectID LObject::GetID()
{
	return m_ID;
}

#endif //_LOBJECT_H_