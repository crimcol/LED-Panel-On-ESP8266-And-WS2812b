// 
// 
// 

#include "RandomPoint.h"
#include <ESP8266TrueRandom.h>

RandomPoint::RandomPoint(Adafruit_NeoMatrix * matrix)
{
  PointColor = matrix->Color(255, 0, 0);
}

void RandomPoint::OnUpdate(int ms)
{
  if (this->newPointEvent.IsWaitCompleted(ms, TimeInterval))
  {
    PositionX = random(0,29);
    PositionY = random(0,13);
  }
}

void RandomPoint::Render(Adafruit_NeoMatrix * matrix)
{
	matrix->drawPixel(PositionX, PositionY, PointColor);
}
