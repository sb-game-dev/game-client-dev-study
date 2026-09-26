#pragma once
#include "Engine_Defines.h"

NS_BEGIN(Engine)
class ENGINE_DLL CCamera
{
protected:
	CCamera(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	virtual ~CCamera() = default;

public:
	virtual	HRESULT		Initialize();
	virtual	void		Update(f32_t fDeltTime);
	virtual	void		LateUpdate(f32_t fDeltTime);
	virtual HRESULT		Render();

	const float4x4_t&	GetView() { return m_matView; }
	const float4x4_t&	GetProj() { return m_matProj; }

	virtual HRESULT	Bind();

protected:
	ComPtr<ID3D11Device>				m_pDevice = { nullptr };
	ComPtr<ID3D11DeviceContext>			m_pContext = { nullptr };

	ComPtr<ID3D11VertexShader>			m_pVS = { nullptr };
	ComPtr<ID3D11Buffer>				m_pCB = { nullptr };

	float4x4_t			m_matView;
	float4x4_t			m_matProj;

	float3_t			m_vEye = { 0.f,0.f,-3.f };
	float3_t			m_vAt = { 0.f,0.f,0.f };
	float3_t			m_vUp = { 0.f,1.f,0.f };

	f32_t				m_fFov = XMConvertToRadians(60.f);
	f32_t				m_fAspect = (f32_t)1280 / 720;
	f32_t				m_fNear = 0.1f;
	f32_t				m_fFar = 1000.f;

public:
	static	shared_ptr<CCamera>	Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
};

NS_END