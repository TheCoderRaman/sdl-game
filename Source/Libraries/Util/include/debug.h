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
	#else
		#define DEBUG_LOG(...) \
			do {} while(0);		// To squish warnings	
	#endif
#else 
	#define DEBUG_LOG(...) \
		do {} while(0);		// To squish warnings	
#endif //DEBUG_LOGGING

// GENERAL LOGGING

#if RUNTIME_LOGGING
	#define RUNTIME_LOG(...) \
		_log(__FILE__, __LINE__, __VA_ARGS__);
#else
	#define RUNTIME_LOG(...) \
		do {} while (0);		// To squish warnings	
#endif //DEBUG_LOGGING

// DEBUG ASSERTIONS
#ifdef _DEBUG

	// Ryan talks about how SDL_Assert is amazing, so I may have to use that here...
	// Link : https://plus.google.com/+RyanGordon/posts/KzV6sLdALX7

	// Uses a very cheeky inline assembly code, which works on windows
	// I'll have to find something for gdb if this doesn't work there
	#define DEBUG_ASSERT( condition )											\
		if ( !(condition) )														\
		{																		\
			_log(__FILE__, __LINE__, "ASSERT FAILED: %s", #condition);			\
			__asm int 3															\
		}

#else
	#define DEBUG_ASSERT( condition ) \
				do {} while (0);		// To squish warnings
#endif

//! \brief method to log information to stdout
void _log(const char* file, int line, const char* format , ... );

#endif //_DEBUG_H_