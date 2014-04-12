#ifndef _TYPES_H_
#define _TYPES_H_

#include "stdio.h"

// Defines
#define DEBUG_LOGGING 1

// Types
enum eError {
	eError_noErr = 0,
	eError_quitRequested,
	eError_SDL_Error
};

// Macros
#if DEBUG_LOGGING
	#define DEBUG_LOG(...) \
		fprintf(stderr,__VA_ARGS__);
#else
	#define DEBUG_LOG(...) 
#endif

#endif //_TYPES_H_