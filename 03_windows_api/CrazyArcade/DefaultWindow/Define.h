#pragma once

#define WINCX		800
#define WINCY		600

#define PI			3.141592f

#define PURE		= 0
#define NOEVENT		0
#define DEAD		1
#define VK_MAX		0xff

#define PLAYER_CX	50
#define PLAYER_CY	59

#define MAP_LEFT	20
#define MAP_RIGHT	620

#define MAP_TOP		40
#define MAP_BOTTOM	560

#define MAP_CX		600
#define MAP_CY		520
#define MAP_CNT_X	15
#define MAP_CNT_Y	13

#define TILECX		40
#define TILECY		56
extern HWND g_hWnd;
extern int  m_iBombCnt;
enum TILEID { TILE1, TILE2, PUSH, BREAK, WALL1, WALL2, WALL3, WALL4, WALL5, WALL6, WALL7, TILE_END };

enum SCENEID { SC_LOGO, SC_EDIT, SC_STAGE1, SC_STAGE2, SC_STAGE3, SC_END };

enum OBJID { OBJ_BOMB, OBJ_MONSTER_BOMB, OBJ_DART, OBJ_SHEID, OBJ_BUTTON, OBJ_WAVE, OBJ_ITEM, OBJ_MONSTER, OBJ_BOSS, OBJ_PLAYER, OBJ_MOUSE, OBJ_END };

enum RENDERID { BACKGROUND, GAMEOBJECT, EFFECT, UI,MOUSE, RENDER_END };

enum DIRECTION { DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT, DIR_END };

enum MOTION { START, IDLE, LEFT, RIGHT, UP, DOWN, ATTACK, HIT, BUBBLE, DEATH, REVIVAL, MOTION_END };


typedef struct tagFrame
{
	int iStart;
	int iEnd;
	int iMotion;
	bool bLoop;
	int iCX;
	int iCY;
	ULONGLONG dwSpeed;
	ULONGLONG dwTime;
}FRAME;
typedef struct tagInfo
{
	float fX, fY;
	float fCX, fCY;

}INFO;

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
	bool operator()(T& p)
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

inline void MakeAlphaAttr(ImageAttributes& attr, float alpha)
{
	ColorMatrix matrix =
	{
		1,0,0,0,0,
		0,1,0,0,0,
		0,0,1,0,0,
		0,0,0,alpha,0,
		0,0,0,0,1
	};
	attr.SetColorMatrix(&matrix);
}

inline int AdjustPosX(float fX) 
{ 
	return (int)(fX - 20) / 40 * 40 + 40;
}

inline int	AdjustPosY(float fY)
{ 
	return (int)(fY - 40) / 40 * 40 + 60;
}

inline bool CheckInMap(float fX, float fY)
{
	if (fX < MAP_RIGHT && fX>MAP_LEFT && fY >MAP_TOP && fY <MAP_BOTTOM)
		return true;
	return false;
}