#pragma once
#include"Client_Defines.h"
#include "PartObject.h"
NS_BEGIN(Client)
class CBody_TargetDummy :public CPartObject
{
public:
	typedef struct tagBodyTargetDummyDesc : public CPartObject::PARTOBJECT_DESC
	{
		float4_t* pGroundPlane = { nullptr };
	}BODYTARGETDUMMY_DESC;
private:
	CBody_TargetDummy(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	virtual ~CBody_TargetDummy() = default;

public:
	const float4x4_t* Get_SocketMatrix(const char_t* pBoneName);

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;

	virtual void Priority_Update(f32_t fDeltaTime) override;
	virtual void Update(f32_t fDeltaTime) override;
	virtual void Late_Update(f32_t fDeltaTime) override;

	virtual HRESULT Render() override;
	virtual HRESULT	Render_Shadow() override;

	const BoundingBox& Get_AABB() { return m_pModelCom->GetBoundingBox(); }

private:
	float4_t						m_vGroundPlane = { 0.f, 1.f, 0.f, 0.f };	// ¹ß¹Ø Æò¸é (a,b,c,d)

	shared_ptr<CModel>				m_pModelCom = { nullptr };
	shared_ptr<CVertexShader>		m_pVSCom = { nullptr };
	shared_ptr<CPixelShader>		m_pPSCom = { nullptr };
	shared_ptr<CPixelShader>		m_pPS_Shadow = { nullptr };

private:
	HRESULT Ready_Components();

	HRESULT Bind_Shader(shared_ptr<CVertexShader> pVS = nullptr, shared_ptr<CPixelShader> pPS = nullptr);
	HRESULT Bind_ShaderResources(const matrix_t& matWorld);

	HRESULT	Render_Mesh(const matrix_t& matWorld, shared_ptr<CPixelShader> pPS);

public:
	static shared_ptr<CBody_TargetDummy> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
	virtual shared_ptr<CPrototype> Clone(void* pArg) override;
};

NS_END