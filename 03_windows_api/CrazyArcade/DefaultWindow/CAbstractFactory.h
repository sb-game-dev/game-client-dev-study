#pragma once
#include "CObj.h"
template<typename T>
class CAbstractFactory
{
public:
	CAbstractFactory() {}
	~CAbstractFactory() {}

public:
	static CObj* Create(float fX, float fY)
	{
		CObj* pObj = new T;

		pObj->Initialize();
		pObj->SetPos(fX, fY);
		return pObj;
	}

	static CObj* Create(float fX, float fY, WCHAR* pFrameKey)
	{
		CObj* pObj = new T;

		pObj->Initialize();
		pObj->SetPos(fX, fY);
		pObj->SetFrameKey(pFrameKey);
		return pObj;
	}
};

