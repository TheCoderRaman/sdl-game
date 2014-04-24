//! \file types.h
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Contains defines for simple global types
//!	Possibly needs refactoring at some point
#ifndef _TYPES_H_
#define _TYPES_H_

//! \brief You can forward declare strongly typed enums!
enum class eError : long;

//! \brief the thread local define
#if defined(WIN32) || defined(_WIN32)
#define THREAD_LOCAL __declspec(thread) 
#else
#define THREAD_LOCAL __thread
#endif

#endif //_TYPES_H_