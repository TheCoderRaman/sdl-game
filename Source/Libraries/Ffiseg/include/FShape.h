//! \file FShape.h
//!
//! \author  Marc Di luzio
//! \date    June 2014
//!
//! Header for FWorld.cpp
//!
#ifndef _FSHAPE_H_
#define _FSHAPE_H_

#include "FCommon.h"

Ffiseg_namespace_start

class FShape
{
public:
	virtual ~FShape(){}

	enum Type
	{
		Circle = 0,
		Edge = 1,
		Polygon = 2,
		Chain = 3,
		TypeCount = 4
	};

	Type m_type;

protected:
	
	FShape(Type type)
		: m_type(type)
	{

	}

private:

	FShape();
};

class FPolygonShape
	: public FShape
{
public:

	FPolygonShape()
		: FShape(FShape::Polygon)
		, m_size{ 0.0f,0.0f}
		, m_centre{ 0.0f,0.0f}
		, m_angle( 0.0f )
	{

	}

	//! \brief Build vertices to represent an axis-aligned box centered on the local origin.
	//! \param hx the half-width.
	//! \param hy the half-height.
	inline void SetAsBox(float hx, float hy)
	{
		m_size.x = hx;
		m_size.y = hy;
	}

	//! \brief Build vertices to represent an oriented box.
	//! \param hx the half-width.
	//! \param hy the half-height.
	//! \param center the center of the box in local coordinates.
	//! \param angle the rotation of the box in local coordinates.
	inline void SetAsBox(float hx, float hy, const Vector2f& center, float angle)
	{
		m_size.x = hx;
		m_size.y = hy;
		m_centre = center;
		m_angle = angle;
	}

	Vector2f m_size;
	Vector2f m_centre;
	float m_angle;
};

Ffiseg_namespace_end

#endif // _FSHAPE_H_