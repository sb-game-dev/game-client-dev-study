#include "CCollisionMgr.h"
#include "CManagement.h"

#include <io.h>
#include <iostream>

IMPLEMENT_SINGLETON(CCollisionMgr)

CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::FixedUpdate_Component()
{
}

_int CCollisionMgr::Update_Component(const _float& fTimeDelta)
{
	return 0;
}
void CCollisionMgr::LateUpdate_Component()
{
}

bool CCollisionMgr::CheckCollision(CCollider* pDst, CCollider* pSrc, float* fX, float* fY, float* fZ)
{
	_vec3 DstCenter = pDst->GetCenter();
	_vec3 SrcCenter = pSrc->GetCenter();

	_vec3 DstHalfSize = pDst->GetHalfSize();
	_vec3 SrcHalfSize = pSrc->GetHalfSize();

	if (fabsf(DstCenter.x - SrcCenter.x) <= DstHalfSize.x + SrcHalfSize.x
		&& fabsf(DstCenter.y - SrcCenter.y) <= DstHalfSize.y + SrcHalfSize.y
		&& fabsf(DstCenter.z - SrcCenter.z) <= DstHalfSize.z + SrcHalfSize.z)
	{
		*fX = (DstHalfSize.x + SrcHalfSize.x) - fabsf(DstCenter.x - SrcCenter.x);
		*fY = (DstHalfSize.y + SrcHalfSize.y) - fabsf(DstCenter.y - SrcCenter.y);
		*fZ = (DstHalfSize.z + SrcHalfSize.z) - fabsf(DstCenter.z - SrcCenter.z);

		return true;
	}
	return false;
}

bool CCollisionMgr::PhysicalCollision(CCollider* pDst, CCollider* pSrc)
{
	float fX, fY, fZ;

	if (CheckCollision(pDst, pSrc, &fX, &fY, &fZ))
	{
		_vec3 DstCenter = pDst->GetCenter();
		_vec3 SrcCenter = pSrc->GetCenter();

		_vec3 vDS = SrcCenter - DstCenter;

		if (fX == min(fX, fY, fZ))
		{
			CGameObject* pSrcObj = pSrc->GetOwner();
			CTransform* pSrcTransform = dynamic_cast<CTransform*> (pSrcObj->Get_Component(ID_DYNAMIC, L"Com_Transform"));
			if (vDS.x > 0)
				pSrcTransform->m_vInfo[INFO_POS].x += fX;
			else 
				pSrcTransform->m_vInfo[INFO_POS].x -= fX;
			return true;
		}

		if (fY == min(fX, fY, fZ))
		{
			CGameObject* pSrcObj = pSrc->GetOwner();
			CTransform* pSrcTransform = dynamic_cast<CTransform*> (pSrcObj->Get_Component(ID_DYNAMIC, L"Com_Transform"));
			if (vDS.y > 0)
			{
				pSrcTransform->m_vInfo[INFO_POS].y += fY;
				//pSrcTransform->m_eMoveState = RIDING;
			}
			else
			{
				pSrcTransform->m_vInfo[INFO_POS].y -= fY;
				//pSrcTransform->m_eMoveState = FALL;
			}
			return true;
		}

		if (fZ == min(fX, fY, fZ))
		{
			CGameObject* pSrcObj = pSrc->GetOwner();
			CTransform* pSrcTransform = dynamic_cast<CTransform*> (pSrcObj->Get_Component(ID_DYNAMIC, L"Com_Transform"));
			if (vDS.z > 0)
				pSrcTransform->m_vInfo[INFO_POS].z += fZ;
			else 
				pSrcTransform->m_vInfo[INFO_POS].z -= fZ;
			return true;
		}
	}
	else
	{
		return false;
		CGameObject* pSrcObj = pSrc->GetOwner();
		CTransform* pSrcTransform = dynamic_cast<CTransform*> (pSrcObj->Get_Component(ID_DYNAMIC, L"Com_Transform"));
		if(pSrcTransform->m_ePreMoveState == RIDING)
		{
			pSrcTransform->m_eMoveState = FALL;
		}
	}
}

bool CCollisionMgr::PhysicalCollision(OBJID eDstID, OBJID eSrcID)
{
	bool bCollision = false;
	for (auto pDstCollider : m_ColliderList[eDstID]) 
	{
		for (auto pSrcCollider : m_ColliderList[eSrcID])
		{
			float fX, fY, fZ;
			if (CheckCollision(pDstCollider, pSrcCollider, &fX, &fY, &fZ))
			{
				_vec3 DstCenter = pDstCollider->GetCenter();
				_vec3 SrcCenter = pSrcCollider->GetCenter();

				_vec3 vDS = SrcCenter - DstCenter;

				if (fX == min(fX, fY, fZ))
				{
					CGameObject* pSrcObj = pSrcCollider->GetOwner();
					CTransform* pSrcTransform = dynamic_cast<CTransform*> (pSrcObj->Get_Component(ID_DYNAMIC, L"Com_Transform"));
					if (vDS.x > 0)
						pSrcTransform->m_vInfo[INFO_POS].x += fX;
					else
						pSrcTransform->m_vInfo[INFO_POS].x -= fX;
					//bCollision = true;
				}

				if (fY == min(fX, fY, fZ))
				{
					CGameObject* pSrcObj = pSrcCollider->GetOwner();
					CTransform* pSrcTransform = dynamic_cast<CTransform*> (pSrcObj->Get_Component(ID_DYNAMIC, L"Com_Transform"));
					if (vDS.y > 0)
					{
						pSrcTransform->m_vInfo[INFO_POS].y += fY;
						//pSrcTransform->m_eMoveState = RIDING;
					}
					else
					{
						pSrcTransform->m_vInfo[INFO_POS].y -= fY;
						//pSrcTransform->m_eMoveState = FALL;
					}
					bCollision = true;
				}

				if (fZ == min(fX, fY, fZ))
				{
					CGameObject* pSrcObj = pSrcCollider->GetOwner();
					CTransform* pSrcTransform = dynamic_cast<CTransform*> (pSrcObj->Get_Component(ID_DYNAMIC, L"Com_Transform"));
					if (vDS.z > 0)
						pSrcTransform->m_vInfo[INFO_POS].z += fZ;
					else
						pSrcTransform->m_vInfo[INFO_POS].z -= fZ;
					//bCollision = true;
				}
			}
		}
	}
	if (bCollision)return true;
	return false;
	
}

void CCollisionMgr::AddCollider(OBJID eID, CCollider* pCollider)
{
	if (eID > OBJ_END || pCollider == nullptr)
		return;
	m_ColliderList[eID].push_back(pCollider);
}


