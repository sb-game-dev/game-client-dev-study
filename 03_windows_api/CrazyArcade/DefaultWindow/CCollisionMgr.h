#pragma once
#include "CObj.h"
class CCollisionMgr
{
public:
	static void CollisionAttack(list<CObj*>& DstList, list<CObj*>& SrcList);
	static void CollisionBody(list<CObj*>& DstList, list<CObj*>& SrcList);


	static void CollisionAttack(vector<CObj*>& DstList, list<CObj*>& SrcList);
	static void CollisionBody(vector<CObj*>& DstList, list<CObj*>& SrcList);
	static void CollisionBody(list<CObj*>& DstList, vector<CObj*>& SrcList);

	static bool CheckRect(CObj* Dst, CObj* Src, float& fDeltaSizeX, float& fDeltaSizeY);
};

