//! \file Main.h
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Header for Main.cpp
//!
#ifndef _SDLMAIN_H_
#define _SDLMAIN_H_

#include "types.h"

// Start the SDLInterface Namespace
namespace SDLInterface
{
	//! \brief Initialise SDL
	//!
	//! Initialises the needed SDL subsystems
	//!
	//! \return Any eError produced
	//! \sa Quit() for the yang to this ying
	//! \warning Do not call this twice
	eError Init();

	//! \brief Quit SDL
	//!
	//! Quits SDL
	//!
	//! \return Any eError produced
	//! \sa Init() for the ying to this yang
	//! \warning Do not call this twice
	eError Quit();


}

#endif //_SDLMAIN_H_