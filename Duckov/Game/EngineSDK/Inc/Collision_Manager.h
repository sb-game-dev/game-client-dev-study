#pragma once
#include "Engine_Defines.h"

NS_BEGIN(Engine)
class CCollision_Manager
{
private:
	CCollision_Manager() = default;
public:
	~CCollision_Manager() = default;

public:
	void Collision(shared_ptr<class CCollider> pDstCollider, shared_ptr<class CCollider> pSrcCollider);

public:
	static unique_ptr<CCollision_Manager> Create();
};

NS_END