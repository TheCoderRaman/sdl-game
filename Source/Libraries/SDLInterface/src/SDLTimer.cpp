//! \file SDLTimer.cpp
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Container for various SDL_Timer functions as found here:
//! https://wiki.libsdl.org/CategoryTimer?highlight=%28%5CbCategoryCategory%5Cb%29
//!
#include "SDLTimer.h"

#include "SDL.h"

//========================================================
SDLInterface::SDLTimer::SDLTimer()
: m_startTime( 0 )
{

}

//========================================================
SDLInterface::SDLTimer::~SDLTimer()
{

}

//========================================================
ms SDLInterface::SDLTimer::GetGlobalLifetime(void)
{
	return SDL_GetTicks();
}

//========================================================
ms SDLInterface::SDLTimer::GetGlobalTicksSince(ms time)
{
	return GetGlobalLifetime() - time;
}

//========================================================
void SDLInterface::SDLTimer::Start(void)
{
	m_startTime = GetGlobalLifetime();
}

//========================================================
ms SDLInterface::SDLTimer::GetTimePassed(void)
{
	return GetGlobalLifetime() - m_startTime;
}

//========================================================
void SDLInterface::SDLTimer::Reset(void)
{
	m_startTime = 0;
}