#pragma once
#include "CCollider.h"
#include "CTransform.h"
#include "CGameObject.h"

BEGIN(Engine)

class ENGINE_DLL CCollisionMgr
{
	DECLARE_SINGLETON(CCollisionMgr)
private:
	explicit CCollisionMgr();
	virtual ~CCollisionMgr();

public:
	virtual void FixedUpdate_Component();
	virtual _int Update_Component(const _float& fTimeDelta);
	virtual void LateUpdate_Component();

public:
	bool	CheckCollision(CCollider* pDst, CCollider* pSrc, float* fX, float* fY, float* fZ);
	void	PhysicalCollision(CCollider* pDst, CCollider* pSrc);

};

END