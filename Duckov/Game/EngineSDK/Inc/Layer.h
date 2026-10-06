#pragma once
#include "Engine_Defines.h"
NS_BEGIN(Engine)
class CGameObject;
class CLayer
{
private:
	CLayer();
public:
	~CLayer() = default;

public:
	HRESULT		Add_GameObject(const wstring_t& strGameObjectTag ,shared_ptr<class CGameObject> pGameObject);
	void		Priority_Update(f32_t fTimeDelta);
	void		Update(f32_t fTimeDelat);
	void		Late_Update(f32_t fTimeDelta);
	HRESULT		Render();

	shared_ptr<CGameObject>	Find_GameObject(const wstring_t& strGameObjectTag);

private:
	map<const wstring_t, shared_ptr<CGameObject>>		m_GameObjects;

public:
	static shared_ptr<CLayer>	Create();
};

NS_END