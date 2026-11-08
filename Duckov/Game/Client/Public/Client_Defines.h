#pragma once

// 클라이언트에서 제작하는 클래스들이 이용할 공통적인 것들
#include <Windows.h>
#include <memory>
#include <process.h> 
#include "Engine_Defines.h"
#include "GameInstance.h"
#include "Client_Tags.h"
namespace Client
{
	static constexpr uint32_t g_iWinSizeX = 1280;
	static constexpr uint32_t g_iWinSizeY = 720;
	enum class LEVEL { STATIC, LOADING, LOGO, GAMEPLAY, MAPTOOL, END };	
};

using namespace std;
using namespace Client;
using namespace Engine;

extern HWND	g_hWnd; 
extern HINSTANCE hInst;

#include "Item_Defines.h"

enum class EQUIP_SLOT
{
	GUN_1, GUN_2,       // 총기 ×2
	MELEE,              // 근접 무기
	HEAD, BODY,         // 머리, 신체
	FACE, HEADSET,      // 얼굴, 헤드폰
	BACKPACK,           // 가방
	TOTEM_1, TOTEM_2,   // 토템 ×2
	END
};


enum class QUICK_SLOT
{
	QUICK_3, QUICK_4, QUICK_5,    // 단축키 3~5
	QUICK_6, QUICK_7, QUICK_8,    // 단축키 6~8
	END
};


