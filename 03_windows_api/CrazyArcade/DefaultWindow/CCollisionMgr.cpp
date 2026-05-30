#include "pch.h"
#include "CCollisionMgr.h"
#include "CBomb.h"
#include "CObjMgr.h"
void CCollisionMgr::CollisionRect(list<CObj*>& DstList, list<CObj*>& SrcList)
{
	RECT rc;
	for (auto& Dst : DstList)
	{
		for (auto& Src : SrcList)
		{
			if (IntersectRect(&rc, Dst->GetRect(), Src->GetRect()))
			{
				CBomb* pTempBomb = dynamic_cast<CBomb*>(Dst);
				if (pTempBomb)
					CObjMgr::GetInstance()->AddObject(OBJ_WATER, pTempBomb->CreateWater());
				Dst->SetDead();
			}
		}
	}
}
void CCollisionMgr::CollisionRectEX(list<CObj*>& DstList, list<CObj*>& SrcList)
{
	float fDeltaSizeX = 0.f, fDeltaSizeY = 0.f;

	for (auto& DstObj : DstList)
	{
		for (auto& SrcObj : SrcList)
		{
			CBomb* pTempBomb = dynamic_cast<CBomb*>(DstObj);
			if (pTempBomb && pTempBomb->GetPlayerCollision() == true)
				return;

			if (CheckRect(DstObj, SrcObj, fDeltaSizeX, fDeltaSizeY))
			{
				// ╩С го
				if (fDeltaSizeX > fDeltaSizeY)
				{
					// го
					if (DstObj->GetInfo().fY < SrcObj->GetInfo().fY)
					{
						SrcObj->SetPosY(fDeltaSizeY);
					}
					// ╩С
					else
					{
						SrcObj->SetPosY(-fDeltaSizeY);
					}
				}
				// аб ©Л
				else
				{
					//©Л
					if (DstObj->GetInfo().fX < SrcObj->GetInfo().fX)
					{
						SrcObj->SetPosX(fDeltaSizeX);
					}
					//аб
					else
					{
						SrcObj->SetPosX(-fDeltaSizeX);
					}
				}
			}
		}
	}
}
bool CCollisionMgr::CheckRect(CObj* Dst, CObj* Src, float& fDeltaSizeX, float& fDeltaSizeY)
{
	float fSizeX = fabsf(Dst->GetInfo().fCX + Src->GetInfo().fCX) * 0.5f;
	float fSizeY = fabsf(Dst->GetInfo().fCX + Src->GetInfo().fCX) * 0.5f;

	float fDistanceX = fabsf(Dst->GetInfo().fX - Src->GetInfo().fX);
	float fDistanceY = fabsf(Dst->GetInfo().fY - Src->GetInfo().fY);

	if (fDistanceX < fSizeX && fDistanceY < fSizeY)
	{
		fDeltaSizeX = fSizeX - fDistanceX;
		fDeltaSizeY = fSizeY - fDistanceY;
		return true;
	}
	return false;
}

void CCollisionMgr::CollisionCircle(list<CObj*>& DstList, list<CObj*>& SrcList)
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
	float fSize = (pDst->GetInfo().fCX + pSrc->GetInfo().fCX) * 0.5f;

	float fWidth = (pDst->GetInfo().fX - pSrc->GetInfo().fX);
	float fHeight = (pDst->GetInfo().fY - pSrc->GetInfo().fY);

	float fDistance = sqrtf(fWidth * fWidth + fHeight * fHeight);

	return fDistance <= fSize;
}
