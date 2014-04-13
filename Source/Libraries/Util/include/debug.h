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
#define DEBUG_LOGGING 1

// Macros
#if !DEBUG_LOGGING
	#define DEBUG_LOG(...) \
			do {} while(0);		// To squish warnings	
#else 
	#define DEBUG_LOG(multiple_args...) \
		_debug_log(__FILE__,__LINE__,multiple_args);
#endif //DEBUG_LOGGING


void _debug_log(const char* file, int line, const char* format , ... );


#endif //_DEBUG_H_