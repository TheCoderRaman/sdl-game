//! \file SDLAudio.cpp
//!
//! \author  Owain Davies
//! \date    May 2014
//!
//! This holds the interface between SDL Audio and LEngine audio systems
//!	

#include "SDL_mixer.h"
#include <stdint.h>

#include "SDLAudio.h"
#include "debug.h"

//====================================================
//   Audio Interface
//====================================================
SDLInterface::Audio::Audio()
{
	if( -1 == Mix_OpenAudio( MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024 ) )
	{
		DEBUG_LOG( "Opening audio channel errors: %s", Mix_GetError() );
	}
	else
	{
		DEBUG_LOG( "Opened an audio channel correctly" );
	}

	if( -1 == Mix_Init( MIX_INIT_FLAC | MIX_INIT_MP3 | MIX_INIT_OGG ) )
	{
		DEBUG_LOG( "Initialising errors: %s", Mix_GetError() );
	}
	else
	{
		DEBUG_LOG( "Initialised mixer correctly" );
	}
}

//====================================================
SDLInterface::Audio::~Audio()
{
	Mix_CloseAudio();
}

//====================================================
SDLInterface::SDLMusicFile SDLInterface::Audio::LoadMusic( const char* filename )
{
	SDLInterface::SDLMusicFile toReturn;

	toReturn.SetMusic( Mix_LoadMUS( filename ) );

	if( toReturn.GetMusic() == NULL )
	{
		DEBUG_LOG( "Can't load that music because: %s", Mix_GetError() );
	}

	return toReturn;
}

//====================================================
void SDLInterface::Audio::PlayMusic( SDLInterface::SDLMusicFile music, bool bLoops )
{
	int loops = 0;

	if( bLoops )
	{
		loops = -1;
	}

	if( Mix_PlayingMusic() == 0 )
	{
		//Play the music
		if( -1 == Mix_PlayMusic( music.GetMusic(), loops ) )
		{
			DEBUG_LOG( "Playing music error: %s", Mix_GetError() );
		}
	}
}

//====================================================
SDLInterface::SDLSoundFile SDLInterface::Audio::LoadSound( const char* filename )
{
	SDLInterface::SDLSoundFile toReturn;

	toReturn.AddSound( Mix_LoadWAV( filename ) );

	if( toReturn.GetSound() == NULL )
	{
		DEBUG_LOG( "Can't load that sound because: %s", Mix_GetError() );
	}

	return toReturn;
}

//====================================================
void SDLInterface::Audio::PlaySound( SDLInterface::SDLSoundFile sound )
{
	int channel = 1;

	if( Mix_Playing( channel ) == 0 )
	{
		//Play the music
		if( -1 == Mix_PlayChannel( channel, sound.GetSound(), 0 ) )
		{
			DEBUG_LOG( "Playing music error: %s", Mix_GetError() );
		}
	}
}

//====================================================
void SDLInterface::Audio::ToggleMusicPause( void )
{
	// If we're unpaused
	if( Mix_PausedMusic() == 0 )
	{
		Mix_PauseMusic(); 
	}
	else // we're paused
	{
		Mix_ResumeMusic();
	}
}

//====================================================
//    Music
//====================================================

void SDLInterface::SDLMusicFile::FreeMusic( void )
{
	Mix_FreeMusic( thisMusic );
	thisMusic = nullptr;
}

//====================================================
void SDLInterface::SDLMusicFile::SetMusic( Mix_Music* file )
{
	thisMusic = file;
}

//====================================================
Mix_Music* SDLInterface::SDLMusicFile::GetMusic( void )
{
	return thisMusic;
}

//====================================================
//    Sound
//====================================================
void SDLInterface::SDLSoundFile::FreeSound( void )
{
	Mix_FreeChunk( thisSound );
	thisSound = nullptr;
}

//====================================================
void SDLInterface::SDLSoundFile::AddSound( Mix_Chunk* file )
{
	thisSound = file;
}

//====================================================
Mix_Chunk* SDLInterface::SDLSoundFile::GetSound( void )
{
	return thisSound;
}