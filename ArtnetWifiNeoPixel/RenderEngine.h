// RenderEngine.h

#ifndef _RENDERENGINE_h
#define _RENDERENGINE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "RenderObject.h"
#include <Adafruit_NeoMatrix.h>

class RenderEngine
{
private:
	int arraySize = 5;
	int objectsCount = 0;
	RenderObject **objectsArray = NULL;

	Adafruit_NeoMatrix *matrix = NULL;
public:
	RenderEngine(Adafruit_NeoMatrix *matrix);
	~RenderEngine();
	void AddObject(RenderObject *renderObject);
	void FrameUpdate(int ms);
};

#endif

