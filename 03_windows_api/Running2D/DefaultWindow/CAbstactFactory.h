#pragma once
#include "CObj.h"
template<typename T>
class CAbstactFactory
{
public:
	static CObj* Create()
	{
		CObj* pObj = new T;

		pObj->Initialize();
		return pObj;
	}


	static CObj* Create(float fX,float fY)
	{
		CObj* pObj = new T;

		pObj->Initialize();
		pObj->SetPos(fX, fY);
		return pObj;
	}
};

