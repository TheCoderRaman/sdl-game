#ifndef _LOBJECT_H_
#define _LOBJECT_H_

#include "error.h"

// Base LObject interface type
// Designed as a base type for all LEngine parts
// Allows similarity of interface
class LObject 
{
public:

	// Create the LObject
	// Memory should be allocated here 
	// Contructor simply for POD
	virtual eError Create() = 0;

	// Initialise the LObject
	// Set object into it's initial state
	virtual eError Initialise() = 0;

	// Update the LObject's state
	// To be used to update the object
	// Not nessasarily once per frame or on a timestamp
	virtual eError Update() = 0;

	// Reset the object
	// Should the LObject back in it's original state
	virtual eError Reset() = 0;

	// Destroy the object 
	// Should de-allocate all memory
	// And perform needed error checking
	virtual eError Destroy() = 0;
};

#endif //_LOBJECT_H_