#pragma once
#include "CCollider.h"

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
	bool	CheckCollision(CCollider* Dst, CCollider* Src);

};

END