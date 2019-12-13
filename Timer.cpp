#include "Timer.h"

unsigned int  Timer::_nowTime;

void Timer::Init()
{
	_nowTime = 0;
}

void Timer::Uninit()
{
}

void Timer::Update()
{
	++_nowTime;
}

unsigned int Timer::GetNowTime()
{
	return _nowTime;
}
