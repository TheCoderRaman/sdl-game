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
}

LAudio::~LAudio()
{
}

void LAudio::PlayMusic( const char* filename, bool bShouldLoop )
{
	SDLInterface::SDLMusicFile thisMusic = m_AudioClass.LoadMusic( filename );

	m_AudioClass.PlayMusic( thisMusic, bShouldLoop );
}

void LAudio::PauseMusic( void )
{

}

void LAudio::ChangeVolume( int newVolume )
{

}