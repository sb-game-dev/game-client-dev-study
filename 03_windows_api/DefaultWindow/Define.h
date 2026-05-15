#pragma once

#define WINCX	800
#define WINCY	600

#define PI		3.141592f

#define PURE	= 0

extern HWND g_hWnd;

typedef struct tagInfo
{
	float fX, fY;
	float fCX, fCY;
}INFO;

template<typename T>
void SafeDelete(T& p)
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
	tagFinder(const TCHAR* pTag) : m_Tag(pTag) {}

	template<typename T>
	bool operator()(T& Pair)
	{
		return !lstrcmp(Pair.first, m_Tag);
	}
	const TCHAR* m_Tag;
};

