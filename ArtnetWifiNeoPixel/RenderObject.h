// RenderObject.h

#ifndef _RENDEROBJECT_h
#define _RENDEROBJECT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Adafruit_NeoMatrix.h>

class RenderObject
{
private:
public:
	// Calculate object state.
	virtual void OnUpdate(int ms) = 0;
	// Render object on matrix
	virtual void Render(Adafruit_NeoMatrix *matrix) = 0;

};

#endif

