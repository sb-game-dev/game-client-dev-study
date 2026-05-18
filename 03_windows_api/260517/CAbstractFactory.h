#pragma once
#include "CObj.h"
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

	static CObj* Create(float fX, float fY, float fHp,float fAttack, DIRECTION eDir=DIR_END)
	{
		CObj* pObj = new T;

		pObj->Initialize();
		pObj->SetStat({ fHp,fAttack });
		pObj->SetPos(fX, fY);
		pObj->SetDir(eDir);

		return pObj;
	}

};

