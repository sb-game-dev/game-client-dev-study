#pragma once

#include "GameObject.h"

NS_BEGIN(Engine)

class ENGINE_DLL CPartObject abstract  : public CGameObject
{
public:
	typedef struct tagPartObjectDesc : public CGameObject::GAMEOBJECT_DESC
	{
		shared_ptr<CTransform>		pParentTransformCom = { nullptr };
	}PARTOBJECT_DESC;

protected:
	CPartObject(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	virtual ~CPartObject() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Priority_Update(f32_t fTimeDelta);
	virtual void Update(f32_t fTimeDelta);
	virtual void Late_Update(f32_t fTimeDelta);
	virtual HRESULT Render();

protected:
	float4x4_t				m_CombinedWorldMatrix = {};
	shared_ptr<CTransform>	m_pParentTransformCom = { nullptr };

protected:
	shared_ptr<CConstantBuffer>		m_pCB = { nullptr };

protected:
	void Update_CombinedWorldMatrix(fmatrix_t ChildMatrix);
	HRESULT Bind_Vertex_ShaderResource(uint32_t iSlot);

public:
	virtual shared_ptr<CPrototype> Clone(void* pArg) = 0;

};

NS_END

