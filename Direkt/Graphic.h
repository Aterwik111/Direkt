#pragma once
#include "stdafx.h"
#include "DirectStuff.h"
#include "Renderable.h"
#include "Structs.h"
class CGraphic
{
public:
	D2D1_POINT_2F CalculatePositionOnScreen(positionD point);
	D2D1_RECT_F RectFromPoints(D2D1_POINT_2F p1, D2D1_POINT_2F p2);
	D2D1_POINT_2F pixToDIP(int x, int y);
	D2D1_POINT_2F pixToDIP(POINT pos);
	D2D1_POINT_2F GetRelativeCursorPos();
	positionD GetInWorldPos(D2D1_POINT_2F point);
	AABB GetCameraAABB();
	CDirectStuff DS;
	std::list <Renderable*> thingsToRender;
	void RenderFrame();
	CGraphic();
	~CGraphic();
};
extern CGraphic* Graphic;

