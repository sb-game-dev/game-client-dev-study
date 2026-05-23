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

	static CObj* Create(float fX, float fY, float fHp, float fAttack, float fAngle=0)
	{
		CObj* pObj = new T;

		pObj->Initialize();
		pObj->SetPos(fX, fY);
		pObj->SetAbility(fHp, fAttack);
		pObj->SetAngle(fAngle);
		return pObj;
	}

	static CObj* Create(float fX, float fY, float fCX, float fCY,float fHp, float fAttack, float fAngle = 0)
	{
		CObj* pObj = new T;

		pObj->Initialize();
		pObj->SetPos(fX, fY);
		pObj->SetSize(fCX, fCY);
		pObj->SetAbility(fHp, fAttack);
		pObj->SetAngle(fAngle);
		return pObj;
	}
};

