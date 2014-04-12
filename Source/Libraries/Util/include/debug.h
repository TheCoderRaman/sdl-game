#ifndef _DEBUG_H_
#define _DEBUG_H_

#include "stdio.h"

// Defines
#define DEBUG_LOGGING 1

// Macros
#if DEBUG_LOGGING
	#define DEBUG_LOG(...) \
		fprintf(stderr,__VA_ARGS__);
#else
	#define DEBUG_LOG(...) 
#endif

#endif //_DEBUG_H_