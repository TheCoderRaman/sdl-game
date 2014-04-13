//! \file error.h
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Contains error handling types and methods
#ifndef _ERROR_H_
#define _ERROR_H_

//! Great explanation on how this can work is here 
//! http://forum.codecall.net/topic/56591-bit-fields-flags-tutorial-with-example/

//! \brief generic Error enum for error handling
enum t_Error
{
// 	Error name					  Error bit value for flags
	eError_noErr 				= 0x00000000,

// 	Error flags                   First two bytes for erro types
	eErrorType_Fatal			= 0x10000000, 	// Fatal flag
    eErrorType_Warning			= 0x20000000, 	// Warning flag

//  Error catagories              3rd and 4th bits for error catagoreis
    eErrorCat_SDL				= 0x00100000, 	// SDL flag

// 	Specific Errors               Last 4 bits for specific errors
	eError_quitRequest			= 0x00000001,

//  Composite Errors
    eError_SDL_Fatal			= 0x10100000	// Contains Fatal error AND SDL catagory

};

//! \brief Actual error type, used as a bit flag
typedef int eError;

//! \brief Check if error is fatal
#define ERRORTYPE_IS_FATAL( err ) 		( err & eErrorType_Fatal 		)
#define ERRORTYPE_IS_WARNING( err ) 	( err & eErrorType_Warning   	)

#define ERRORCAT_IS_SDL( err )			( err & eErrorCat_SDL   	)


#endif //_ERROR_H_
