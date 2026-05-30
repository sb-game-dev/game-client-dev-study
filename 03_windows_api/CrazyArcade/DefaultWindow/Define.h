#pragma once

#define WINCX	800
#define WINCY	600
//게임 칸의 크기는 가로 600, 세로 520
#define PI		3.141592f

#define PURE	= 0

#define NONEVENT 0
#define DEAD 1
#define	VK_MAX 0xff
extern HWND g_hWnd;
enum DIRECTION { DIR_LEFT, DIR_UP, DIR_RIGHT, DIR_DOWN, DIR_LU, DIR_RU, DIR_END };
enum OBJID { OBJ_BOMB, OBJ_WATER, OBJ_MONSTER, OBJ_BLOCK, OBJ_PLAYER,OBJ_MOUSE, OBJ_END };
enum STATE { ST_READY, ST_EXPLODE_READY, ST_EXPLODE_ING, ST_END };

typedef struct tagInfo
{
	float fX, fY;
	float fCX, fCY;

}INFO;

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