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

void LAudio::PauseMusic( void )
{

}

void LAudio::ChangeVolume( int newVolume )
{

}