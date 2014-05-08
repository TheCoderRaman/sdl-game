//! \file LRenderer.h
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//!
#include "LRenderer.h"

#include "eError.h"
#include "debug.h"

#define MAX_NUM_RENDERABLES 256

//===============================================================
LRendereable2D::LRendereable2D()
: m_zValue( 0 )
, m_bVisible( true )
, m_pRenderer( nullptr )
{

}

//===============================================================
LRendereable2D::~LRendereable2D()
{
	// the rendererable must get detached before destruction
	DEBUG_ASSERT(m_pRenderer == nullptr);
}

//===============================================================
eError LRendereable2D::SetRenderer(LRenderer2D* parent)
{
	eError err = eError::NoErr;
	
	// Throw an error if the renderer was already attached to another renderer
	if (m_pRenderer != nullptr)
	{
		// TODO: use a more specific error code here
		err |= eError::Type_Warning;
	}

	m_pRenderer = parent;

	return err;
}

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

	// Assert the max number of renderables
	DEBUG_ASSERT(m_Renderables.size() <= MAX_NUM_RENDERABLES);
	
	// Add the renderable to the list
	m_Renderables.push_back(toAdd);

	toAdd->SetRenderer(this);

	return err;
}

//===============================================================
eError LRenderer2D::RemoveRenderable(LRendereable2D* toRemove)
{
	eError err = eError::NoErr;

	// Remove the renderable from the list
	m_Renderables.remove(toRemove);

	toRemove->SetRenderer(nullptr);

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

	// Sort the renderables based on Z value
	m_Renderables.sort(
	[](const LRendereable2D* lhs, const LRendereable2D* rhs)->bool
	{
		return lhs->GetZ() > rhs->GetZ(); 
	});

	// For each renderable
	for (LRendereable2D* pRenderable : m_Renderables)
	{
		// Sanity check
		DEBUG_ASSERT(pRenderable);

		// if the renderable is visible, then render it
		if (pRenderable->IsVisible())
		{
			// Render the renderable
			pRenderable->Render(this);
		}
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