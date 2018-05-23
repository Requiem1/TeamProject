// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>
#include <d3dx9.h>
#include <assert.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <set>
#include <map>

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")



#ifdef _DEBUG
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#endif 

#define SAFE_WNDPROC(p) if(p) {(p)->WndProc(hWnd,message,wParam,lParam);}
#define SAFE_UPDATE(p) if(p) { (p)->Update();}
#define SAFE_RENDER(p) if(p) { (p)->Render();}
#define SAFE_RELEASE(p) if(p) { (p)->Release(); (p) = NULL;}
#define SAFE_DELETE(p) if(p) { delete (p); (p) = NULL;}

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.

extern HWND g_hWnd;

//using std::set;
//using std::map;
//using std::string;

// 추가 헤더 인클루드
#include "../portfolio/Manager/Application.h"
#include "../portfolio/Manager/DeviceManager.h"
#include "../portfolio/Manager/BaseObject.h"
#include "../portfolio/Manager/GlobalDefinition.h"
#include "../portfolio/Manager/Camera.h"
#include "../portfolio/Manager/D3DUtility.h"
#include "../portfolio/Manager/IDisplayObject.h"
#include "../portfolio/Player/Player.h"
#include "../portfolio/Manager/PlayerManager.h"
#include "../Portfolio/Manager/SceneManager.h"
#include "../Portfolio/Manager/TextureManager.h"
#include "../Portfolio/Manager/DisplayObjManager.h"
#include "../Portfolio/Manager/InputManager.h"