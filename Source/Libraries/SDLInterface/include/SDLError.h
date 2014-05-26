//! \file SDLError.h
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Header for SDLInterface::Error type
//!
#ifndef _SDLERROR_H_
#define _SDLERROR_H_

//! Great explanation on how this can work is here 
//! http://forum.codecall.net/topic/56591-bit-fields-flags-tutorial-with-example/

#define _SDL_ERROR_WARNING		0x10000000
#define _SDL_ERROR_FATAL		0x20000000

namespace SDLInterface
{

//! \brief generic Error enum for Error handling
enum class Error : int
{
	// 	Error name				Error bit value for flags
	None						= 0,

	// Harmless errors
	QuitRequest					= 0x00000001,

	// Warning errors
	Surface_create_fail			= 0x00000002 | _SDL_ERROR_WARNING,
	Texture_create_fail			= 0x00000004 | _SDL_ERROR_WARNING,

	// Fatal errors
	Init_fail					= 0x00000008 | _SDL_ERROR_FATAL,
	Img_init_fail				= 0x00000010 | _SDL_ERROR_FATAL,
	Window_create_fail			= 0x00000011 | _SDL_ERROR_FATAL,
	Eventloop_double_create		= 0x00000012 | _SDL_ERROR_FATAL,
	Renderer_create_fail		= 0x00000014 | _SDL_ERROR_FATAL,
	Thread_func_null			= 0x00000018 | _SDL_ERROR_FATAL,

};

//! \brief bitwise or operator 
//! returns an enum containing a combination the bits of \a lhs and \a rhs
inline Error operator | (Error lhs, Error rhs)
{
	return (Error)((int)lhs | (int)rhs);
}

//! \brief bitwise & operator
//! returns an enum containing only the shared bits of \a lhs and \a rhs
inline Error operator & (Error lhs, Error rhs)
{
	return (Error)((int)lhs & (int)rhs);
}

//! \brief bitwise ~ operator for const errors
inline Error operator ~ (const Error& err)
{
	return (Error)(~(int)err);
}

//! \brief bitwise | and assignement operator
inline Error& operator |= (Error& lhs, Error rhs)
{
	lhs = lhs | rhs;
	return lhs;
}

//! \brief bitwise | and assignement operator
inline Error& operator += (Error& lhs, Error rhs)
{
	lhs = lhs | rhs;
	return lhs;
}

//! \brief bitwise & and assignement operator
inline Error& operator &= (Error& lhs, Error rhs)
{
	lhs = lhs & rhs;
	return lhs;
}

//! \brief Check if the error contains
#define SDL_ERROR_HAS( err , contains )				( (err & (contains) ) == (contains) )

//! \brief Check if Error is fatal
#define SDL_ERROR_HAS_FATAL( err ) 			( SDL_ERROR_HAS( err , (SDLInterface::Error)_SDL_ERROR_FATAL )			) 

//! \brief Check if Error is warning
#define SDL_ERROR_HAS_WARNING( err ) 			( SDL_ERROR_HAS( err , (SDLInterface::Error)_SDL_ERROR_WARNING )		)

//! \brief Check if Error is an SDL Error
#define SDL_REMOVE_ERR( err , toremove )			( err &= ( ~(toremove) ) )

}

#endif