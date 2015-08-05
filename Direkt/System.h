#pragma once
#include "Graphic.h"
#include "World.h"
#include "Structs.h"
struct ViewSettings{
	bool bFullScreen;
	int screenWidth,screenHeight;
};
class CSystem
{
public:
	CGraphic Gr;
	CWorld World;
	ViewSettings vs;
	Fd fd;
	HINSTANCE m_hinstance;
	HWND m_hwnd;
	WNDCLASSEX m_wc;
	RECT clientRect;
	std::thread programThread, loadingThread;
	static void ProgramThreadProcedure();
	static void LoadingThreadProcedure();
	void Frame();
	void StartProgramThread();
	void StartLoadingThread();
	void CreateMainWindow(LPCWSTR WindowClassName, LPCWSTR WindowTitle, int iWidth, int iHeight, bool bFullScreen);
	bool GoFullScreen();
	void GoWindowed(int iWidth, int iHeight);
	void MessageLoop();
	void ShutdownMainWindow();
	static LRESULT CALLBACK MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam);
	CSystem();
	~CSystem();
};
extern CSystem* System;
extern Fd* FrameData;