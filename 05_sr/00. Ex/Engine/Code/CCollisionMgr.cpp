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
					CGameObject* pDstObj = pDstCollider->GetOwner();
					CGameObject* pSrcObj = pSrcCollider->GetOwner();
					CTransform* pSrcTransform = dynamic_cast<CTransform*> (pSrcObj->Get_Component(ID_DYNAMIC, L"Com_Transform"));
					if (vDS.x > 0)
					{
						pSrcTransform->m_vInfo[INFO_POS].x += fX;
						//pDstObj->CollisionEnter();
					}
					else
					{
						pSrcTransform->m_vInfo[INFO_POS].x -= fX;
					}
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

void CCollisionMgr::Collision(CCollider* pDstCollider, CCollider* pSrcCollider)
{
	// 충돌 확인 후 Trigger 확인
	//if (pDstCollider->GetIsTrigger() || pSrcCollider->GetIsTrigger())
	//{
	//	//pDstCollider->OnTrigger 호출
	//	//pSrcCollider->OnTrigger 호출
	//	return;
	//}

	COLLIDER_TYPE pDstType = pDstCollider->GetColliderType();
	COLLIDER_TYPE pSrcType = pSrcCollider->GetColliderType();

	if (pDstType == COLLIDER_CUBE && pSrcType == COLLIDER_CUBE)
	{
		// 함수 내부에서 호출
		if (pDstCollider->GetIsTrigger() || pSrcCollider->GetIsTrigger())
		{
			//pDstCollider->OnTrigger 호출
			//pSrcCollider->OnTrigger 호출
			return;
		}
		else
		{
			//pDstCollider->OnCollision 호출
			//pSrcCollider->OnCollision 호출
		}
		
	}
	else if (pDstType == COLLIDER_SPHERE && pSrcType == COLLIDER_SPHERE)
	{

	}
	else if (pDstType == COLLIDER_CAPSULE && pSrcType == COLLIDER_CAPSULE)
	{

	}
	else if (pDstType == COLLIDER_CUBE && pSrcType == COLLIDER_SPHERE)
	{

	}
	else if (pDstType == COLLIDER_SPHERE && pSrcType == COLLIDER_CAPSULE)
	{

	}
	else if (pDstType == COLLIDER_CAPSULE && pSrcType == COLLIDER_CUBE)
	{

	}

	return;
}

bool CCollisionMgr::CubevsCube(CCollider* pDstCollider, CCollider* pSrcCollider)
{
	vector<_vec3> vAxis(15);

	CTransform* pDstTransform = dynamic_cast<CTransform*>(pDstCollider->GetOwner()->Get_Component(ID_DYNAMIC, L"Com_Transform"));
	CTransform* pSrcTransform = dynamic_cast<CTransform*>(pSrcCollider->GetOwner()->Get_Component(ID_DYNAMIC, L"Com_Transform"));

	_vec3 vDstAxis,vSrcAxis;
	for (int i = 0; i < 3; ++i)
	{
		memcpy(&vDstAxis, &(pDstTransform->Get_World()->m[i][0]), sizeof(_vec3));
		vAxis.push_back(vDstAxis);

		memcpy(&vSrcAxis, &(pSrcTransform->Get_World()->m[i][0]), sizeof(_vec3));
		vAxis.push_back(vSrcAxis);
		for (int j = 0; j < 3; j++)
		{
			_vec3 vCross;
			D3DXVec3Cross(&vCross, &vDstAxis, &vSrcAxis);
		}
	}

	_vec3 vDstPos;
	_vec3 vSrcPos;
	pDstTransform->Get_Info(INFO_POS, &vDstPos);
	pSrcTransform->Get_Info(INFO_POS, &vSrcPos);
	for (auto Axis : vAxis)
	{
		// 중심좌표 투영
		float fDstCenter = D3DXVec3Dot(&vDstPos, &Axis);
		float fSrcCenter = D3DXVec3Dot(&vSrcPos, &Axis);
		float fDistance = fabsf(fDstCenter - fSrcCenter);

		// 반지름 투영
		_matrix	matDstWorld, matSrcWorld;
		_vec3 vRight, vUp, vLook, vScale;

		matDstWorld = *(pDstTransform->Get_World());

		memcpy(&vRight, &matDstWorld.m[0][0], sizeof(_vec3));
		memcpy(&vUp, &matDstWorld.m[1][0], sizeof(_vec3));
		memcpy(&vLook, &matDstWorld.m[2][0], sizeof(_vec3));
		vScale = pDstTransform->Get_Scale();
		vRight	*= vScale.x;
		vUp		*= vScale.y;
		vLook	*= vScale.z;
		_vec3 vSum = vRight + vUp + vLook;
		float fDstRadius = fabsf(D3DXVec3Dot(&vSum, &Axis) - fDstCenter);

		matSrcWorld = *(pSrcTransform->Get_World());
		memcpy(&vRight, &matSrcWorld.m[0][0], sizeof(_vec3));
		memcpy(&vUp,	&matSrcWorld.m[1][0], sizeof(_vec3));
		memcpy(&vLook,	&matSrcWorld.m[2][0], sizeof(_vec3));
		vScale = pSrcTransform->Get_Scale();
		vRight	*= vScale.x;
		vUp		*= vScale.y;
		vLook	*= vScale.z;
		vSum = vRight + vUp + vLook;

		float fSrcRadius = fabsf(D3DXVec3Dot(&vSum, &Axis) - fSrcCenter);
		if (fDistance > fDstRadius + fSrcRadius)
			return false;
	}
	return true;
}

void CCollisionMgr::AddCollider(OBJID eID, CCollider* pCollider)
{
	if (eID > OBJ_END || pCollider == nullptr)
		return;
	m_ColliderList[eID].push_back(pCollider);
}


