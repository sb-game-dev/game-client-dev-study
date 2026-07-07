#pragma once

#define WINCX	800
#define WINCY	600

#define PI		3.141592f

#define PURE	= 0

extern HWND g_hWnd;

typedef struct tagInfo
{
	D3DXVECTOR3		vPos;		// 위치 벡터
	D3DXVECTOR3		vDir;		// 방향 벡터
	D3DXVECTOR3		vLook;		// 방향 벡터

	D3DXVECTOR3		vNormal;	// 방향 벡터(법선 벡터)

}INFO;

// 벡터의 상등 : 방향과 크기가 일치하는 벡터는 완전히 같은 벡터
 
// 단위 벡터 : 벡터의 크기가 1인 상태를 말함
// 벡터의 정규화 : 벡터의 크기가 1이 되도록 만드는 과정

// 벡터의 곱셈은 본래 없으나 벡터의 곱셈이라 불리는 두 과정이 있다.

// 내적 : x * x` + y * y` + z * z`, 상수(스칼라) 곱, 두 방향 벡터 사이의 끼인 각을 구하는 용도로 자주 사용(절대 벡터의 내적의 결과가 끼인 각이라는 말은 아니다!!!!)

// - 두 방향 벡터의 크기가 단위 벡터로 정규화가 되어 있고, 두 방향 벡터의 내적의 결과를
// 역함수를 이용하여 각도를 추출하는 용도로 사용 할 수 있다.


// 외적 : 벡터 곱, 3D 공간이 아닌 곳에서는 외적은 사용 불가, 두 방향 벡터와 모두 직각을 이루는 방향 벡터를 구하는 용도로 사용

// x	y	z
// 
// x`  y`  z`
// 
// (y * z` - z * y`, x * z` - z * x`, x * y` - y * x`)

inline float GetLength(float fX, float fY)
{
	return sqrtf(fX * fX + fY * fY);
}

inline float GetCos(const D3DXVECTOR3& vDst, const D3DXVECTOR3& vSrc)
{
	float fDstLength = GetLength(vDst.x, vDst.y);
	float fSrcLength = GetLength(vSrc.x, vSrc.y);
	
	float fDstX = vDst.x / fDstLength;
	float fDstY = vDst.y / fDstLength;	

	float fSrcX = vSrc.x / fSrcLength;
	float fSrcY = vSrc.y / fSrcLength;

	return fDstX * fSrcX + fDstY * fSrcY;
}

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
	tagFinder(const TCHAR* pTag) : m_pTag(pTag) {}

	template<typename T>
	bool operator()(T& Pair)
	{
		return !lstrcmp(Pair.first, m_pTag);
	}

	const TCHAR* m_pTag;
};

static D3DXVECTOR3 GetMouse()
{
	POINT	pt{};

	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	return D3DXVECTOR3((float)pt.x, (float)pt.y, 0.f);
}