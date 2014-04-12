#ifndef _ERROR_H_
#define _ERROR_H_

//! \brief generic Error enum for error handling
enum eError 
{
	eError_noErr = 0,
	eError_quitRequested,
	eError_SDL_Error
};

#endif //_ERROR_H_