#pragma once
#define WINCX 800
#define WINCY 600
#define PI 3.141592f
#define PURE =0
#define NONEVENT 0
#define DEAD 1

extern HWND g_hWnd;

enum DIRECTION{DIR_LEFT,DIR_TOP,DIR_RIGHT,DIR_BOTTOM,DIR_LU,DIR_RU,DIR_END};
enum OBJID { OBJ_PLAYER, OBJ_BULLET, OBJ_MONSTER, OBJ_MOUSE, OBJ_END };

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

struct tagSafeDelete
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

struct tagFind
{
	tagFind(const TCHAR* pTag) : m_pTag(pTag) {}
	template<typename T>
	bool operator()(T& pair)
	{
		return !lstrcmp(m_pTag,pair.first);
	}
	const TCHAR* m_pTag;
};