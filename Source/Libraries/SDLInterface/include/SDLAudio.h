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

struct Mix_Chunk;

// Start the SDLInterface Namespace
namespace SDLInterface
{
	class SDLMusicFile
	{
	public:
		void FreeMusic( void );
		void SetMusic( Mix_Music* file );
		Mix_Music* GetMusic( void );

	private:
		Mix_Music* thisMusic;
	};

	class SDLSoundFile
	{
	public:
		void FreeSound( void );
		void AddSound( Mix_Chunk* file );
		Mix_Chunk* GetSound( void );

	private:
		Mix_Chunk* thisSound;
	};
	
	//! \brief an Audio class
	class Audio
	{
	public:

		// Constructor and destructor
		Audio();
		~Audio();

		SDLMusicFile LoadMusic( const char* filename );
		void PlayMusic( SDLMusicFile music, bool bLoops );

		SDLSoundFile LoadSound( const char* filename );
		void PlaySound( SDLSoundFile sound );
	};
}

#endif //_SDLAUDIO_H_
