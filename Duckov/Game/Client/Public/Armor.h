#pragma once

#include "Client_Defines.h"
#include "PartObject.h"

NS_BEGIN(Client)

class CArmor final : public CPartObject
{
public:
	typedef struct tagArmorDesc : public CPartObject::PARTOBJECT_DESC
	{
		const float4x4_t* pSocketMatrix = { nullptr };
		const uint32_t* pParentState = { nullptr };
	}ARMOR_DESC;
private:
	CArmor(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	virtual ~CArmor() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Priority_Update(f32_t fTimeDelta) override;
	virtual void Update(f32_t fTimeDelta) override;
	virtual void Late_Update(f32_t fTimeDelta) override;
	virtual HRESULT Render() override;

	HRESULT	Change_Model(const wstring_t& strMeshPath);

private:
	shared_ptr<CVertexShader>				m_pVSCom = { nullptr };
	shared_ptr<CPixelShader>				m_pPSCom = { nullptr };
	shared_ptr<CModel>						m_pModelCom = { nullptr };

	weak_ptr<class CInven>					m_pInven;

private:
	const float4x4_t* m_pSocketMatrix = { nullptr };

private:
	HRESULT Ready_Components();
	HRESULT Bind_Shader();
	HRESULT Bind_ShaderResources(const matrix_t& matWorld);

public:
	static shared_ptr<CArmor> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
	virtual shared_ptr<CPrototype> Clone(void* pArg) override;
};

NS_END