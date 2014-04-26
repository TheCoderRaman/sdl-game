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
SDLTimer::SDLTimer()
: m_startTime( 0 )
{

}

//========================================================
SDLTimer::~SDLTimer()
{

}

//========================================================
ms SDLTimer::GetGlobalLifetime(void)
{
	return SDL_GetTicks();
}

//========================================================
ms SDLTimer::GetGlobalTicksSince(ms time)
{
	return GetGlobalLifetime() - time;
}

//========================================================
void SDLTimer::Start(void)
{
	m_startTime = GetGlobalLifetime();
}

//========================================================
ms SDLTimer::GetTimePassed(void)
{
	return GetGlobalLifetime() - m_startTime;
}

//========================================================
void SDLTimer::Reset(void)
{
	m_startTime = 0;
}