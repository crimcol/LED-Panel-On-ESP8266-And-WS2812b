// TIMEEVENT.h

#ifndef _TIMEEVENT_h
#define _TIMEEVENT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

class TimeEvent
{
private:
	int currentWaitMs = 0;
	
  void WaitIncrement(int ms);
  bool IsWaitCompleted(int targetMs);
  
public:
	TimeEvent();
  bool IsWaitCompleted(int incrementMs, int targetMs);
};

#endif
