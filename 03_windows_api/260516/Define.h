#pragma once
#define WINCX 800
#define WINCY 600

#define PI 3.141592f
#define PURE =0

extern HWND g_hWnd;
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
	tagFinder(const TCHAR* pTag) :m_pTag(pTag) {}

	template<typename T>
	bool operator()(T& pair)
	{
		return !lstrcmp(pair.first, m_pTag);
	}
	const TCHAR* m_pTag;
};