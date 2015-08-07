#include "stdafx.h"
#include "DirectStuff.h"


CDirectStuff::CDirectStuff()
{
}
void CDirectStuff::Initialize(){
	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_factory);
	DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(m_writeFactory), reinterpret_cast<IUnknown **>(&m_writeFactory));
	GetClientRect(System->m_hwnd, &System->clientRect);
	RECT* rc = &System->clientRect;
	D2D1_SIZE_U size = D2D1::SizeU(
		rc->right - rc->left,
		rc->bottom - rc->top
		);
	m_factory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(System->m_hwnd, size, D2D1_PRESENT_OPTIONS_IMMEDIATELY),
		&m_renderTarget
		);
	DirectStuff->m_renderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::YellowGreen, 1.0f), &DirectStuff->firstBrush);
	DirectStuff->m_renderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Gold, 1.0f), &DirectStuff->secondBrush);
}
void CDirectStuff::Cleanup(){
	SafeRelease(m_renderTarget);
	SafeRelease(m_factory);
}
CDirectStuff::~CDirectStuff()
{
}
