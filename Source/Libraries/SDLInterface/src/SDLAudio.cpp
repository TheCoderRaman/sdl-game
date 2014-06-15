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
		DEBUG_LOG( "Errors: %s", Mix_GetError() );
	}

	Mix_Init( MIX_INIT_FLAC | MIX_INIT_MP3 | MIX_INIT_OGG );

	Mix_Music* music;

	music = Mix_LoadMUS( "Media/music.mp3" );

	if( music == NULL )
	{
		DEBUG_LOG( "butts\n" );
	}

	if( Mix_PlayingMusic() == 0 )
	{
		//Play the music
		if( -1 == Mix_PlayMusic( music, -1 ) )
		{
			DEBUG_LOG( "Errors: %s", Mix_GetError() );
		}
	}
}

SDLInterface::Audio::~Audio()
{

}