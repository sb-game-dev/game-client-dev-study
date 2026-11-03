#pragma once

#include "Engine_Defines.h"

/* 사용자의 기준에 따라 객체들을 모은다. */

NS_BEGIN(Engine)

class CLayer final
{
private:
	CLayer();
public:
	~CLayer() = default;

public:
	HRESULT Add_GameObject(shared_ptr<class CGameObject> pGameObject);
	void Priority_Update(f32_t fTimeDelta);
	void Update(f32_t fTimeDelta);
	void Late_Update(f32_t fTimeDelta);

private:
	list<shared_ptr<class CGameObject>>			m_GameObjects;

public:
	static shared_ptr<CLayer> Create();
};

NS_END