#pragma once

#include "Engine_Defines.h"
#include "GameObject.h"
NS_BEGIN(Engine)
class ENGINE_DLL CLevel abstract //객체화 되지 않는다(x) 자식객체를 생성해야만 객체화 된다.(O)
{
protected:
	CLevel(ComPtr<ID3D11Device>pDevice, ComPtr<ID3D11DeviceContext> pContext);

public:
	virtual ~CLevel() = default;
public:
	virtual HRESULT Initialize();
	virtual void	Update(f32_t fDeltaTime);
	virtual void	LateUpdate(f32_t fDeltaTime);
	virtual HRESULT	Render();


protected:
	map<const wstring_t, shared_ptr<CGameObject>> m_mapObject;

protected:
	ComPtr<ID3D11Device>		m_pDevice = { nullptr };
	ComPtr<ID3D11DeviceContext> m_pContext = { nullptr };
};
NS_END
