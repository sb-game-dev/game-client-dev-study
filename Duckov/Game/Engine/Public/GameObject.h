#pragma once
#include "Engine_Defines.h"
NS_BEGIN(Engine)
class ENGINE_DLL CGameObject
{
protected:
	CGameObject(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	virtual ~CGameObject() = default;

public:
	virtual HRESULT		Initialize();
	virtual void		Update(f32_t fDeltaTime);
	virtual void		LateUpdate(f32_t fDeltaTime);
	virtual HRESULT		Render();
	

	virtual	void		SetPos(float3_t vPos) { m_vInfo[static_cast<uint32_t>(INFO::POS)] = vPos; }
	virtual	void		MovePos(XMVECTOR vDir, f32_t fSpeed, f32_t fDeltaTime);
	virtual	void		SetWorld(XMMATRIX matWorld)		{ XMStoreFloat4x4(&m_matWorld, matWorld); }
	virtual	void		SetWorld(float4x4_t matWorld)	{ m_matWorld = matWorld; }
	virtual	float3_t	GetInfo(INFO eID)				{ return m_vInfo[static_cast<int>(eID)]; }

	virtual XMMATRIX	GetWorld();

protected:
	ComPtr<ID3D11Device>				m_pDevice = { nullptr };
	ComPtr<ID3D11DeviceContext>			m_pContext = { nullptr };

	ComPtr<ID3D11Buffer>				m_pVB;				// 버텍스 버퍼
	ComPtr<ID3D11Buffer>				m_pIB;				// 인덱스 버퍼
	uint32_t							m_iIndexCnt;		// 인덱스 개수
	ComPtr<ID3D11Buffer>				m_pCB;				// 변환 정보를 가지고있는 상수버퍼

	ComPtr<ID3D11InputLayout>			m_pInputLayout;		// 정점 메모리 해석표(FVF의 역할)

	ComPtr<ID3D11VertexShader>			m_pVS;				// 버텍스 셰이더
	ComPtr<ID3D11PixelShader>			m_pPS;				// 픽셀 셰이더
	ComPtr<ID3D11RasterizerState>		m_pRS;				// 레스터라이저

	float4x4_t			m_matWorld;

	float3_t			m_vInfo[static_cast<int>(INFO::END)];

	float3_t			m_vScale = { 1.f,1.f,1.f };
	
	f32_t               m_fRotX = 0.f;
	f32_t               m_fRotY = 0.f;
	f32_t               m_fRotZ = 0.f;

	f32_t				m_fSpeed = 1.f;
};
NS_END
