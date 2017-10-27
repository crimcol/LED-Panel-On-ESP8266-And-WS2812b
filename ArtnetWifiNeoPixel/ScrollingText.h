// ScrollingText.h

#ifndef _SCROLLINGTEXT_h
#define _SCROLLINGTEXT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "RenderObject.h"

class ScrollingText : public RenderObject
{
private:
	//int currentTextPosition;
	int textPixelLength = 0;
	String Text;

	int targetWaitMs = 500;
	int currentWaitMs = 0;
	void WaitIncrement(int ms);
	bool IsWaitCompleted(int incrementMs, int targetMs);
	bool IsWaitCompleted(int targetMs);

public:
	int PositionY = 0;
	int PositionX = 0;
	int TargetSpeedMs = 120;
	uint16_t TextColor;

	ScrollingText(Adafruit_NeoMatrix * matrix);
	void SetText(String text);
	// Inherited via RenderObject
	virtual void OnUpdate(int ms) override;


	// Inherited via RenderObject
	virtual void Render(Adafruit_NeoMatrix * matrix) override;

};

#endif

