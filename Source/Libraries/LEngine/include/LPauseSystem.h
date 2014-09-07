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

template < typename T > 
class LPauseSystem
{
public:

	typedef T TFlags;

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


//===============================================================
template < typename T >
LPauseSystem< T >::LPauseSystem()
	: m_currentFlags(0)
	, m_nextFlags(0)
{

}

//===============================================================
template < typename T >
LPauseSystem< T >::~LPauseSystem()
{

}

//===============================================================
template < typename T >
int LPauseSystem< T >::GetCurrentFlags() const
{
	return m_currentFlags;
}

//===============================================================
template < typename T >
void LPauseSystem< T >::AddNextFlag(int flag)
{
	m_nextFlags |= flag;
}

//===============================================================
template < typename T >
void LPauseSystem< T >::AddNextFlags(int flags)
{
	m_nextFlags |= flags;
}

//===============================================================
template < typename T >
void LPauseSystem< T >::RemoveNextFlags(int flags)
{
	m_nextFlags &= ~flags;
}

//===============================================================
template < typename T >
bool LPauseSystem< T >::GetCurrentFlag(int flag) const
{
	return (m_currentFlags & flag) != 0;
}

//===============================================================
template < typename T >
void LPauseSystem< T >::SetNextFlags(int flags)
{
	m_nextFlags = flags;
}

//===============================================================
template < typename T >
void LPauseSystem< T >::FlushNextFlags()
{
	int flags = m_nextFlags;
	m_currentFlags = flags;
}


#endif //_LPAUSESYSTEM_H_
