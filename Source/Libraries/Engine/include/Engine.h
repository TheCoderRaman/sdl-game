#ifndef _ENGINE_H_
#define _ENGINE_H_

#include "types.h"
#include "SDLWindow.h"

// Engine delegate class
class Engine
{
public:

	// Constructor and destructor
	Engine();
	~Engine();

	// Init the engine
	eError init();

	// run ( will not return until finished running )
	eError run();

	// quit the engine
	eError quit();	

private:

	// Loads assets
	eError load();

	// calls the event loop	
	eError loop();

	// unloads the assets
	eError unload();

	// Member variables
	SDLWindow myMainWindow;

};

#endif //_ENGINE_H_