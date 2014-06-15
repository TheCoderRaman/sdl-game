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

class LAudio
{
public:
	LAudio();
	~LAudio();

	void PlayMusic( const char* filename );
	void PauseMusic( void );
	void ChangeVolume( int newVolume );

private:

	SDLInterface::Audio m_AudioClass;
};



#endif //_LAUDIO_H_