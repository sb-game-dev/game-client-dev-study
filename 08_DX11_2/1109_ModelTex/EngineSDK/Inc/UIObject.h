#pragma once

#include "GameObject.h"

NS_BEGIN(Engine)

class ENGINE_DLL CUIObject abstract : public CGameObject
{
public:
	typedef struct tagUIObjectDesc : public CGameObject::GAMEOBJECT_DESC
	{
		f32_t		fX{}, fY{}, fSizeX{}, fSizeY{};
	}UIOBJECT_DESC;

protected:
	CUIObject(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	virtual ~CUIObject() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Priority_Update(f32_t fTimeDelta);
	virtual void Update(f32_t fTimeDelta);
	virtual void Late_Update(f32_t fTimeDelta);
	virtual HRESULT Render();

protected:
	f32_t			m_fX{}, m_fY{}, m_fSizeX{}, m_fSizeY{};
	uint32_t		m_iWinSizeX{}, m_iWinSizeY{};
protected:
	void Update_State();

public:
	virtual shared_ptr<CPrototype> Clone(void* pArg) = 0;

};

NS_END