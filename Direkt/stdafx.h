// stdafx.h: do³¹cz plik do standardowych systemowych plików do³¹czanych,
// lub specyficzne dla projektu pliki do³¹czane, które s¹ czêsto wykorzystywane, ale
// s¹ rzadko zmieniane
//

#pragma once
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Wyklucz rzadko u¿ywane rzeczy z nag³ówków systemu Windows
// Pliki nag³ówkowe systemu Windows:
#include <windows.h>

// Pliki nag³ówkowe œrodowiska uruchomieniowego C
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <iostream>
#include <fstream>
#include <string>  
#include <math.h>  
#include <d2d1.h>
#include <d2d1helper.h>
#include <Dwrite.h>
#include <thread>
#include <mutex>
#include <vector>
#include <map>
#include <array>
#include <list>

#pragma comment( lib, "d2d1.lib" ) 
#pragma comment( lib, "Dwrite.lib" ) 

#define CHUNK_WIDTH (16)
#define WORLD_HEIGHT (256)




#include "Direkt.h"
#include "System.h"
#include "Graphic.h"
#include "DirectStuff.h"
#include "Timer.h"
#include "Structs.h"
#include "World.h"
#include "Synchronization.h"
#include "Renderable.h"
#include "WorldRenderer.h"
#include "FPSCounter.h"

#define SafeRelease(ptr)	if(ptr!=NULL){ptr->Release(); ptr=NULL;}
#define SafeCloseHandle(handle)	if(handle!=NULL && handle!=INVALID_HANDLE_VALUE){CloseHandle(handle);}
#define synchronized(M)  for(SyncLock M##_lock = M; M##_lock; M##_lock.setUnlock())

