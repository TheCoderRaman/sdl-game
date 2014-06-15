//! \file LPauseSystem.h
//!
//! \author  Marc Di luzio
//! \date    Jun 2014
//!
//! Header for LPauseSystem.cpp
//!
#ifndef _LPAUSESYSTEM_H_
#define _LPAUSESYSTEM_H_

#include <atomic>

//! Enum for pause flags
// Not strongly typed as it's just a flag
enum EPauseFlag
{
	Game		= 0x0001,
	Render		= 0x0002,
	Physics		= 0x0004,
	Audio		= 0x0008,
	Controls	= 0x0010,

	Global		= 0xFFFF
};

class LPauseSystem
{
public:

	//! \brief default constructor
	LPauseSystem();

	//! \brief default destructor
	~LPauseSystem();

	//! \brief set the current flags
	void SetNextFlags(int flags);

	//! \brief Get the current pause flags
	void AddNextFlag(int flag);

	//! \brief Get the current pause flags
	void AddNextFlags(int flags);

	//! \brief Get the current pause flags
	void RemoveNextFlags(int flags);

	//! \brief Get the current pause flags
	int GetCurrentFlags() const;

	//! \brief Get the current pause flags
	bool GetCurrentFlag(int flag) const;

	//! \brief flush the flags
	void FlushNextFlags();

private:

	//! \brief Current pause flags
	std::atomic<int>	m_currentFlags;

	//! \brief Next pause flags
	std::atomic<int>	m_nextFlags;

};

#endif //_LPAUSESYSTEM_H_