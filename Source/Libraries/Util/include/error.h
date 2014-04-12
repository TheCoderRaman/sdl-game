#ifndef _ERROR_H_
#define _ERROR_H_

//! Great explanation on how this can work is here 
//! http://forum.codecall.net/topic/56591-bit-fields-flags-tutorial-with-example/

//! \brief generic Error enum for error handling
enum t_Error
{
// 	Error name					  Error bit value for flags
	eError_noErr 				= 0x00000000,

// Error types
	eError_Type_Fatal			= 0x10000000, 	// Fatal flag

	eError_quitRequested		= 0x00000001,

	eError_SDL_Fatal			= 0x10000002	// Contains Fatal error

};

//! \brief Actual error type, used as a bit flag
typedef int eError;

#endif //_ERROR_H_