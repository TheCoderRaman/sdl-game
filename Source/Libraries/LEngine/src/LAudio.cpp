//! \file LEngine.cpp
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Description
//! 
#include "LAudio.h"

LAudio::LAudio()
{
	m_musicTracks.reserve( iMAX_MUSIC_TRACKS );
}

LAudio::~LAudio()
{
	for( auto track : m_musicTracks )
	{
		std::get< 0 >( track ).FreeMusic();
	}

	for( auto sound : m_sounds )
	{
		std::get< 0 >( sound ).FreeSound();
	}
}

void LAudio::LoadMusic( const char* filename, const char* name )
{
	SDLInterface::SDLMusicFile thisMusic = m_AudioClass.LoadMusic( filename );

	m_musicTracks.push_back( std::make_tuple( thisMusic, name ) );
}

void LAudio::PlayMusic( const char* name, bool bShouldLoop )
{
	for( auto track : m_musicTracks )
	{
		if( 0 == strcmp( std::get< 1 >( track ), name ) )
		{
			m_AudioClass.PlayMusic( std::get< 0 >( track ), bShouldLoop );
		}
	}
}

void LAudio::LoadSound( const char* filename, const char* name )
{
	SDLInterface::SDLSoundFile thisSound = m_AudioClass.LoadSound( filename );

	m_sounds.push_back( std::make_tuple( thisSound, name ) );
}

void LAudio::PlaySound( const char* name )
{
	for( auto sound : m_sounds )
	{
		if( 0 == strcmp( std::get< 1 >( sound ), name ) )
		{
			m_AudioClass.PlaySound( std::get< 0 >( sound ) );
		}
	}
}

void LAudio::PauseMusic( void )
{

}

void LAudio::ChangeVolume( int newVolume )
{

}