// 
// 
// 

#include "ScrollingText.h"

ScrollingText::ScrollingText(Adafruit_NeoMatrix * matrix)
{
	TextColor = matrix->Color(0, 255, 0);
}

void ScrollingText::SetText(String text)
{
	this->Text = text;
	//this->PositionX = 30;
	this->textPixelLength = this->Text.length() * 6;
}

void ScrollingText::OnUpdate(int ms)
{
	if (this->scrollingEvent.IsWaitCompleted(ms, TargetSpeedMs))
	{
		PositionX--;

		if (PositionX <= -textPixelLength)
		{
			PositionX = 30;
		}

	}
}

void ScrollingText::Render(Adafruit_NeoMatrix * matrix)
{
	matrix->setTextWrap(false);
	matrix->setTextColor(TextColor);
	matrix->setCursor(PositionX, PositionY);
	matrix->print(this->Text);
}
