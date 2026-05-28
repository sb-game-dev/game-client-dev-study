#pragma once

#define WINCX	800
#define WINCY	600

#define PI		3.141592f

#define PURE	= 0

#define NONEVENT	0
#define DEAD		1
#define VK_MAX		0xff
extern HWND g_hWnd;

enum OBJID { OBJ_PLAYER, OBJ_OBSTACLE, OBJ_END };

enum MOVE_STATE {
	MOVE_GROUND,
	MOVE_JUMP,
	MOVE_FALL,
	MOVE_DOWNJUMP,
	MOVE_WALL,
	MOVE_ROPE,
	MOVE_TAKEDAMAGER,
	MOVE_TAKEDAMAGEL,
	MOVE_END
};

typedef struct tagInfo
{
	float fX, fY;
	float fCX, fCY;
}INFO;

typedef struct tagLinePoint
{
	float fX, fY;
	tagLinePoint() { ZeroMemory(this, sizeof(tagLinePoint)); }
	tagLinePoint(float _fX, float _fY):fX(_fX), fY(_fY)  {}
}LINEPOINT;

typedef struct tagLine
{
	LINEPOINT tLeft;
	LINEPOINT tRight;

	tagLine() { ZeroMemory(this, sizeof(tagLine)); }
	tagLine(LINEPOINT& _tLeft, LINEPOINT& _tRight) :tLeft(_tLeft), tRight(_tRight) {}

	bool operator==(tagLine rLine)
	{
		if (fabs(tLeft.fX - rLine.tLeft.fX)<=2.f
			&& fabs(tLeft.fY == rLine.tLeft.fY)<=2.f
			&& fabs(tRight.fX == rLine.tRight.fX)<=2.f
			&& fabs(tRight.fY == rLine.tRight.fY)<=2.f)
		{
			return true;
		}
		return false;
	}
}LINE;

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