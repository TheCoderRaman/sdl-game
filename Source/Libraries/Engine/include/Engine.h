#ifndef _ENGINE_H_
#define _ENGINE_H_

#include "types.h"
#include "SDLWindow.h"

class Engine
{
public:

	// Constructor and destructor
	Engine();
	~Engine();

	eError init();

	eError run();

	eError quit();	

private:

	eError load();	
	eError loop();
	eError unload();

	SDLWindow myMainWindow = SDLWindow();

};

#endif //_ENGINE_H_