//! \file SDLAudio.h
//!
//! \author  Owain Davies
//! \date    May 2014
//!
//! Header for SDLAudio.cpp
//!	
#ifndef _SDLAUDIO_H_
#define _SDLAUDIO_H_

#include "SDLCommon.h"


// Forward declare SDL structs
struct SDL_AudioSpec;

// Start the SDLInterface Namespace
namespace SDLInterface
{

	//! \brief an Audio class
	class Audio
	{
	public:

		// Constructor and destructor
		Audio();
		~Audio();

	private:

		//! \brief a test sound
		SDL_AudioSpec* my_sdl_audiospec;
	};
}

#endif //_SDLAUDIO_H_
