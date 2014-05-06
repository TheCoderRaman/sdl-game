//! \file LRenderer.h
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Header for LRenderer.cpp
//!
#ifndef _LRENDERER_H_
#define _LRENDERER_H_

#include "types.h"

#include "SDLRenderer.h"
#include "SDLWindow.h"

#include <list>

class LRenderer2D;

//! \brief The renderable base class
class LRendereable2D
{
public:

	//! \brief default ctor
	LRendereable2D();

	//! \brief default dtor
	~LRendereable2D();

	//! \brief the pure virtual render method
	//! Overload this to perform the render
	virtual eError Render(LRenderer2D* renderer) = 0;

	//! \brief inline set for the Z value
	inline void SetZ( int Z )
	{
		m_zValue = Z;
	}

	//! \brief inline get for the Z value
	inline int GetZ() const 
	{
		return m_zValue;
	}

	//! \brief inline set for the Z value
	inline void SetVisible(bool visible)
	{
		m_bVisible = visible;
	}

	//! \brief inline get for the Z value
	inline bool IsVisible() const
	{
		return m_bVisible;
	}


private:

	//! \brief the internal Z value
	int m_zValue;

	//! \brief if the renderable is visible
	bool m_bVisible;
	
};



//! \brief A 2D Renderer
//! Allows registering a set of renderables, that it can then choose what to do with
class LRenderer2D
{
public:

	//! \brief default ctor
	LRenderer2D();

	//! \brief default dtor
	~LRenderer2D();

	//! \brief create the renderer
	eError Create(SDLInterface::Window &window);

	//! \brief Add a renderable
	eError AddRenderable(LRendereable2D* toAdd);

	//! \brief Remove a renderable
	eError RemoveRenderable(LRendereable2D* toRemove);

	//! \brief perform the render
	eError Render();

	//! \brief destroy the renderer
	eError Destroy();

	//! \brief the base renderer get method
	inline SDLInterface::Renderer& GetBaseRenderer()
	{
		return m_BaseSDLRenderer;
	}

private:

	//! \brief call render on all renderables
	eError RenderRenderables();

	//! \brief the full list of renderables
	std::list<LRendereable2D*> m_Renderables;

	//! \brief The underlying renderer
	SDLInterface::Renderer m_BaseSDLRenderer;

};

#endif //_LRENDERER_H_