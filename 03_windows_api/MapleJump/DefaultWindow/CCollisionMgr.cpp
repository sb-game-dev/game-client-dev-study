#include "pch.h"
#include "CCollisionMgr.h"
#include "CPlayer.h"

void CCollisionMgr::CollisionRect(list<CObj*> DstList, list<CObj*> SrcList)
{
}

void CCollisionMgr::CollisionRectEx(list<CObj*> DstList, list<CObj*> SrcList)
{
}

bool CCollisionMgr::CheckRect(CObj* Dst, CObj* Src, float& fDeltaSizeX, float& fDeltaSizeY)
{
	return false;
}

void CCollisionMgr::CollisionCircle(list<CObj*> DstList, list<CObj*> SrcList)
{
	for (auto& pDst : DstList)
	{
		for (auto& pSrc : SrcList)
		{
			if (CheckCircle(pDst, pSrc))
			{
				pSrc->SetDEAD();
				//dynamic_cast<CPlayer*>(pDst)->SetState(MOVE_TAKEDAMAGE);
				if (pDst->GetInfo().fX < pSrc->GetInfo().fX)
					dynamic_cast<CPlayer*>(pDst)->SetState(MOVE_TAKEDAMAGER);
				else
					dynamic_cast<CPlayer*>(pDst)->SetState(MOVE_TAKEDAMAGEL);
			}
		}
	}
}

bool CCollisionMgr::CheckCircle(CObj* Dst, CObj* Src)
{
	float fDistanceX = Dst->GetInfo().fX - Src->GetInfo().fX;
	float fDistanceY = Dst->GetInfo().fY - Src->GetInfo().fY;

	float fDistance = sqrtf(fDistanceX * fDistanceX + fDistanceY * fDistanceY);

	float fDeltaSize = (Dst->GetInfo().fCX + Src->GetInfo().fCY) * 0.5f;

	return fDistance <= fDeltaSize;
}
