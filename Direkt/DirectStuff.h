#pragma once
class CDirectStuff
{
public:
	ID2D1Factory* m_factory;
	ID2D1HwndRenderTarget* m_renderTarget;
	ID2D1SolidColorBrush *firstBrush;
	ID2D1SolidColorBrush *secondBrush;
	void Initialize();
	void Cleanup();
	CDirectStuff();
	~CDirectStuff();
};
extern CDirectStuff* DirectStuff;
