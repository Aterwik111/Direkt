#include "stdafx.h"
#include "Graphic.h"

CGraphic::CGraphic()
{

}

D2D1_POINT_2F CGraphic::CalculatePositionOnScreen(positionD point)
{
	D2D1_SIZE_F screenSize = DirectStuff->m_renderTarget->GetSize();
	D2D1_POINT_2F ret;
	ret.x = (screenSize.width / 2) - ((static_cast<FLOAT> (FrameData->camPos.x) - static_cast<FLOAT> (point.x))*FrameData->fPixelsPerMeter);
	ret.y = (screenSize.height / 2) + ((static_cast<FLOAT> (FrameData->camPos.y) - static_cast<FLOAT> (point.y))*FrameData->fPixelsPerMeter);
	return ret;
}
D2D1_RECT_F CGraphic::RectFromPoints(D2D1_POINT_2F p1, D2D1_POINT_2F p2){
	D2D1_RECT_F ret;
	if (p1.x >= p2.x){
		ret.right = p1.x;
		ret.left = p2.x;
	}
	else{
		ret.left = p1.x;
		ret.right = p2.x;
	}

	if (p1.y >= p2.y){
		ret.bottom = p1.y;
		ret.top = p2.y;
	}
	else{
		ret.top = p1.y;
		ret.bottom = p2.y;
	}
	return ret;
}
AABB CGraphic::GetCameraAABB(){
	AABB ret;
	D2D1_SIZE_F screenSize = DirectStuff->m_renderTarget->GetSize();
	ret.left = FrameData->camPos.x - screenSize.width / 2 / FrameData->fPixelsPerMeter;
	ret.right = FrameData->camPos.x + screenSize.width / 2 / FrameData->fPixelsPerMeter;
	ret.bottom = FrameData->camPos.y - screenSize.height / 2 / FrameData->fPixelsPerMeter;
	ret.top = FrameData->camPos.y + screenSize.height / 2 / FrameData->fPixelsPerMeter;
	return ret;
}
D2D1_POINT_2F CGraphic::pixToDIP(int x, int y){
	float dpiX, dpiY;
	DirectStuff->m_factory->GetDesktopDpi(&dpiX, &dpiY);
	return{ x / (dpiX / 96), y / (dpiY / 96) };
}
D2D1_POINT_2F CGraphic::pixToDIP(POINT pos){
	float dpiX, dpiY;
	DirectStuff->m_factory->GetDesktopDpi(&dpiX, &dpiY);
	return{ pos.x / (dpiX / 96), pos.y / (dpiY / 96) };
}
D2D1_POINT_2F CGraphic::GetRelativeCursorPos(){
	POINT p;
	GetCursorPos(&p);
	ScreenToClient(System->m_hwnd, &p);
	return pixToDIP({p.x, p.y});
}
positionD CGraphic::GetInWorldPos(D2D1_POINT_2F point){
	D2D1_SIZE_F screenSize = DirectStuff->m_renderTarget->GetSize();
	AABB CamAABB = GetCameraAABB();
	return{ CamAABB.left + (point.x / FrameData->fPixelsPerMeter), CamAABB.bottom + ((screenSize.height - point.y) / FrameData->fPixelsPerMeter) };
}
void CGraphic::RenderFrame(){
	GetClientRect(System->m_hwnd, &System->clientRect);
	DirectStuff->m_renderTarget->Resize(D2D1::SizeU(System->clientRect.right - System->clientRect.left, System->clientRect.bottom - System->clientRect.top));
	

	DirectStuff->m_renderTarget->BeginDraw();
	DirectStuff->m_renderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));
	for (std::list<Renderable*>::iterator it = thingsToRender.begin(); it != thingsToRender.end(); it++){
		(*it)->Render();
	}
	DirectStuff->m_renderTarget->EndDraw();
}
CGraphic::~CGraphic()
{
}
