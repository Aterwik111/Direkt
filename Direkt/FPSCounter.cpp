#include "stdafx.h"
#include "FPSCounter.h"


FPSCounter::FPSCounter()
{
	iCounter = 0;
	wstr = L"0";
	Timer.Start();
	rect.left = 0; rect.right = 300; rect.top = 0; rect.bottom = 100;
	DirectStuff->m_writeFactory->CreateTextFormat(L"Verdana",
		NULL, 
		DWRITE_FONT_WEIGHT_NORMAL, 
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		50,
		L"",
		&textFormat);
	textFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
	textFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
}
void FPSCounter::Render(){
	iCounter++;
	lTime = Timer.Stop();	
	if (lTime >= 1000000.0L){
		wstr = std::to_wstring(iCounter);
		Timer.Start();
		iCounter = 0;
	}
	DirectStuff->m_renderTarget->DrawTextW(wstr.c_str(), wstr.length(), textFormat, &rect, DirectStuff->firstBrush, D2D1_DRAW_TEXT_OPTIONS_NONE, DWRITE_MEASURING_MODE_NATURAL);
}

FPSCounter::~FPSCounter()
{
}
