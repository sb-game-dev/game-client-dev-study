#pragma once
#define WINCX 800
#define WINCY 600
#define PI 3.141592.f
#define PURE =0
#define NONEVENT 0
#define DEAD 1

extern HWND g_hWnd;
enum DIRECTION{DIR_LEFT,DIR_UP,DIR_RIGHT,DIR_DOWN,DIR_LU,DIR_RU,DIR_END};
enum OBJID{OBJ_PLAYER,OBJ_BOMB,OBJ_MONSTER,OBJ_END};
enum STATE { ST_READY, ST_EXPLODE_READY, ST_EXPLODE_ING, ST_END };
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

struct tagFind
{
	tagFind(const TCHAR* pTag) :m_pTag(pTag) {}
	template<typename T>
	bool operator()(T& pair)
	{
		return !lstrcmp(pair.first, m_pTag);
	}
	const TCHAR* m_pTag;
};