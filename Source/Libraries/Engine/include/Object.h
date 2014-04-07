#ifndef _OBJECT_H_
#define _OBJECT_H_

// Base Object interface type
// Designed as a base type for all Engine parts
// Allows similarity of interface
class Object 
{
public:

	// Create the Object
	// Memory should be allocated here 
	// Contructor simply for POD
	virtual eError Create() = 0;

	// Initialise the Object
	// Set object into it's initial state
	virtual eError Initialise() = 0;

	// Update the Object's state
	// To be used to update the object
	// Not nessasarily once per frame or on a timestamp
	virtual eError Update() = 0;

	// Reset the object
	// Should the Object back in it's original state
	virtual eError Reset() = 0;

	// Destroy the object 
	// Should de-allocate all memory
	// And perform needed error checking
	virtual eError Destroy() = 0;
};

#endif //_OBJECT_H_