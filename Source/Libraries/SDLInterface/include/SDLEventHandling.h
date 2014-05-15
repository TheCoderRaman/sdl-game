//! \file SDLEventHandling.h
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Header for SDLEventHandling.cpp
//!
#ifndef _SDLEVENTHANDLING_H_
#define _SDLEVENTHANDLING_H_

#include "types.h"

// Forward declare SDL union
union SDL_Event;

// Start the SDLInterface Namespace
namespace SDLInterface
{

	enum class eSDLKeyInterface
	{
		key_a,
		key_b,
		key_c,
		key_d,
		key_e,
		key_f,
		key_g,
		key_h,
		key_i,
		key_j,
		key_k,
		key_l,
		key_m,
		key_n,
		key_o,
		key_p,
		key_q,
		key_r,
		key_s,
		key_t,
		key_u,
		key_v,
		key_w,
		key_x,
		key_y,
		key_z,
		key_escape,
		key_enter,
		key_return,
		key_tab,
		key_space,
		key_0,
		key_1,
		key_2,
		key_3,
		key_4,
		key_5,
		key_6,
		key_7,
		key_8,
		key_9,
		key_up,
		key_down,
		key_left,
		key_right,

		key_invalid,	// Should be the last one

		total_keys
	};

	//! \brief A struct that will hold this accumulated keyboard data until reset
	//! this will usually be at the end of the frame
	struct SDLKeyboardEvents
	{
		static const unsigned	sk_iTotalKeyboardEvents = ( unsigned ) eSDLKeyInterface::total_keys;
		bool					m_abKeyboardEvents[ sk_iTotalKeyboardEvents ];

		SDLKeyboardEvents()
		{
			ResetValues();
		}

		~SDLKeyboardEvents()
		{
			ResetValues();
		}

		void ResetValues( void )
		{
			for( auto& bVal : m_abKeyboardEvents )
			{
				bVal = false;
			}
		}

		void AddKeyboardEvent( eSDLKeyInterface eKeyPressed )
		{
			m_abKeyboardEvents[ ( unsigned ) eKeyPressed ] = true;
		}
	};



	class EventHandling
	{
	public:

		//! \brief Handle any event
		//! \return Any eError produced
		static eError HandleEvent(SDL_Event *event);

		//! \brief Handle any keyboard related event
		//! \return Any eError produced
		static eError HandleKeyboardEvent(SDL_Event *event);

		//! \brief Handle any Mouse related event
		//! \return Any eError produced
		static eError HandleMouseEvent(SDL_Event *event);

		//! \brief Handle any Window related event
		//! \return Any eError produced
		static eError HandleWindowEvent(SDL_Event *event);

		//! \brief Handle any Joystick related event
		//! \return Any eError produced
		//! \sa HandleControllerEvent as these two are pretty related
		static eError HandleJoystickEvent(SDL_Event *event);

		//! \brief Handle any Controller related event
		//! \return Any eError produced
		//! \sa HandleJoystickEvent as these two are pretty related
		static eError HandleControllerEvent(SDL_Event *event);

		//! \brief Getter for the static stored keyboard events struct
		//! \return The member SDLKeyboardEvents struct
		static SDLInterface::SDLKeyboardEvents* GetKeyboardEvents( void );

	private:

	};
}

#endif //_SDLEVENTHANDLING_H_