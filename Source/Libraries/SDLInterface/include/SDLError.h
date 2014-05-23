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

namespace SDLInterface
{

//! \brief generic Error enum for Error handling
enum class Error : int
{
	// 	Error name		  Error bit value for flags
	NoErr				= 0x00000000,

	// 	Error types         First two bytes for erro types
	Type_Fatal			= 0x10000000, 	// Fatal flag
	Type_Warning		= 0x20000000, 	// Warning flag

	// 	Specific Errors     Last 4 bits for specific errors
	QuitRequest			= 0x00000001,
	Init_fail			= 0x10000002,
	Img_init_fail		= 0x10000004,

	Window_create_fail,
	Eventloop_double_create,
	Renderer_create_fail,
	Thread_func_null,
	Surface_create_fail,
	Texture_create_fail,

	// ALL errors
	All					= 0x11111111,

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
#define SDL_ERROR_HAS_TYPE_FATAL( err ) 			( SDL_ERROR_HAS( err , SDLInterface::Error::Type_Fatal )			) 

//! \brief Check if Error is warning
#define SDL_ERROR_HAS_TYPE_WARNING( err ) 			( SDL_ERROR_HAS( err , SDLInterface::Error::Type_Warning )		)

//! \brief Check if Error is an SDL Error
#define SDL_REMOVE_ERR( err , toremove )			( err &= ( ~(toremove) ) )

}

#endif