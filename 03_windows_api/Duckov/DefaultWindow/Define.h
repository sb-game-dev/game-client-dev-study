#pragma once

#define WINCX		800
#define WINCY		600

#define PI			3.141592f

#define PURE		= 0
#define NONEVENT	0
#define DEAD		1
extern HWND g_hWnd;

enum OBJID { OBJ_PLAYER, OBJ_PLAYER_BULLET, OBJ_MONSTER,OBJ_MONSER_BULLET, OBJ_MOUSE, OBJ_END };
enum WEAPON { WEAPON_MAIN, WEAPON_SUB, WEAPON_END };
enum BULLETTAG { BULLET_PLAYER, BULLET_MONSTER, BULLET_END };
typedef struct tagInfo
{
	float fX, fY;
	float fCX, fCY;

}INFO;

typedef struct tagAbility
{
	float fHp, fAttack;
}ABILITY;

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
	bool operator()(T& pair)
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