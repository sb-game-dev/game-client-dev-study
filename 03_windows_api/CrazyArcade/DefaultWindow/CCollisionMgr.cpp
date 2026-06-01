#include "pch.h"
#include "CCollisionMgr.h"
#include "CBomb.h"
#include "CObjMgr.h"
#include "CPlayer.h"
#include "CBlock.h"
#include "CItem.h"
void CCollisionMgr::CollisionAttack(list<CObj*>& DstList, list<CObj*>& SrcList)
{
	RECT rc;
	for (auto& Dst : DstList)
	{
		for (auto& Src : SrcList)
		{
			if (IntersectRect(&rc, Dst->GetRect(), Src->GetRect()))
			{
				CBomb* pDstBomb = dynamic_cast<CBomb*>(Dst);
				CBomb* pSrcBomb = dynamic_cast<CBomb*>(Src);
				CPlayer* pDstPlayer = dynamic_cast<CPlayer*>(Dst);
				CPlayer* pSrcPlayer = dynamic_cast<CPlayer*>(Src);
				CItem* pDstItem = dynamic_cast<CItem*>(Dst);
				CBlock* pDstBlock = dynamic_cast<CBlock*>(Dst);

				if (pDstBomb)
				{
					CObjMgr::GetInstance()->AddObject(OBJ_WATER, pDstBomb->CreateWater());
					Dst->SetDead();
				}
				else if (pDstPlayer)
				{
					pDstPlayer->SetBubble();
				}
				else if (pDstItem && pSrcPlayer)
				{
					switch (pDstItem->GetType())
					{
					case IT_BOMB_UP:
						pSrcPlayer->UpBomb();
						break;
					case IT_POWER_UP:
						pSrcPlayer->UpPower();
						break;
					case IT_SPEED_UP:
						pSrcPlayer->UpSpeed();
						break;
					case IT_NEEDLE:
						break;

					default:
						break;
					}
					Dst->SetDead();
				}
				else if(pDstBlock)
				{
					if(lstrcmp(pDstBlock->GetFrameKey(),L"Wall"))
						Dst->SetDead();
				}
				else
				{
					Dst->SetDead();
				}
			}
		}
	}
}
void CCollisionMgr::CollisionBody(list<CObj*>& DstList, list<CObj*>& SrcList)
{
	float fDeltaSizeX = 0.f, fDeltaSizeY = 0.f;

	for (auto& DstObj : DstList)
	{
		for (auto& SrcObj : SrcList)
		{
			if (DstObj == SrcObj)
				continue;
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
