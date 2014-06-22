//! \file LRenderer.h
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//!
#include "LRenderer.h"
#include "SDLTimer.h"
#include "SDLError.h"

#include "LError.h"
#include "debug.h"

#define MAX_NUM_RENDERABLES 256

#define RENDER_TIMING_DEBUG 0

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
LError LRendereable2D::SetRenderer(LRenderer2D* parent)
{
	LError err = LError::NoErr;
	
	// Throw an error if the renderer was already attached to another renderer
	if (m_pRenderer != nullptr)
	{
		// TODO: use a more specific error code here
		err |= LError::Warning;
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
LError LRenderer2D::Create(SDLInterface::Window &window)
{
	SDLInterface::Error err = SDLInterface::Error::None;

	// Create the renderer
	err |= m_BaseSDLRenderer.Create(&window);

	return SDL_ERROR_HAS_FATAL(err) ? LError::Fatal : LError::NoErr;
}

//===============================================================
LError LRenderer2D::AddRenderable(LRendereable2D* toAdd)
{
	LError err = LError::NoErr;

	// Assert the max number of renderables
	DEBUG_ASSERT(m_Renderables.size() <= MAX_NUM_RENDERABLES);
	
	// Add the renderable to the list
	m_Renderables.push_back(toAdd);

	toAdd->SetRenderer(this);

	return err;
}

//===============================================================
LError LRenderer2D::RemoveRenderable(LRendereable2D* toRemove)
{
	LError err = LError::NoErr;

	// Remove the renderable from the list
	m_Renderables.remove(toRemove);

	toRemove->SetRenderer(nullptr);

	return err;
}

//===============================================================
LError LRenderer2D::Render()
{
	LError err = LError::NoErr;
	SDLInterface::Error sdlerr = SDLInterface::Error::None;

#if RENDER_TIMING_DEBUG
	SDLInterface::Timer timer;
	timer.Start();
#endif

	// Start the render
	if (!LERROR_HAS_FATAL(err))
		sdlerr |= m_BaseSDLRenderer.RenderStart();

	// Render all the renderables
	if (!SDL_ERROR_HAS_FATAL(sdlerr))
		err |= RenderRenderables();

	// End the render
	if (!LERROR_HAS_FATAL(err))
		sdlerr |= m_BaseSDLRenderer.RenderEnd();

#if RENDER_TIMING_DEBUG
	ms time = timer.GetTimePassed();
	DEBUG_LOG("RENDER TOOK: %i ticks %f seconds %f fps", time, msToSec(time), 1.0f / msToSec(time));
#endif

	// Pull in the SDL error
	err |= SDL_ERROR_HAS_FATAL(sdlerr) ? LError::Fatal : LError::NoErr;

	return err;
}


//===============================================================
LError LRenderer2D::RenderRenderables()
{
	LError err = LError::NoErr;

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
LError LRenderer2D::Destroy()
{
	LError err = LError::NoErr;

	// Destroy the renderer
	m_BaseSDLRenderer.Destroy();

	return err;
}