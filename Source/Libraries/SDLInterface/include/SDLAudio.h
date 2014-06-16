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

struct _Mix_Music;
typedef _Mix_Music Mix_Music;

// Start the SDLInterface Namespace
namespace SDLInterface
{
	class SDLMusicFile
	{
	public:
		SDLMusicFile();
		~SDLMusicFile();

		void SetMusic( Mix_Music* file );
		Mix_Music* GetMusic( void );

	private:
		Mix_Music* thisMusic;
	};
	
	//! \brief an Audio class
	class Audio
	{
	public:

		// Constructor and destructor
		Audio();
		~Audio();

		SDLMusicFile LoadMusic( const char* filename );

		void PlayMusic( SDLMusicFile, bool bLoops );
	};
}

#endif //_SDLAUDIO_H_
