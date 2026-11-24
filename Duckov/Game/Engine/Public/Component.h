#pragma once

#include "Prototype.h"

NS_BEGIN(Engine)

class ENGINE_DLL CComponent abstract : public CPrototype
{
protected:
	CComponent(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	virtual ~CComponent() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;

	virtual void	Set_Owner(shared_ptr<class CGameObject> pGameObject) { m_pOwner = pGameObject; }
	virtual weak_ptr<class CGameObject> Get_Owner() { return m_pOwner; }
protected:
	weak_ptr<class CGameObject> m_pOwner;

public:
	virtual shared_ptr<CPrototype> Clone(void* pArg) PURE;

};

NS_END