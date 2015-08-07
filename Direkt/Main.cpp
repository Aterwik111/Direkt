#include "stdafx.h"
#include <fstream>
CSystem* System = NULL;
CGraphic* Graphic = NULL;
CDirectStuff* DirectStuff = NULL;
CWorld* World = NULL;
Fd* FrameData = NULL;

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	CSystem sys;
	System = &sys;
	Graphic = &System->Gr;
	DirectStuff = &Graphic->DS;
	World = &System->World;
	FrameData = &System->fd;

	System->CreateMainWindow(L"MainWindow", L"Window",1024,768, false);
	DirectStuff->Initialize();
	System->StartProgramThread();
	System->MessageLoop();
	System->programThread.join();
	DirectStuff->Cleanup();
	System->ShutdownMainWindow();
	return 0;
}
