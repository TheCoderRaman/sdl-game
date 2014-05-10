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
enum class eError : int;

//! \brief all timer methods are in ms (milliseconds)
typedef long ms;

//! \brief the thread local define
#ifdef WINDOWS_BUILD
#define THREAD_LOCAL __declspec(thread) 
#elif defined UNIX_BUILD
#define THREAD_LOCAL __thread
#else
#error "not known platform"
#endif

#endif //_TYPES_H_