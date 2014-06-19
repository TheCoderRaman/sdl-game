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
#include "LUpdatingList.h"
#include "LRenderer.h"
#include "LInput.h"
#include "LError.h"


//! \brief Base class for the Game, to be overloaded by the game specific class
class LGameBase
{
public:

	//! \brief Constructor
	LGameBase();

	//! \brief Create the game
	LError Create();

	//! \brief Reset the game to initial state
	LError Reset();

		//! \brief called just before updating
		LError PreUpdate();

		//! \brief update the game state
		LError Update(ms elapsed);

		//! \brief called immediately after updating
		LError PostUpdate();

	//! \brief destroy the game
	LError Destroy();

	//! \brief Destructor
	~LGameBase();

protected:

	//! \brief Get the updatable list
	inline LUpdatingList&	GetUpdatingList();

private:

	//! \brief Method called on creation of the game
	virtual LError VOnCreate() = 0;

	//! \brief Method called upon reseting the game
	virtual LError VOnReset() = 0;

		//! \brief Method called just before an update
		virtual LError VOnPreUpdate() = 0;

		//! \brief Method called to update game state
		virtual LError VOnUpdate(ms elapsed) = 0;

		//! \brief Method called just after game update
		virtual LError VOnPostUpdate() = 0;

	//! \brief Method called on unloading the game
	virtual LError VOnDestroy() = 0;

	//! \brief the game's updating list
	LUpdatingList	m_UpdatingList;

};

//===============================================================
inline LUpdatingList& LGameBase::GetUpdatingList()
{
	return m_UpdatingList;
}

#endif //_LGAMEBASE_H_
