//! \file math.h
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Contains defines for simple global types
//!	Possibly needs refactoring at some point
#ifndef _MATH_H_
#define _MATH_H_

//! \brief a generic 2D point
template< typename T >
struct CoordBase2D
{
	T x;
	T y;

	CONSTEXPR CoordBase2D() : x(0), y(0) {}
	CONSTEXPR CoordBase2D(T X, T Y) : x(X), y(Y) {}

	//! \brief get the length of the vector squared (fast)
	inline T MagnituteSqr() const
	{
		return (x*x) + (y*y);
	}

	//! \brief get the length of the vector ( slow )
	inline T Magnitute() const
	{
		return sqrt(MagnituteSqr());
	}
};

//! \brief a generic 2D vector
template< typename T >
struct VectorBase2D
{
	// Union of the two co-ordinates
	union
	{
		struct
		{
			T ox;
			T oy;
			T x;
			T y;
		};

		struct
		{
			CoordBase2D<T> origin;
			CoordBase2D<T> end;
		};
	};

	// Plain constructors
	CONSTEXPR VectorBase2D() : origin(0, 0), end(0,0) {}
	CONSTEXPR VectorBase2D(T X, T Y) : origin(0,0), end(X,Y) {}
	CONSTEXPR VectorBase2D(T OX, T OY, T X, T Y) : origin(OX, OY), end(X, Y) {}

	CONSTEXPR VectorBase2D(const CoordBase2D<T>& orig, const CoordBase2D<T>& en) : origin(orig), end(en) {}

	//! \brief get the length of the vector squared (fast)
	inline T LengthSqr() const
	{
		const T xl = x - ox;
		const T y1 = y = oy;
		return (ox*ox) + (oy*oy);
	}

	//! \brief get the length of the vector ( slow )
	inline T Length() const
	{
		return sqrt(LengthSqr());
	}
};

//! \brief a generic 2D rectangle
template< typename T >
struct RectBase2D
{
	union
	{
		struct
		{
			T x;
			T y;
			T w;
			T h;
		};
		CoordBase2D<T> origin;
		CoordBase2D<T> dimensions;
	};

	CONSTEXPR RectBase2D() : origin(), dimensions(){}
	CONSTEXPR RectBase2D(T X, T Y, T W, T H) : origin(X, Y), dimensions(W,H){}

	CONSTEXPR RectBase2D(const CoordBase2D<T>& orig, const CoordBase2D<T>& dim) : origin(orig), dimensions(dim) {}

	//! \brief get the area
	inline T Area() const
	{
		return w*h;
	}
};

// Points ( x,y )
typedef CoordBase2D<float>	Point2f;
typedef CoordBase2D<int>	Point2i;

typedef CoordBase2D<float>	Velocity2f;
typedef CoordBase2D<int>	Velocity2i;

// Vectors ( ox,oy x,y )
typedef VectorBase2D<float>	Vector2f;
typedef VectorBase2D<int>	Vector2i;

// Rectangles ( x,y w,h )
typedef RectBase2D<float>	Rect4f;
typedef RectBase2D<int>		Rect4i;

#endif //_MATH_H_