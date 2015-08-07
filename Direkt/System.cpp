#include "stdafx.h"
#include "System.h"



CSystem::CSystem()
{
	vs.screenWidth = GetSystemMetrics(SM_CXSCREEN);
	vs.screenHeight = GetSystemMetrics(SM_CYSCREEN);
}
void CSystem::CreateMainWindow(LPCWSTR WindowClassName, LPCWSTR WindowTitle, int resX, int resY, bool bFullScreen){

	m_wc.hInstance = GetModuleHandle(NULL);
	// Setup the windows class with default settings.
	m_wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	m_wc.lpfnWndProc = MessageHandler;
	m_wc.cbClsExtra = 0;
	m_wc.cbWndExtra = 0;
	m_wc.hInstance = m_hinstance;
	m_wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	m_wc.hIconSm = m_wc.hIcon;
	m_wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	m_wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	m_wc.lpszMenuName = NULL;
	m_wc.lpszClassName = WindowClassName;
	m_wc.cbSize = sizeof(WNDCLASSEX);
	RegisterClassEx(&m_wc);
	m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, WindowClassName, WindowTitle, WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW, 0, 0, 0, 0, 0, 0, m_hinstance, 0);
	if (bFullScreen){
		GoFullScreen();
	}
	else{
		GoWindowed(resX,resY);
	}
	
}
void CSystem::GoWindowed(int iWidth, int iHeight){
	int iPosX, iPosY;
	iPosX = (vs.screenWidth - iWidth) / 2;
	iPosY = (vs.screenHeight - iHeight) / 2;
	SetWindowLongPtr(m_hwnd, GWL_STYLE, WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW);
	SetWindowPos(m_hwnd, HWND_TOP, iPosX, iPosY, iWidth, iHeight, NULL);
	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);
	vs.bFullScreen = false;	
}
bool CSystem::GoFullScreen(){

	SetWindowLongPtr(m_hwnd, GWL_STYLE, WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP);
	SetWindowPos(m_hwnd, 0, 0, 0, vs.screenWidth, vs.screenHeight, NULL);
	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);
	vs.bFullScreen = true;
	return true;
}
void CSystem::MessageLoop(){
	MSG msg; 
	while (GetMessage(&msg, NULL, 0, 0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	if (System->programThread.joinable()){ //Sends WM_QUIT to programThread
		PostThreadMessage(GetThreadId(System->programThread.native_handle()), msg.message, msg.wParam, msg.lParam);
	}
}
void CSystem::ShutdownMainWindow(){
	ShowCursor(true);
	if (vs.bFullScreen)
	{
		ChangeDisplaySettings(NULL, 0);
	}
	DestroyWindow(m_hwnd);
	m_hwnd = NULL;
	UnregisterClass(m_wc.lpszClassName, m_hinstance);
	m_hinstance = NULL;
}
void CSystem::StartProgramThread(){
	programThread = std::thread(CSystem::ProgramThreadProcedure);
}
void __cdecl CSystem::ProgramThreadProcedure(){
	MSG msg;
	FrameData->camPos.x = 0;
	FrameData->camPos.y = 128;
	WorldRenderer wr;
	FPSCounter fps;
	bool bActive = false;
	wr.SetActive();
	while (true){
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			switch (msg.message){
				case WM_QUIT:{
					return; //end of thread
				}
				case WM_SYSCOMMAND:{
					if (msg.wParam == SC_MAXIMIZE){
						System->GoFullScreen();
					}
					break;
				}
				case WM_KEYDOWN:{
					if (msg.wParam == VK_F11){
						if (System->vs.bFullScreen){
						System->GoWindowed(1024, 768);
						}
						else{
						System->GoFullScreen();
						}
					}
					else if(msg.wParam == VK_F3){
						if (bActive){
							fps.SetInactive();
							bActive = false;
						}
						else{
							fps.SetActive();
							bActive = true;
						}
					}
					break;
				}
				case WM_MOUSEWHEEL:{
					break;
				}
			}
		}		
		System->Frame();
	}
}
void CSystem::Frame(){
	int iCurrentChunk = InWhichChunk(FrameData->camPos);
	for (int i = iCurrentChunk - 3; i <= iCurrentChunk + 3; i++){
		if (!World.isChunkLoaded(i)){	
			World.GenerateChunk(i);
		}
	}
	FrameData->camAABB = Graphic->GetCameraAABB();
	Graphic->RenderFrame();
}
LRESULT CALLBACK CSystem::MessageHandler(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam){

	switch (umessage)
	{
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
		case WM_CLOSE:
		{
			PostQuitMessage(0);
			return 0;
		}
		default:
		{
			if (System->programThread.joinable()){
				PostThreadMessage(GetThreadId(System->programThread.native_handle()), umessage, wparam, lparam);
			}
			return DefWindowProc(hwnd, umessage, wparam, lparam);
		}
	}
}
CSystem::~CSystem()
{

}

