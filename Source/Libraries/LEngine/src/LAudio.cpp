//! \file LAudio.cpp
//!
//! \author  Owain Davies
//! \date    June 2014
//!
//! The main audio engine class - this loads and stores all the music and sfx used in the game
//! through an SDL interface
//!

#include "LAudio.h"
#include <string.h>

//====================================================
LAudio::LAudio()
{
	// Ensure we reserve the vectors so no RTA is done
	m_musicTracks.reserve( iMAX_MUSIC_TRACKS );
	m_sounds.reserve( iMAX_SOUNDS );
}

//====================================================
LAudio::~LAudio()
{
	// Delete all music
	for( auto track : m_musicTracks )
	{
		std::get< 0 >( track ).FreeMusic();
	}
	// Delete all sounds
	for( auto sound : m_sounds )
	{
		std::get< 0 >( sound ).FreeSound();
	}
}

//====================================================
// Load music and push it into our storage container with a name
void LAudio::LoadMusic( const char* filename, const char* name )
{
	SDLInterface::SDLMusicFile thisMusic = m_AudioClass.LoadMusic( filename );

	m_musicTracks.push_back( std::make_tuple( thisMusic, name ) );
}

//====================================================
// Search through every music track for the correct name and play that track
void LAudio::PlayMusic( const char* name, bool bShouldLoop )
{
	for( auto track : m_musicTracks )
	{
		if( 0 == strcmp( std::get< 1 >( track ), name ) )
		{
			m_AudioClass.PlayMusic( std::get< 0 >( track ), bShouldLoop );
			break;
		}
	}
}

//====================================================
// Load a sound and push it into our storage container with a name
void LAudio::LoadSound( const char* filename, const char* name )
{
	SDLInterface::SDLSoundFile thisSound = m_AudioClass.LoadSound( filename );

	m_sounds.push_back( std::make_tuple( thisSound, name ) );
}

//====================================================
// Play a sound given by searching for the name the sound was given 
void LAudio::PlaySound( const char* name )
{
	for( auto sound : m_sounds )
	{
		if( 0 == strcmp( std::get< 1 >( sound ), name ) )
		{
			m_AudioClass.PlaySound( std::get< 0 >( sound ) );
			break;
		}
	}
}

//====================================================
void LAudio::TogglePauseMusic( void )
{
	m_AudioClass.ToggleMusicPause();
}

//====================================================
void LAudio::ChangeVolume( int newVolume )
{

}
