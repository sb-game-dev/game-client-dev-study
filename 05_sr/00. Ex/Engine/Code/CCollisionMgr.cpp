#include "CCollisionMgr.h"
#include "CManagement.h"

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

	if (fabsf(DstCenter.x - SrcCenter.x) < DstHalfSize.x + SrcHalfSize.x
		&& fabsf(DstCenter.y - SrcCenter.y) < DstHalfSize.y + SrcHalfSize.y
		&& fabsf(DstCenter.z - SrcCenter.z) < DstHalfSize.z + SrcHalfSize.z)
	{
		*fX = fabsf(fabsf(DstCenter.x - SrcCenter.x) - (DstHalfSize.x + SrcHalfSize.x));
		*fY = fabsf(fabsf(DstCenter.y - SrcCenter.y) - (DstHalfSize.y + SrcHalfSize.y));
		*fZ = fabsf(fabsf(DstCenter.z - SrcCenter.z) - (DstHalfSize.z + SrcHalfSize.z));


		return true;
	}
	return false;
}

void CCollisionMgr::PhysicalCollision(CCollider* pDst, CCollider* pSrc, CTransform* pSrcTransform)
{
	float fX, fY, fZ;

	if (CheckCollision(pDst, pSrc, &fX, &fY, &fZ))
	{
		_vec3 DstCenter = pDst->GetCenter();
		_vec3 SrcCenter = pSrc->GetCenter();

		_vec3 vDS = SrcCenter - DstCenter;

		if (fX == min(fX, fY, fZ))
		{
			if (vDS.x > 0)
				pSrcTransform->m_vInfo[INFO_POS].x += fX;
			else 
				pSrcTransform->m_vInfo[INFO_POS].x -= fX;
		}

		if (fY == min(fX, fY, fZ))
		{
			if (vDS.y > 0)
			{
				pSrcTransform->m_vInfo[INFO_POS].y += fY;
				pSrcTransform->m_eMoveState = RIDING;
			}
			else
			{
				pSrcTransform->m_vInfo[INFO_POS].y -= fY;
				pSrcTransform->m_eMoveState = FALL;
			}
		}

		if (fZ == min(fX, fY, fZ))
		{
			if (vDS.z > 0)
				pSrcTransform->m_vInfo[INFO_POS].z += fZ;
			else 
				pSrcTransform->m_vInfo[INFO_POS].z -= fZ;
		}
	}
	else
	{
		cout << "CollisionExit" << endl;
		if(pSrcTransform->m_ePreMoveState == RIDING)
		{
			pSrcTransform->m_eMoveState = FALL;
		}
	}
}


