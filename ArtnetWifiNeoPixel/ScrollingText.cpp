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
	this->currentTextPosition = 30;
	this->textPixelLength = this->Text.length() * 6;
}

void ScrollingText::OnUpdate(int ms)
{
	if (IsWaitCompleted(ms, TargetSpeedMs))
	{
		currentTextPosition--;

		if (currentTextPosition <= -textPixelLength)
		{
			currentTextPosition = 30;
		}

	}
}

void ScrollingText::Render(Adafruit_NeoMatrix * matrix)
{
	matrix->setTextWrap(false);
	matrix->setTextColor(TextColor);
	matrix->setCursor(currentTextPosition, TextLine * 7);
	matrix->print(this->Text);
}

