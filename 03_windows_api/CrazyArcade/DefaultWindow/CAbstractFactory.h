#pragma once
#include "CObj.h"
#include "CBlock.h"
template<typename T>
class CAbstractFactory
{
public:
	CAbstractFactory() {}
	~CAbstractFactory() {}

public:
	static CObj* Create()
	{
		CObj* pObj = new T;

		pObj->Initialize();
		return pObj;
	}
	//static CObj* Create(float fX, float fY)
	//{
	//	CObj* pObj = new T;
	//
	//	pObj->Initialize();
	//	pObj->SetPos(fX, fY);
	//	return pObj;
	//}
	static CObj* Create(float fX, float fY,DIRECTION eDir = DIR_END)
	{
		CObj* pObj = new T;

		pObj->Initialize();
		pObj->SetPos(fX, fY);
		pObj->SetDir(eDir);
		return pObj;
	}

	static CObj* Create(float fX, float fY, BLOCK_TYPE eBT)
	{
		CObj* pObj = new T;

		pObj->Initialize();
		pObj->SetPos(fX, fY);
		dynamic_cast<CBlock*> (pObj)->SetType(eBT);
		//pObj->SetDir(eDir);
		return pObj;
	}
};

