#pragma once

#define WINCX	800
#define WINCY	600

//게임 칸의 크기는 가로 605, 세로 530
//	가로(X) -> 15 ~ 620
//	세로(Y) -> 40 ~	570
// 테스트

#define TILECX 605
#define TILECY 530

#define TILE_CNT_X 15
#define TILE_CNT_Y 13

#define TILE_START_X 20
#define TILE_START_Y 40

#define PI		3.141592f
#define	INF		123456789
#define PURE	= 0

#define PlayerImgX 70.f
#define PlayerImgY 70.f

#define TILECX 40
#define TILECY 40

#define NONEVENT 0
#define DEAD 1
#define	VK_MAX 0xff
extern HWND g_hWnd;

enum DIRECTION { DIR_LEFT, DIR_UP, DIR_RIGHT, DIR_DOWN, DIR_LEFTEND, DIR_UPEND, DIR_RIGHTEND, DIR_DOWNEND, DIR_END };
enum OBJID { OBJ_BOMB, OBJ_WATER, OBJ_MONSTER, OBJ_BLOCK, OBJ_MOUSE, OBJ_ITEM, OBJ_UI, OBJ_PLAYER, OBJ_END };
enum MOTIONSTATE { MOTION_IDLE, MOTION_WALK, MOTION_HIT, MOTION_DEATH, MOTION_END };

enum ITEM_TYPE { IT_BOMB_UP, IT_POWER_UP, IT_SPEED_UP, IT_NEEDLE, IT_END };
enum SCENEID { SC_LOGO, SC_MENU, SC_EDIT, SC_STAGE, SC_END };

enum TILEID{ TILE_NORMAL, TILE_MOUSE, TILE_PUSH,TILE_BREAK,TILE_WALL,TILE_END};

typedef struct tagInfo
{
	float fX, fY;
	float fCX, fCY;

}INFO;

typedef struct tagFrame
{
	int		iStart;
	int		iEnd;
	int		iMotion;
	DWORD	dwSpeed;
	DWORD	dwTime;
}FRAME;
typedef struct tagRenderInfo
{
	int iFrameStart, iFrameEnd, dwFrameSpeed;
	int iRectStartX, iRectStartY;
}RENDERINFO;

template<typename T>
void Safe_Delete(T& p)
{
	if (p)
	{
		delete p;
		p = nullptr;
	}
}

struct tagDelete
{
	template<typename T>
	void operator()(T& p)
	{
		if (p)
		{
			delete p;
			p = nullptr;
		}
	}
};
struct tagDeleteMap
{
	template<typename T>
	void operator()(T& pair)
	{
		if (pair.second)
		{
			delete pair.second;
			pair.second = nullptr;
		}
	}
};

struct tagFinder
{
	tagFinder(const TCHAR* pTag) : m_pTag(pTag) {}

	template<typename T>
	bool operator()(T& Pair)
	{
		return !lstrcmp(Pair.first, m_pTag);
	}

	const TCHAR* m_pTag;
};