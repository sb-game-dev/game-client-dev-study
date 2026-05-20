#include "pch.h"
#include "CCollisionMgr.h"

void CCollisionMgr::CollisionRect(list<CObj*> DstList, list<CObj*> SrcList)
{
	RECT rc;
	for (auto& DstObj : DstList)
	{
		for (auto& SrcObj : SrcList)
		{
			if (IntersectRect(&rc, (DstObj->GetRect()), (SrcObj->GetRect())))
			{
				DstObj->SetDead();
				SrcObj->SetDead();
			}
		}
	}
}

void CCollisionMgr::CollisionCircle(list<CObj*> DstList, list<CObj*> SrcList)
{
	for (auto& DstObj : DstList)
	{
		for (auto& SrcObj : SrcList)
		{
			if (CheckCircle(DstObj, SrcObj))
			{
				DstObj->SetDead();
				SrcObj->SetDead();
			}
		}
	}
}

bool CCollisionMgr::CheckCircle(CObj* pDst, CObj* pSrc)
{
	double fDistance = sqrt((pDst->GetInfo().fX - pSrc->GetInfo().fX) * (pDst->GetInfo().fX - pSrc->GetInfo().fX)
		+ (pDst->GetInfo().fY - pSrc->GetInfo().fY) * (pDst->GetInfo().fY - pSrc->GetInfo().fY));
	double fSize = (pDst->GetInfo().fCX - pSrc->GetInfo().fCX) * 0.5f;

	return fDistance <= fSize;
}
