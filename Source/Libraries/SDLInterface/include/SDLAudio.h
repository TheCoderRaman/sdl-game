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

// Forward Declaring the structs
struct _Mix_Music;
struct Mix_Chunk;

// Ensuring Mix_Music has the right symbol
typedef _Mix_Music Mix_Music;

// Start the SDLInterface Namespace
namespace SDLInterface
{
	//=====================================
	//! \brief a storage container for a music track
	class SDLMusicFile
	{
	public:
		void FreeMusic( void );
		void SetMusic( Mix_Music* file );
		Mix_Music* GetMusic( void );

	private:
		Mix_Music* thisMusic;
	};

	//=====================================
	//! \brief a storage container for a non-music sound
	class SDLSoundFile
	{
	public:
		void FreeSound( void );
		void AddSound( Mix_Chunk* file );
		Mix_Chunk* GetSound( void );

	private:
		Mix_Chunk* thisSound;
	};
	
	//=====================================
	//! \brief an Audio class
	class Audio
	{
	public:

		Audio( void );
		~Audio( void );

		SDLMusicFile LoadMusic( const char* filename );
		void PlayMusic( SDLMusicFile music, bool bLoops );

		SDLSoundFile LoadSound( const char* filename );
		void PlaySound( SDLSoundFile sound );

		void ToggleMusicPause( void );
	};
}

#endif //_SDLAUDIO_H_
