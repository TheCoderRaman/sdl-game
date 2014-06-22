//! \file LEngine.h
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Header for LEngine.cpp
//!
#ifndef _LAUDIO_H_
#define _LAUDIO_H_

#include "SDLAudio.h"
#include <vector>
#include <tuple>

class LAudio
{
public:
	LAudio();
	~LAudio();

	void LoadMusic( const char* filename, const char* name );
	void PlayMusic( const char* name, bool bShouldLoop );
	void TogglePauseMusic( void );

	void LoadSound( const char* filename, const char* name );
	void PlaySound( const char* name );

	void ChangeVolume( int newVolume );

private:

	const int iMAX_MUSIC_TRACKS = 1;
	const int iMAX_SOUNDS		= 1;

	std::vector< std::tuple< SDLInterface::SDLMusicFile, const char* > > m_musicTracks;
	std::vector< std::tuple< SDLInterface::SDLSoundFile, const char* > > m_sounds;
	
	SDLInterface::Audio m_AudioClass;
};



#endif //_LAUDIO_H_