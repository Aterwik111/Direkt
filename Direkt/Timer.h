#pragma once
class CTimer
{
private:
	LARGE_INTEGER liFrequency;
	LARGE_INTEGER liCountStart, liCountStop;
public:
	void Start();
	long long Stop();
	CTimer();
	~CTimer();
};

