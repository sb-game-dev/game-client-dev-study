#include "pch.h"
#include "CCollisionMgr.h"
#include "CPlayer.h"
#include "CTile.h"
#include "CBomb.h"
#include "CWave.h"
#include "CObjMgr.h"
#include "CBoss.h"
#include "CItem.h"

void CCollisionMgr::CollisionAttack(list<CObj*>& DstList, list<CObj*>& SrcList)
{
	if (DstList.empty() || SrcList.empty())
		return;
	RECT rc;
	for (auto& Dst : DstList)
	{
		for (auto& Src : SrcList)
		{
			if (IntersectRect(&rc, Dst->GetRect(), Src->GetRect()))
			{
				CWave* pSrcWave = dynamic_cast<CWave*>(Src);
				CBomb* pDstBomb = dynamic_cast<CBomb*>(Dst);
				CBoss* pSrcBoss = dynamic_cast<CBoss*>(Src);
				CPlayer* pDstPlayer = dynamic_cast<CPlayer*>(Dst);

				CPlayer* pSrcPlayer = dynamic_cast<CPlayer*>(Src);
				CItem* pDstItem = dynamic_cast<CItem*>(Dst);

				if (pDstBomb)
				{
					CObjMgr::GetInstance()->AddObject(OBJ_WAVE, pDstBomb->CreateWave());
					pDstBomb->SetDead();
				}
				else if (pSrcBoss && pDstPlayer)
				{
					if (pSrcBoss->GetCurMotion() == BUBBLE)
						pSrcBoss->SetDeath();
#ifdef NDEBUG
					else
						pDstPlayer->SetBossHit();
#endif // NDEBUG

				}
				//else if (pDstItem && pSrcWave)
				//{
				//	pDstItem->SetDead();
				//}
				else if (pSrcPlayer)//pDstItem && 
				{
					pSrcPlayer->PickUpItem(pDstItem->GetFrameKey());
					pDstItem->SetDead();
				}
				else
				{
					Dst->SetHit();
				}
			}
		}
	}
}

void CCollisionMgr::CollisionBody(list<CObj*>& DstList, list<CObj*>& SrcList)
{
	if (DstList.empty() || SrcList.empty())
		return;
	float fDeltaSizeX = 0.f, fDeltaSizeY = 0.f;

	for (auto& DstObj : DstList)
	{
		for (auto& SrcObj : SrcList)
		{
			if (DstObj == SrcObj)
				continue;
			
			CBomb* pDstBomb = dynamic_cast<CBomb*> (DstObj);
			CBomb* pSrcBomb = dynamic_cast<CBomb*> (SrcObj);

			if (pDstBomb && pDstBomb->GetPlayerCollision() == false)
				return;

			if (CheckRect(DstObj, SrcObj, fDeltaSizeX, fDeltaSizeY))
			{
				if (pDstBomb && pSrcBomb && pSrcBomb->GetCanMove() == true)
				{
					pSrcBomb->SetCanMove(false);
					return;
				}
				if (fDeltaSizeX > fDeltaSizeY)
				{
					if (DstObj->GetInfo()->fY < SrcObj->GetInfo()->fY)
						SrcObj->SetPosY(fDeltaSizeY);
					else
						SrcObj->SetPosY(-fDeltaSizeY);
				}
				else
				{
					if (DstObj->GetInfo()->fX < SrcObj->GetInfo()->fX)
						SrcObj->SetPosX(fDeltaSizeX);
					else 
						SrcObj->SetPosX(-fDeltaSizeX);
				}
				
			}
		}
	}
}

void CCollisionMgr::CollisionAttack(vector<CObj*>& DstList, list<CObj*>& SrcList)
{
	if (DstList.empty() || SrcList.empty())
		return;
	RECT rc;
	for (auto& Dst : DstList)
	{
		for (auto& Src : SrcList)
		{
			if (IntersectRect(&rc, Dst->GetRect(), Src->GetRect()))
			{
				CWave* pSrWave = dynamic_cast<CWave*>(Src);
				CTile* pDstTile = dynamic_cast<CTile*>(Dst);

				if (pDstTile && pSrWave)
				{
					if (pDstTile->GetFrame().iStart == PUSH || pDstTile->GetFrame().iStart == BREAK)
					{
						pSrWave->SetDead();
						pDstTile->SetHit();
					}
				}
			}
		}
	}
}

void CCollisionMgr::CollisionBody(vector<CObj*>& DstList, list<CObj*>& SrcList)
{
	if (DstList.empty() || SrcList.empty())
		return;
	float fDeltaSizeX = 0.f, fDeltaSizeY = 0.f;

	for (auto& DstObj : DstList)
	{
		for (auto& SrcObj : SrcList)
		{
			if (DstObj == SrcObj)
				continue;
			CTile* pTempTile = dynamic_cast<CTile*> (DstObj);
			CBomb* pSrcBomb = dynamic_cast<CBomb*> (SrcObj);

			if (pTempTile->GetFrame().iStart <= 1)
				continue;

			if (CheckRect(DstObj, SrcObj, fDeltaSizeX, fDeltaSizeY))
			{
				if (fDeltaSizeX > fDeltaSizeY)
				{
					if (DstObj->GetInfo()->fY < SrcObj->GetInfo()->fY)
						SrcObj->SetPosY(fDeltaSizeY);
					else
						SrcObj->SetPosY(-fDeltaSizeY);
				}
				else
				{
					if (DstObj->GetInfo()->fX < SrcObj->GetInfo()->fX)
						SrcObj->SetPosX(fDeltaSizeX);
					else
						SrcObj->SetPosX(-fDeltaSizeX);
				}

			}
		}
	}
}

void CCollisionMgr::CollisionBody(list<CObj*>& DstList, vector<CObj*>& SrcList)
{
	if (DstList.empty() || SrcList.empty())
		return;
	float fDeltaSizeX = 0.f, fDeltaSizeY = 0.f;

	for (auto& DstObj : DstList)
	{
		for (auto& SrcObj : SrcList)
		{
			if (DstObj == SrcObj)
				continue;
			CTile* pTempTile = dynamic_cast<CTile*> (SrcObj);
			if (pTempTile->GetFrame().iStart <= 1)
				continue;

			if (CheckRect(DstObj, SrcObj, fDeltaSizeX, fDeltaSizeY))
			{
				
				if (fDeltaSizeX > fDeltaSizeY)
				{
					if (DstObj->GetInfo()->fY < SrcObj->GetInfo()->fY)
						SrcObj->SetPosY(fDeltaSizeY);
					else
						SrcObj->SetPosY(-fDeltaSizeY);
				}
				else
				{
					if (DstObj->GetInfo()->fX < SrcObj->GetInfo()->fX)
						SrcObj->SetPosX(fDeltaSizeX);
					else
						SrcObj->SetPosX(-fDeltaSizeX);
				}

			}
		}
	}
}

bool CCollisionMgr::CheckRect(CObj* Dst, CObj* Src, float& fDeltaSizeX, float& fDeltaSizeY)
{
	float fSizeX = fabsf(Dst->GetInfo()->fCX + Src->GetInfo()->fCX) * 0.5f;
	float fSizeY = fabsf(Dst->GetInfo()->fCX + Src->GetInfo()->fCX) * 0.5f;

	float fDistanceX = fabsf(Dst->GetInfo()->fX - Src->GetInfo()->fX);
	float fDistanceY = fabsf(Dst->GetInfo()->fY - Src->GetInfo()->fY);

	if (fDistanceX < fSizeX && fDistanceY < fSizeY)
	{
		fDeltaSizeX = fSizeX - fDistanceX;
		fDeltaSizeY = fSizeY - fDistanceY;
		return true;
	}
	return false;
}