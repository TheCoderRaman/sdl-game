//! \file eError.h
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Contains eError handling types and methods
#ifndef _ERROR_H_
#define _ERROR_H_

//! Great explanation on how this can work is here 
//! http://forum.codecall.net/topic/56591-bit-fields-flags-tutorial-with-example/

//! \brief generic eError enum for eError handling
enum class eError
: long
{
// 	eError name		  eError bit value for flags
	noErr			= 0x00000000,

	// 	eError flags         First two bytes for erro types
	Type_Fatal		= 0x10000000, 	// Fatal flag
	Type_Warning	= 0x20000000, 	// Warning flag

	//  eError catagories    3rd and 4th bits for eError catagoreis
	Catagory_SDL	= 0x00100000, 	// SDL flag

	// 	Specific Errors     Last 4 bits for specific errors
	quitRequest		= 0x00000001,

	//  Composite Errors (Errors produced as a composite of type, catagory and/or specifics)
	SDL_Fatal		= 0x10100000	// Contains Fatal eError AND SDL catagory

};

//! \brief bitwise or operator 
//! returns an enum containing a combination the bits of \a lhs and \a rhs
inline eError operator | (eError lhs, eError rhs)
{
	return (eError)((long)lhs | (long)rhs);
}

//! \brief bitwise & operator
//! returns an enum containing only the shared bits of \a lhs and \a rhs
inline eError operator & (eError lhs, eError rhs)
{
	return (eError)((long)lhs & (long)rhs);
}

//! \brief bitwise | and assignement operator
inline eError& operator |= (eError& lhs, eError rhs)
{
	lhs = lhs | rhs;
	return lhs;
}

//! \brief bitwise & and assignement operator
inline eError& operator &= (eError& lhs, eError rhs)
{
	lhs = lhs & rhs;
	return lhs;
}

//! \brief Check if eError is fatal
#define ERROR_TYPE_IS_FATAL( err ) 			( (err & eError::Type_Fatal)	== eError::Type_Fatal		) 

//! \brief Check if eError is warning
#define ERROR_TYPE_IS_WARNING( err ) 		( (err & eError::Type_Warning)	== eError::Type_Warning		)

//! \brief Check if eError is an SDL eError
#define ERROR_CATAGORY_IS_SDL( err )		( (err & eError::Catagory_SDL)	== eError::Catagory_SDL		)


#endif //_ERROR_H_
