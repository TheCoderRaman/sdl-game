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

//! Default ctor
SDLTimer::SDLTimer()
: m_startTime( 0 )
{

}

//! Default dtor
SDLTimer::~SDLTimer()
{

}

//! \brief Get the number of ticks since program initialisation
ms SDLTimer::GetGlobalLifetime(void)
{
	return SDL_GetTicks();
}

//! \brief Get number of ticks since
ms SDLTimer::GetGlobalTicksSince(ms time)
{
	return GetGlobalLifetime() - time;
}

//! \brief Start the timer
void SDLTimer::Start(void)
{
	m_startTime = GetGlobalLifetime();
}

//! \brief Get the time passed since Start
ms SDLTimer::GetTimePassed(void)
{
	return GetGlobalLifetime() - m_startTime;
}

//! \brief Reset the timer
void SDLTimer::Reset(void)
{
	m_startTime = 0;
}