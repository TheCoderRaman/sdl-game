//! \file LRenderer.h
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//!
#include "LRenderer.h"

#include "eError.h"

//===============================================================
LRenderer2D::LRenderer2D()
{

}

//===============================================================
LRenderer2D::~LRenderer2D()
{

}

//===============================================================
eError LRenderer2D::Create(SDLInterface::Window &window)
{
	eError err = eError::NoErr;

	// Create the renderer
	err |= m_BaseSDLRenderer.Create(&window);

	return err;
}

//===============================================================
eError LRenderer2D::AddRenderable(LRendereable2D* toAdd)
{
	eError err = eError::NoErr;

	// Add the renderable to the list
	m_vecRenderables.push_back(toAdd);

	return err;
}

//===============================================================
eError LRenderer2D::RemoveRenderable(LRendereable2D* toRemove)
{
	eError err = eError::NoErr;

	// Remove the renderable from the list
	m_vecRenderables.remove(toRemove);

	return err;
}

//===============================================================
eError LRenderer2D::Render()
{
	eError err = eError::NoErr;

	// Start the render
	if (!ERROR_HAS_TYPE_FATAL(err))
		err |= m_BaseSDLRenderer.RenderStart();

	// Render all the renderables
	if (!ERROR_HAS_TYPE_FATAL(err))
		err |= RenderRenderables();

	// End the render
	if (!ERROR_HAS_TYPE_FATAL(err))
		err |= m_BaseSDLRenderer.RenderEnd();

	return err;
}

//===============================================================
eError LRenderer2D::RenderRenderables()
{
	eError err = eError::NoErr;

	// For each renderable
	for (LRendereable2D* pRenderable : m_vecRenderables)
	{
		// Render the renderable
		pRenderable->Render(m_BaseSDLRenderer);
	}

	return err;
}

//===============================================================
eError LRenderer2D::Destroy()
{
	eError err = eError::NoErr;

	// Destroy the renderer
	err |= m_BaseSDLRenderer.Destroy();

	return err;
}