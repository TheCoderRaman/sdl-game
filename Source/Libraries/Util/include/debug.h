//! \file debug.h
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Contains various types helpful debug methods
//!
#ifndef _DEBUG_H_
#define _DEBUG_H_

// Defines
#define RUNTIME_LOGGING 1

// DEBUG LOGGING
#ifdef _DEBUG
	#if RUNTIME_LOGGING
		#define DEBUG_LOG(...) \
			_log(__FILE__, __LINE__, __VA_ARGS__);
	#endif
#else 
	#define DEBUG_LOG(...) \
		do {} while(0);		// To squish warnings	
#endif //DEBUG_LOGGING

// GENERAL LOGGING

#if RUNTIME_LOGGING
	#define RUNTIME_LOG(...) \
		_log(__FILE__, __LINE__, __VA_ARGS__);
#endif //DEBUG_LOGGING

// DEBUG ASSERTIONS
#ifdef _DEBUG
	#define DEBUG_ASSERT( condition )											\
		if ( !(condition) )														\
			_assert(__FILE__, __LINE__, #condition);							

#else
	#define DEBUG_ASSERT( condition ) \
				do {} while (0);		// To squish warnings
#endif


void _log(const char* file, int line, const char* format , ... );
void _assert(const char* file, int line, const char* format );

#endif //_DEBUG_H_