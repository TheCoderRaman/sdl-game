#pragma once

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