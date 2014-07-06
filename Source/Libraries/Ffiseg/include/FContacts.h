//! \file FContacts.h
//!
//! \author  Marc Di luzio
//! \date    June 2014
//!
//! Contact manager for Ffiseg
//!
#ifndef _FCONTACTS_H_
#define _FCONTACTS_H_

#include "FCommon.h"

Ffiseg_namespace_start

class FContactListener_internal;

class FContactListener
{
public:
	FContactListener();

	void Create();
	void Destroy();

	~FContactListener();

	inline void* GetInternal();

private:

	void* m_internalListener;

};

inline void* FContactListener::GetInternal()
{
	return m_internalListener;
}

Ffiseg_namespace_end

#endif //_FCONTACTS_H_