//! \file LUpdateLoop.h
//!
//! \author  Owain Davies
//! \date    May 2014
//!
//! Header for LUpdateLoop.cpp
//!
#ifndef _LUPDATELOOP_H_
#define _LUPDATELOOP_H_

#include "types.h"
#include <list>

#include "LUpdatable.h"

//! \brief Manages all LUpdatable types
//! Designed as a base type for all LEngine parts
//! Is a subclass of LUpdatable to gain its interface.
//! \Warning Adding and Removing objects WHILE updating them is not currently thread safe
class LUpdateLoop 
	: public LUpdatable
{
public:
	
	//! \brief default constructor for the update loop
	LUpdateLoop( void );

	//! \brief the default destructor
	~LUpdateLoop( void );

	//! \brief Register an updatable with this manager
	LError Register(LUpdatable* pToRegister);

	//! \brief Register an updatable with this manager
	LError UnRegister(LUpdatable* pToRegister);

private:

	//! \brief Override for when the EventLoop is updated
	virtual LError VOnPreUpdate() override;

	//! \brief Override for when the EventLoop is updated
	virtual LError VOnUpdate(ms frameTime) override;

	//! \brief Override for when the EventLoop is updated
	virtual LError VOnPostUpdate() override;


	//! \brief the list of updatables
	std::list< LUpdatable* > m_vecObjects;
};

#endif //_LUPDATELOOP_H_