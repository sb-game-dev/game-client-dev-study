#pragma once
#define WINCX 800
#define WINCY 600
#define PURE =0
#define PI 3.141592f
#define NONEVENT 0
#define DEAD 1

extern HWND g_Hwnd;

enum DIRECTION { DIR_RIGHT, DIR_LEFT, DIR_UP, DIR_DOWN, DIR_RU, DIR_LU, DIR_END };
enum OBJID{OBJ_PLAYER,OBJ_BULLET,OBJ_MONSTER,OBJ_SHILED,OBJ_UI,OBJ_END};

enum BULLETSTATE { READY, EXPLODE, EXPLODE_END, STATE_END };
typedef struct tagInfo
{
	float fX, fY;
	float fCX, fCY;
}INFO;

typedef struct tagStat
{
	float fHp, fAttack;
}STAT;

template<typename T>
void Safe_Delete(T& p)
{
	if (p)
	{
		delete p;
		p = nullptr;
	}
}

template<typename T>
struct tagSafeDelete
{
	void operator()(T& p)
	{
		if (p)
		{
			delete p;
			p = nullptr;
		}
	}
};

template<typename T>
struct tagDeleteMap
{
	void operator()(T& pair)
	{
		if (pair.second)
		{
			delete pair.second;
			pair.second = nullptr;
		}
	}
};

template<typename T>
struct tagFind
{
	tagFind(const TCHAR* pTag) : m_pTag(pTag) {}
	bool operator()(T& pair)
	{
		return !lstrcmp(m_pTag, pair.first);
	}
	const TCHAR* m_pTag;
};