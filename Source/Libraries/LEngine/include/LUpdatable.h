//! \file LUpdatable.h
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Header for LUpdatable.cpp
//!
#ifndef _LUPDATABLE_H_
#define _LUPDATABLE_H_

#include "types.h"
#include "LError.h"

//! \brief type to identify objects by ID
typedef int ObjectID;

//! \brief enum to track current state
enum class LUpdateableStatus
	: char
{
	Active,
	Inactive
};

//! \brief Base LUpdatable interface type
//! Not currently thread-safe at all
class LUpdatable 
{
public:

	//! \brief Default contructor
	LUpdatable();

	//! \brief Default destructor
	virtual ~LUpdatable();

	//! \brief Update the object to a new state based on a timestamp
	LError Update(ms elapsed);

	//! \brief Reset the object to it's initial state
	LError Reset();

	//! \brief Check if the updatable is currently active
	inline LUpdateableStatus GetCurrentStatus() const;

	//! \brief set the new status of the updatable
	//! \return returns the current state of the object
	inline LUpdateableStatus SetNextStatus(LUpdateableStatus stat);

		//! \brief Check if the object is currently active
	inline ObjectID GetID();

private:

	//! \brief Activate the object
	LError Activate();

	//! \brief De-activate the object
	LError Deactivate();

	//! \brief virtual update delegate method to be overloaded
	virtual LError VOnUpdate(ms elapsed) = 0;

	//! \brief virtual reset delegate method to be overloaded
	virtual LError VOnReset();

	//! \brief virtual activate delegate method to be overloaded
	virtual LError VOnActivate();

	//! \brief virtual deactivate delegate method to be overloaded
	virtual LError VOnDeactivate();

	//! \brief progress the objects status based on requested state
	void ProgressStatus();

	//! \brief if the updatable is currently active
	LUpdateableStatus m_uCurrentStatus;

	//! \brief the status for the updatable to reach
	LUpdateableStatus m_uNextStatus;

	//! \brief static variable for current object ID
	static ObjectID s_updatableID;

	//! \brief the object's unique ID
	ObjectID m_ID;
};

//===============================================================
LUpdateableStatus LUpdatable::GetCurrentStatus() const
{
	return m_uCurrentStatus;
}

//===============================================================
LUpdateableStatus LUpdatable::SetNextStatus(LUpdateableStatus stat)
{
	m_uNextStatus = stat;
	return m_uCurrentStatus;
}


//===============================================================
ObjectID LUpdatable::GetID()
{
	return m_ID;
}

#endif //_LUPDATABLE_H_