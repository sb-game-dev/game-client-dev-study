#pragma once

#include "Client_Defines.h"
#include "PartObject.h"

NS_BEGIN(Client)

class CHelmet_TargetDummy final : public CPartObject
{
public:
	typedef struct tagHelmet_TargetDummyDesc : public CPartObject::PARTOBJECT_DESC
	{
		const float4x4_t* pSocketMatrix = { nullptr }; 
		const wchar_t* pHelmetTag = { nullptr };
	}HELMETTARGETDUMMY_DESC;
private:
	CHelmet_TargetDummy(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	virtual ~CHelmet_TargetDummy() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Priority_Update(f32_t fDeltaTime) override;
	virtual void Update(f32_t fDeltaTime) override;
	virtual void Late_Update(f32_t fDeltaTime) override;
	virtual HRESULT Render() override;

	void	Set_Hit() { m_fHitTimeRemaining = m_fHitDuration; }

private:
	shared_ptr<CVertexShader>				m_pVSCom = { nullptr };
	shared_ptr<CPixelShader>				m_pPSCom = { nullptr };
	shared_ptr<CModel>						m_pModelCom = { nullptr };


private:
	const float4x4_t*	m_pSocketMatrix		= { nullptr };
	const wchar_t*		m_pHelmetTag		= { nullptr };

	f32_t							m_fHitTimeRemaining = { 0.f };	// 남은 시간
	f32_t							m_fHitDuration = { 0.15f };		// 전체 애니메이션 길이
	shared_ptr<CConstantBuffer>		m_pCBHitRatio = { nullptr };
	float4_t						m_vHitRatio = {};

private:
	HRESULT Ready_Components();
	HRESULT	Ready_ConstantBuffer();
	HRESULT	Update_ConstantBuffer();

	HRESULT Bind_Shader();
	HRESULT Bind_ShaderResources(const matrix_t& matWorld);

public:
	static shared_ptr<CHelmet_TargetDummy> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
	virtual shared_ptr<CPrototype> Clone(void* pArg) override;
};

NS_END