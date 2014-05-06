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
SDLInterface::Timer::Timer()
: m_startTime( 0 )
{

}

//========================================================
SDLInterface::Timer::~Timer()
{

}

//========================================================
ms SDLInterface::Timer::GetGlobalLifetime(void)
{
	return SDL_GetTicks();
}

//========================================================
ms SDLInterface::Timer::GetGlobalTicksSince(ms time)
{
	return GetGlobalLifetime() - time;
}

//========================================================
void SDLInterface::Timer::Start(void)
{
	m_startTime = GetGlobalLifetime();
}

//========================================================
ms SDLInterface::Timer::GetTimePassed(void)
{
	return GetGlobalLifetime() - m_startTime;
}

//========================================================
void SDLInterface::Timer::Reset(void)
{
	m_startTime = GetGlobalLifetime();
}