#include "pch.h"
#include "CCollisionMgr.h"
#include "CPlayer.h"
#include "CTile.h"
#include "CBomb.h"
#include "CWave.h"
#include "CObjMgr.h"
#include "CBoss.h"
#include "CItem.h"
#include "CDart.h"
#include "CMonster.h"
#include "CMark.h"
#include "CSoundMgr.h"
#include "CPlayer2.h"

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
				CBomb* pDstBomb = dynamic_cast<CBomb*>(Dst);
				CPlayer* pDstPlayer = dynamic_cast<CPlayer*>(Dst);
				CPlayer2* pDstPlayer2 = dynamic_cast<CPlayer2*>(Dst);

				CPlayer* pSrcPlayer = dynamic_cast<CPlayer*>(Src);
				CPlayer2* pSrcPlayer2 = dynamic_cast<CPlayer2*>(Src);
				if (pDstBomb)
				{
					CDart* pSrcDart = dynamic_cast<CDart*>(Src);
					CObjMgr::GetInstance()->AddObject(OBJ_WAVE, pDstBomb->CreateWave());
					pDstBomb->SetDead();
					if (pSrcDart)
					{
						CSoundMgr::Get_Instance()->PlaySound(L"BubblePop.wav", BOMB_EXPLODE, 0.3f);
						pSrcDart->SetDead();
					}
				}
				else if (pDstPlayer)
				{
					if (pSrcPlayer2 && pDstPlayer->GetCurMotion() == HIT)
						pDstPlayer->SetBossHit();

					if (pDstPlayer->GetShield() == true || pDstPlayer->GetCurMotion() == HIT || pDstPlayer->GetCurMotion() == DEATH || pDstPlayer->GetCurMotion() == DISMOUNT
						|| pDstPlayer->GetCurMotion() == REVIVAL || pDstPlayer->GetCurMotion() == START || pDstPlayer->GetCurMotion() == RESPAWN)
						return;
					CWave* pSrcWave = dynamic_cast<CWave*>(Src);
					CBoss* pSrcBoss = dynamic_cast<CBoss*>(Src);
					CMonster* pSrcMonster = dynamic_cast<CMonster*>(Src);
					if (pSrcBoss && pSrcBoss->GetCurMotion() == BUBBLE)
						pSrcBoss->SetDeath();
#ifdef NDEBUG
					else if(pSrcBoss || pSrcMonster)
						pDstPlayer->SetBossHit();
					else if(pSrcWave)
						pDstPlayer->SetHit();
#endif // NDEBUG
				}
				else if (pDstPlayer2)
				{
					if (pSrcPlayer && pDstPlayer2->GetCurMotion() == HIT)
						pDstPlayer2->SetBossHit();

					if (pDstPlayer2->GetShield() == true || pDstPlayer2->GetCurMotion() == HIT || pDstPlayer2->GetCurMotion() == DEATH || pDstPlayer2->GetCurMotion() == DISMOUNT
						|| pDstPlayer2->GetCurMotion() == REVIVAL || pDstPlayer2->GetCurMotion() == START || pDstPlayer2->GetCurMotion() == RESPAWN)
						return;

					CWave* pSrcWave = dynamic_cast<CWave*>(Src);
					CBoss* pSrcBoss = dynamic_cast<CBoss*>(Src);
					CMonster* pSrcMonster = dynamic_cast<CMonster*>(Src);
					if (pSrcBoss && pSrcBoss->GetCurMotion() == BUBBLE)
						pSrcBoss->SetDeath();
#ifdef NDEBUG
					else if (pSrcBoss || pSrcMonster)
						pDstPlayer2->SetBossHit();
					else if (pSrcWave)
						pDstPlayer2->SetHit();
#endif // NDEBUG
				}
				else if (pSrcPlayer)
				{
					if (pSrcPlayer->GetCurMotion() == HIT || pSrcPlayer->GetCurMotion() == DEATH || pSrcPlayer->GetCurMotion() == DISMOUNT
						|| pSrcPlayer->GetCurMotion() == REVIVAL || pSrcPlayer->GetCurMotion() == START || pSrcPlayer->GetCurMotion() == RESPAWN)
						return;
					CItem* pDstItem = dynamic_cast<CItem*>(Dst);
					CMark* pDstMark = dynamic_cast<CMark*>(Dst);
					if (pDstItem)
					{
						pSrcPlayer->PickUpItem(pDstItem->GetFrameKey());
						pDstItem->SetDead();
					}
					else if (pDstMark && pSrcPlayer && pDstMark->GetDraw() == true)
					{
						pDstMark->SetStartFrame(1);
					}
				}
				else if (pSrcPlayer2)
				{
					if (pSrcPlayer2->GetCurMotion() == HIT || pSrcPlayer2->GetCurMotion() == DEATH || pSrcPlayer2->GetCurMotion() == DISMOUNT
						|| pSrcPlayer2->GetCurMotion() == REVIVAL || pSrcPlayer2->GetCurMotion() == START || pSrcPlayer2->GetCurMotion() == RESPAWN)
						return;
					CItem* pDstItem = dynamic_cast<CItem*>(Dst);
					CMark* pDstMark = dynamic_cast<CMark*>(Dst);
					if (pDstItem)
					{
						pSrcPlayer2->PickUpItem(pDstItem->GetFrameKey());
						pDstItem->SetDead();
					}
					else if (pDstMark && pSrcPlayer2 && pDstMark->GetDraw() == true)
					{
						pDstMark->SetStartFrame(2);
					}
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

			if (pDstBomb && (pDstBomb->GetPlayerCollision() == false || pDstBomb->GetCanMove() == true))
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
				CDart* pSrcDart = dynamic_cast<CDart*>(Src);
				if (pDstTile && pSrWave)
				{
					if (pDstTile->GetFrame().iStart == PUSH || pDstTile->GetFrame().iStart == BREAK || pDstTile->GetFrame().iStart == STAGE3TILE12)
					{
						pSrWave->SetDead();
						pDstTile->SetHit();
					}
				}
				else if (pDstTile && pSrcDart)
				{
					if ((pDstTile->GetFrame().iStart >= 2 && pDstTile->GetFrame().iStart <=10) || pDstTile->GetFrame().iStart>= 18 || pDstTile->GetFrame().iStart >= 31)
						pSrcDart->SetDead();
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

			if (pTempTile->GetFrame().iStart <= 1
				|| (pTempTile->GetFrame().iStart >= 11 && pTempTile->GetFrame().iStart <= 17)
				|| (pTempTile->GetFrame().iStart >= 20 && pTempTile->GetFrame().iStart <= 30))
				continue;
		
			if (CheckRect(DstObj, SrcObj, fDeltaSizeX, fDeltaSizeY))
			{
				if (pSrcBomb)
				{
					pSrcBomb->SetCanMove(false);
					continue;
				}
				//if (fDeltaSizeX < 15.f && fDeltaSizeY < 15.f)
				//{
				//	//SrcObj->SetPosX(AdjustPosX(SrcObj->GetInfo()->fX));
				//	//SrcObj->SetPosY(AdjustPosY(SrcObj->GetInfo()->fY));
				//	return;
				//}
				if (fDeltaSizeX > fDeltaSizeY)
				{
					if (DstObj->GetInfo()->fY < SrcObj->GetInfo()->fY)	
						SrcObj->SetPosY(fDeltaSizeY);
					else												
						SrcObj->SetPosY(-fDeltaSizeY);

					if (DstObj->GetFrame().iStart == PUSH)
						continue;
					if (fDeltaSizeX < 20.f && fDeltaSizeY < 20.f)
					{
						if (DstObj->GetInfo()->fX < SrcObj->GetInfo()->fX)
							SrcObj->SetPosX(3);
						else
							SrcObj->SetPosX(-3);
					}
				}
				else
				{
					if (DstObj->GetInfo()->fX < SrcObj->GetInfo()->fX)
						SrcObj->SetPosX(fDeltaSizeX);
					else
						SrcObj->SetPosX(-fDeltaSizeX);
					if (DstObj->GetFrame().iStart == PUSH)
						continue;
					if (fDeltaSizeX < 20.f && fDeltaSizeY < 20.f)
					{
						if (DstObj->GetInfo()->fY < SrcObj->GetInfo()->fY)
							SrcObj->SetPosY(3);
						else
							SrcObj->SetPosY(-3);
					}
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
			if (pTempTile->GetFrame().iStart <= 1 || (pTempTile->GetFrame().iStart >= 11 && pTempTile->GetFrame().iStart <= 17))
				continue;

			CBomb* pTempBomb = dynamic_cast<CBomb*>(DstObj);
			
			if (CheckRect(DstObj, SrcObj, fDeltaSizeX, fDeltaSizeY))
			{
				if (pTempBomb && pTempBomb->GetCanMove() == false)
				{
					continue;
					pTempBomb->SetPosX(AdjustPosX(pTempBomb->GetInfo()->fX));
					pTempBomb->SetPosY(AdjustPosY(pTempBomb->GetInfo()->fY));
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