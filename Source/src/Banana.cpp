//! \file GameOne.cpp
//!
//! \author  Marc Di luzio
//! \date    April 2014
//!
//! Main game class, responsible for managing all game specific stuff
//!
#include "Banana.h"

#include "eError.h"
#include "debug.h"

eError Banana::Create( void )
{
	RUNTIME_LOG( "Creating Banana..." );

	eError err = eError::NoErr;

	m_iTimeElapsed = 100;

	// Create the banana
	err |= m_banana.Create( *GetRenderer(), "Media/banana.png" );

	// Set up the banana
	m_banana.SetSourceRect( { 0, 0, 400, 300 } );
	m_banana.SetSize( 400, 300 );
	m_banana.SetPos( 100, 100 );

	return err;
}

eError Banana::Initialise( void )
{ 
	RUNTIME_LOG( "Initialising Banana..." );

	eError err = eError::NoErr;

	// Add said banana to the renderer
	if( !ERROR_HAS_TYPE_FATAL( err ) )
		err |= GetRenderer()->AddRenderable( &m_banana );

	return err;
}

eError Banana::Update( ms elapsed )
{
	m_iTimeElapsed += elapsed / 1.5;

	if( m_iTimeElapsed > 700 )
	{
		m_iTimeElapsed = -450;
	}

	m_banana.SetPos( m_iTimeElapsed, 100 );

	return eError::NoErr;
}

eError Banana::Render( LRenderer2D* renderer )
{
	return eError::NoErr;
}

eError Banana::Reset( void )
{ 
	RUNTIME_LOG( "Resetting Banana..." );

	return eError::NoErr;
}

eError Banana::Destroy( void )
{
	RUNTIME_LOG( "Destroying Banana..." );

	GetRenderer()->RemoveRenderable( &m_banana );

	m_banana.Destroy();

	// Removing our reference to the renderer
	SetRenderer( nullptr );

	return eError::NoErr;
}