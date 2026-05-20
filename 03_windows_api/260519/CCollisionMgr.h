#pragma once
#include "CObj.h"
class CCollisionMgr
{
public:
	static void CollisionRect(list<CObj*> DstList, list<CObj*> SrcList);
	static void CollisionCircle(list<CObj*> DstList, list<CObj*> SrcList);
	static bool CheckCircle(CObj* pDst, CObj* pSrc);
};

