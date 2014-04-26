//! \file Timer.h
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Header for Timer.cpp
//!
#ifndef _SDLTIMER_H_
#define _SDLTIMER_H_

#include "types.h"

//! \brief convert ms to seconds
#define msToSec(ms) (ms/1000)

// Start the SDLInterface Namespace
namespace SDLInterface
{

	//! \brief class to contain a timer, useful for timekeeping
	//! Could be extended with various stopwatch like abilities like laps and pause/play
	class Timer
	{
	public:

		//! Default ctor and dtor
		Timer();
		~Timer();

		//! \brief Start the timer
		void Start(void);

		//! \brief Get the time passed since Start
		ms GetTimePassed(void);

		//! \brief Reset the timer
		void Reset(void);

		// Static timer methods

		//! \brief Get the number of ticks since program initialisation
		static ms GetGlobalLifetime(void);

		//! \brief Get number of ticks since
		static ms GetGlobalTicksSince(ms time);

	private:

		ms m_startTime;
	};

}
#endif //_SDLTIMER_H_
