//! \file FDebugDraw.cpp
//!
//! \author  Marc Di luzio
//! \date    June 2014
//!
//! Implementation for debug drawing
//!
#include "FDebugDraw.h"
#include "FInternal.h"

Ffiseg_namespace_start

class FDebugDraw_Internal
	: public b2Draw
{
public:

	FDebugDraw_Internal()
		: m_renderer(nullptr)
	{

	}

	/// Draw a closed polygon provided in CCW order.
	virtual void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);

	/// Draw a solid closed polygon provided in CCW order.
	virtual void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);

	/// Draw a circle.
	virtual void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color);

	/// Draw a solid circle.
	virtual void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color);

	/// Draw a line segment.
	virtual void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);

	/// Draw a transform. Choose your own length scale.
	/// @param xf a transform.
	virtual void DrawTransform(const b2Transform& xf);

	SDLInterface::Renderer* m_renderer;

};

//========================================================
FDebugDraw_Internal s_FDebugDraw_Internal;

//========================================================
FDebugDraw FDebugDraw::s_debugDraw;

//========================================================
void FDebugDraw::DebugDraw(SDLInterface::Renderer* renderer)
{
	if (renderer && s_debugDraw.m_world)
	{
		s_FDebugDraw_Internal.m_renderer = renderer;
		s_debugDraw.m_world->GetBaseWorldPtr()->DrawDebugData();
	}
}

//========================================================
void FDebugDraw::Register(FWorld* world)
{
	s_debugDraw.m_world = world;

	s_debugDraw.m_world->GetBaseWorldPtr()->SetDebugDraw(&s_FDebugDraw_Internal);
}

//========================================================
void FDebugDraw::UnRegister()
{
	s_debugDraw.m_world->GetBaseWorldPtr()->SetDebugDraw(nullptr);
	s_debugDraw.m_world = nullptr;
}

//========================================================
/// Draw a closed polygon provided in CCW order.
void FDebugDraw_Internal::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	for (int i = 0; i < vertexCount; i++)
	{

	}
}

//========================================================
/// Draw a solid closed polygon provided in CCW order.
void FDebugDraw_Internal::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{

}

//========================================================
/// Draw a circle.
void FDebugDraw_Internal::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{

}

//========================================================
/// Draw a solid circle.
void FDebugDraw_Internal::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{

}

//========================================================
/// Draw a line segment.
void FDebugDraw_Internal::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{

}

//========================================================
/// Draw a transform. Choose your own length scale.
/// @param xf a transform.
void FDebugDraw_Internal::DrawTransform(const b2Transform& xf)
{

}


Ffiseg_namespace_end