//! \file debug.h
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Contains various types helpful debug methods
//!
#ifndef _DEBUG_H_
#define _DEBUG_H_

//! \brief macro definition to turn on runtime logging
#define RUNTIME_LOGGING 1

//! \brief method to log information to stdout
//! Actual debug log method, used to produce the log output
//! \warning never call directly, always call one of the various LOG macros
void _log(const char* file, int line, const char* format, ...);

// DEBUG ONLY LOGGING
#ifdef DEBUG_BUILD
	#if RUNTIME_LOGGING
		//! \brief log text in debug
		#define DEBUG_LOG(...) \
			_log(__FILE__, __LINE__, __VA_ARGS__);	
	#endif
#endif 
#ifndef DEBUG_LOG
	//! \brief log text in debug
	#define DEBUG_LOG(...) \
		do {} while (0);		// To squish warnings	
#endif

// RUNTIME LOGGING
#if RUNTIME_LOGGING
	//! \brief log text in debug and release
	#define RUNTIME_LOG(...) \
		_log(__FILE__, __LINE__, __VA_ARGS__);	
#endif 
#ifndef RUNTIME_LOG
	//! \brief log text in debug and release
	#define RUNTIME_LOG(...) \
		do {} while (0);		// To squish warnings
#endif

// Different debug breakpoints on windows/linux
#ifdef WINDOWS_BUILD
//! \brief use magic inline assembly
// Uses a very cheeky inline assembly code, which works on windows
// I'll have to find something for gdb if this doesn't work there
#define DEBUG_BREAKPOINT __asm int 3
#else
#define DEBUG_BREAKPOINT
#endif

// DEBUG ASSERTIONS
#ifdef DEBUG_BUILD

	// Ryan talks about how SDL_Assert is amazing, so I may have to use that here...
	// Link : https://plus.google.com/+RyanGordon/posts/KzV6sLdALX7

	//! \brief trigger an assert and breakpoint
	#define DEBUG_ASSERT( condition )											\
		if ( !(condition) )														\
		{																		\
			_log(__FILE__, __LINE__, "ASSERT FAILED: %s", #condition);			\
			DEBUG_BREAKPOINT													\
		}

#else
	//! \brief trigger an assert and breakpoint
	#define DEBUG_ASSERT( condition ) \
				do {} while (0);		// To squish warnings
#endif

#endif //_DEBUG_H_