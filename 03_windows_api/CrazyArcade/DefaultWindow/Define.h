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
#define TILECY		67

#define fMarkDeltaX 14.f
#define fMarkDeltaY 8.5f

extern HWND g_hWnd;
extern int  m_iBombCnt;
enum TILEID { TILE1, TILE2, PUSH, BREAK, WALL1, WALL2, WALL3, WALL4, WALL5, WALL6, WALL7, 
	STAGE2TILE1, STAGE2TILE2, STAGE2TILE3, STAGE2TILE4, STAGE2TILE5, STAGE2TILE6, STAGE2TILE7, STAGE2TILE8, STAGE2TILE9, TILE_END };

enum SCENEID { SC_LOGO, SC_MENU, SC_EDIT, SC_SHOP, SC_STAGE1, SC_STAGE2, SC_STAGE3,SC_STAGE4, SC_END };

enum OBJID { OBJ_MARK, OBJ_BOMB, OBJ_BOSS_BOMB, OBJ_DART, OBJ_SHEID, OBJ_BUTTON, OBJ_WAVE, OBJ_ITEM, OBJ_MONSTER, OBJ_BOSS,  OBJ_PLAYER, OBJ_MOUSE, OBJ_END };

enum RENDERID { BACKGROUND, GAMEOBJECT, EFFECT, UI,MOUSE, RENDER_END };

enum DIRECTION { DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT, DIR_END };

enum MOTION { START, IDLE, UP, LEFT, DOWN, RIGHT, ATTACK, HIT, BUBBLE, DEATH, REVIVAL, MOTION_END };

enum ITEMTYPE { IT_NEEDLE, IT_SHIELD, IT_DART, IT_TRAMPOLINE, IT_END }; 

enum CHANNELID { SOUND_BGM, SOUND_EFFECT, 
	BUTTON_CURSOR, BUTTON_CLICK, 
	BOMB_PUTDOWN, BOMB_EXPLODE, 
	PLAYER_BUBBLE,PLAYER_DEAD,
	SOUND_ITEMGAIN, SOUND_DART, SOUND_NEDDLE,
	STAGE_START, STAGE_WIN, STAGE_LOSE, 
	MAXCHANNEL };

typedef struct tagInven
{
	int iNeedleCnt;
	int iDartCnt;
	int iShieldCnt;
}INVEN;

typedef struct tagIntRect
{
	int iLeft;
	int iTop;
	int iRight;
	int iBottom;
}INTRECT;
typedef struct tagNode
{
	int m_iNodeID;
	int m_iParendtID;
	int m_iFscore;
	int m_iGscore;
	int m_iHscore;
}NODE;
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