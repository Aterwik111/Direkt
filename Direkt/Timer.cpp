#include "stdafx.h"
#include "Timer.h"


CTimer::CTimer()
{
	QueryPerformanceFrequency(&this->liFrequency);
}
void CTimer::Start(){
	QueryPerformanceCounter(&this->liCountStart);
}
long long CTimer::Stop(){
	QueryPerformanceCounter(&this->liCountStop);
	long long ticks = liCountStop.QuadPart - liCountStart.QuadPart;
	return ticks*1000000/ liFrequency.QuadPart;
}

CTimer::~CTimer()
{
}
