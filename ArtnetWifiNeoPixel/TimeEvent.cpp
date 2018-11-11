// 
// 
// 

#include "TimeEvent.h"

TimeEvent::TimeEvent()
{
}

void TimeEvent::WaitIncrement(int ms)
{
	this->currentWaitMs += ms;
}

bool TimeEvent::IsWaitCompleted(int targetMs)
{
	if (this->currentWaitMs >= targetMs)
	{
		return true;
	}
	return false;
}

bool TimeEvent::IsWaitCompleted(int incrementMs, int targetMs)
{
	if (targetMs == 0)
	{
		return false;
	}

	WaitIncrement(incrementMs);
	if (IsWaitCompleted(targetMs))
	{
		currentWaitMs = currentWaitMs % targetMs;
		return true;
	}
	return false;
}
