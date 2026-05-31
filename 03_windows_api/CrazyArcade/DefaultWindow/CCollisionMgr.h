#pragma once
#include "CObj.h"
class CCollisionMgr
{
public:
	static void CollisionAttack(list<CObj*>& DstList, list<CObj*>& SrcList);
	static void CollisionBody(list<CObj*>& DstList, list<CObj*>& SrcList);
	static bool CheckRect(CObj* Dst, CObj* Src, float& fDeltaSizeX, float& fDeltaSizeY);


	static void CollisionCircle(list<CObj*>& DstList, list<CObj*>& SrcList);
	static bool CheckCircle(CObj* pDst, CObj* pSrc);
};

