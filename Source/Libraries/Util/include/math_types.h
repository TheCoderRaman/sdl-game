//! \file math.h
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Contains defines for simple global types
//!	Possibly needs refactoring at some point
#ifndef _MATH_H_
#define _MATH_H_

// MSVC Does not support constexpr yet...
#if WINDOWS_BUILD
#define CONSTEXPR
#else
#define CONSTEXPR constexpr
#endif

//! \brief a 2D vector
struct Vector2f
{
	CONSTEXPR Vector2f()
		: x(0.0f)
		, y(0.0f)
	{
	}

	CONSTEXPR Vector2f(float X, float Y)
		: x(X)
		, y(Y)
	{
	}

	float x;
	float y;
};

#endif //_MATH_H_