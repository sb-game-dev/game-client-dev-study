#include "CCollisionMgr.h"

//IMPLEMENT_SINGLETON(CCollisionMgr)

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

bool CCollisionMgr::CheckCollision(CCollider* Dst, CCollider* Src)
{
	_vec3 DstCenter = Dst->GetCenter();
	_vec3 SrcCenter = Src->GetCenter();

	_vec3 DstHalfSize = Dst->GetHalfSize();
	_vec3 SrcHalfSize = Src->GetHalfSize();

	if (fabsf(DstCenter.x - SrcCenter.x) < DstHalfSize.x + SrcHalfSize.x
		&& fabsf(DstCenter.y - SrcCenter.y) < DstHalfSize.y + SrcHalfSize.y
		&& fabsf(DstCenter.z - SrcCenter.z) < DstHalfSize.z + SrcHalfSize.z)
	{
		MSG_BOX("Collision");
		return true;
	}
	return false;
}

// 일단 저 함수가 맞는지 확인해야하니까 그냥 클라에서 한번 불러봐야겠지?
