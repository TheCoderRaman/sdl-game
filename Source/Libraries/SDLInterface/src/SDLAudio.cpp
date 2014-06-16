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

SDLInterface::Audio::Audio()
{
	if( -1 == Mix_OpenAudio( MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024 ) )
	{
		DEBUG_LOG( "Opening audio channel errors: %s", Mix_GetError() );
	}

	if( -1 == Mix_Init( MIX_INIT_FLAC | MIX_INIT_MP3 | MIX_INIT_OGG ) )
	{
		DEBUG_LOG( "Initialising errors: %s", Mix_GetError() );
	}
}

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

SDLInterface::Audio::~Audio()
{

}

SDLInterface::SDLMusicFile::SDLMusicFile( void )
: thisMusic( nullptr )
{
}

SDLInterface::SDLMusicFile::~SDLMusicFile( void )
{

}

void SDLInterface::SDLMusicFile::FreeMusic( void )
{
	Mix_FreeMusic( thisMusic );
	thisMusic = nullptr;
}

void SDLInterface::SDLMusicFile::SetMusic( Mix_Music* file )
{
	thisMusic = file;
}

Mix_Music* SDLInterface::SDLMusicFile::GetMusic( void )
{
	return thisMusic;
}

