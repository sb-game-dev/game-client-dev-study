#pragma once
#include "CObj.h"
#include "CTile.h"
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

	static CObj* Create(float fX, float fY, const WCHAR* pFrameKey)
	{
		CObj* pObj = new T;

		pObj->Initialize();
		pObj->SetPos(fX, fY);
		pObj->SetFrameKey(pFrameKey);
		return pObj;
	}
	
	static CObj* Create(float fX, float fY, TILEID eID)
	{
		CObj* pObj = new T;

		pObj->Initialize();
		pObj->SetPos(fX, fY);
		pObj->SetStartFrame(eID);
		return pObj;
	}
};

