#pragma once
#include "Renderable.h"
class FPSCounter :
	public Renderable
{
	CTimer Timer;
	long long lTime;
	int iCounter;
	IDWriteTextFormat* textFormat;
	std::wstring wstr;
	D2D1_RECT_F rect;
public:
	void Render();
	FPSCounter();
	~FPSCounter();
};

