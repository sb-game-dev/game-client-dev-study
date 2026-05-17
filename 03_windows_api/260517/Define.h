#pragma once
#define WINCX 800
#define WINCY 600
#define PURE =0
#define PI 3.141592f

extern HWND g_Hwnd;

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