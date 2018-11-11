// RANDOMPOINT.h

#ifndef _RANDOMPOINT_h
#define _RANDOMPOINT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "RenderObject.h"
#include "TimeEvent.h"

class RandomPoint : public RenderObject
{
private:
  TimeEvent newPointEvent;
  int TimeInterval = 500;
  int PositionY = 0;
  int PositionX = 0;
  
public:

	RandomPoint(Adafruit_NeoMatrix * matrix);
  uint16_t PointColor;
	
	// Inherited via RenderObject
	virtual void OnUpdate(int ms) override;
	// Inherited via RenderObject
	virtual void Render(Adafruit_NeoMatrix * matrix) override;

};

#endif
