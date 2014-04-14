//! \file SDLTimer.h
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Header for SDLTimer.cpp
//!
#ifndef _SDLTIMER_H_
#define _SDLTIMER_H_

//! \brief all timer methods are in ms (milliseconds)
typedef int ms;

#define msToSec(ms) (ms/1000)

//! \brief class to contain a timer, useful for timekeeping
//! Could be extended with various stopwatch like abilities like laps and pause/play
class SDLTimer
{
public:	
	
	//! \brief Get the number of ticks since program initialisation
	static ms GetGlobalLifetime(void);

	//! \brief Get number of ticks since
	static ms GetGlobalTicksSince(ms since);

	//! \brief Start the timer
	void Start( void );

	//! \brief Get the time passed since Start
	ms GetTimePassed( void );

	//! \brief Reset the timer
	void Reset( void );

private:

	ms m_startTime;
};

#endif //_SDLTIMER_H_
