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

#define _SDL_ERROR_WARNING		(SDLInterface::Error)0x10000000
#define _SDL_ERROR_FATAL		(SDLInterface::Error)0x20000000

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
	Surface_create_fail			= 0x10000001,
	Texture_create_fail			= 0x10000002,

	// Fatal errors
	Init_fail					= 0x20000002,
	Img_init_fail				= 0x20000004,
	Window_create_fail			= 0x20000008,
	Eventloop_double_create		= 0x20000010,
	Renderer_create_fail		= 0x20000011,
	Thread_func_null			= 0x20000012,

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
#define SDL_ERROR_HAS_TYPE_FATAL( err ) 			( SDL_ERROR_HAS( err , _SDL_ERROR_FATAL )			) 

//! \brief Check if Error is warning
#define SDL_ERROR_HAS_TYPE_WARNING( err ) 			( SDL_ERROR_HAS( err , _SDL_ERROR_WARNING )		)

//! \brief Check if Error is an SDL Error
#define SDL_REMOVE_ERR( err , toremove )			( err &= ( ~(toremove) ) )

}

#endif