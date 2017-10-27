// 
// 
// 

#include "ScrollingText.h"

void ScrollingText::WaitIncrement(int ms)
{
	this->currentWaitMs += ms;
}

bool ScrollingText::IsWaitCompleted(int targetMs)
{
	if (this->currentWaitMs >= targetMs)
	{
		return true;
	}
	return false;
}

bool ScrollingText::IsWaitCompleted(int incrementMs, int targetMs)
{
	if (targetMs == 0)
	{
		return false;
	}

	WaitIncrement(incrementMs);
	if (IsWaitCompleted(targetMs))
	{
		currentWaitMs = currentWaitMs % targetMs;
		Serial.println("Wait completed.");
		return true;
	}
	return false;
}

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
	if (IsWaitCompleted(ms, TargetSpeedMs))
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

