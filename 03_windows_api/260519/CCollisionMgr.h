#pragma once
#include "CObj.h"
class CCollisionMgr
{
public:
	static void CollisionRect(list<CObj*> DstList, list<CObj*> SrcList);

	static void CollisionRectEx(list<CObj*> DstList, list<CObj*> SrcList);
	static bool CheckRect(CObj* Dst, CObj* Src, float& fDeltaSizeX, float& fDeltaSizeY);

	static void CollisionCircle(list<CObj*> DstList, list<CObj*> SrcList);
	static bool CheckCircle(CObj* pDst, CObj* pSrc);
};

