//! \file SDLAudio.cpp
//!
//! \author  Owain Davies
//! \date    May 2014
//!
//! This holds the interface between SDL Audio and LEngine audio systems
//!	

#include "SDLAudio.h"
#include "debug.h"

#include "SDL.h"

void fill_audio( void* userData, Uint8* stream, int length );

void fill_audio( void* userData, Uint8* stream, int length )
{

}

SDLInterface::Audio::Audio()
{
	my_sdl_audiospec = new SDL_AudioSpec();

	my_sdl_audiospec->freq		= 22050;
	my_sdl_audiospec->format	= AUDIO_S16;
	my_sdl_audiospec->channels	= 2;    /* 1 = mono, 2 = stereo */
	my_sdl_audiospec->samples	= 1024;  /* Good low-latency value for callback */
	my_sdl_audiospec->callback	= fill_audio;
	my_sdl_audiospec->userdata	= NULL;

	if( SDL_OpenAudio( my_sdl_audiospec, NULL ) < 0 )
	{
		DEBUG_LOG( "Gah!" );
	}
	else
	{
		DEBUG_LOG( "Whee!" );
	}

}

SDLInterface::Audio::~Audio()
{

}