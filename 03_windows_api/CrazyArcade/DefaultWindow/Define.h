#pragma once

#define WINCX	800
#define WINCY	600

#define PI		3.141592f

#define PURE	= 0
#define NOEVENT 0
#define DEAD 1
#define VK_MAX 0xff
extern HWND g_hWnd;

enum SCENEID { SC_LOGO, SC_EDIT, SC_STAGE1, SC_STAGE2, SC_STAGE3, SC_END };
enum OBJID { OBJ_PLAYER, OBJ_MONSTER, OBJ_TILE, OBJ_BOMB, OBJ_WAVE, OBJ_MOUSE, OBJ_SHEID, OBJ_BUTTON, OBJ_END };
enum DIRECTION{DIR_UP,DIR_DOWN,DIR_LEFT,DIR_RIGHT};

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
