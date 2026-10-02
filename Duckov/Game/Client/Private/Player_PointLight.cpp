#include "Player_PointLight.h"
#include "GameObject.h"

CPlayer_PointLight::CPlayer_PointLight(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
	: CPointLight{ pDevice,pContext }
{
}

HRESULT	 CPlayer_PointLight::Initialize()
{
    // 점조명 구조체 초기화
    m_tPointLight.Ambient = float4_t(0.3f, 0.3f, 0.3f, 1.f);
    m_tPointLight.Diffuse = float4_t(0.7f, 0.7f, 0.7f, 1.f);
    m_tPointLight.Specular = float4_t(0.7f, 0.7f, 0.7f, 1.f);
    m_tPointLight.Att = float3_t(1.f, 0.1f, 0.05f);   // a0 = 1: 가까워도 과노출 안 됨
    m_tPointLight.Range = 3.f;

    // 점조명 상수 버퍼 생성
    D3D11_BUFFER_DESC LightCBDesc{};
    LightCBDesc.ByteWidth = sizeof(CB_POINTLIGHT);
    LightCBDesc.Usage = D3D11_USAGE_DEFAULT;
    LightCBDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

    if (FAILED(m_pDevice->CreateBuffer(&LightCBDesc, nullptr, &m_pLightCB)))
        return E_FAIL;
    return S_OK;
}

void CPlayer_PointLight::Priority_Update(f32_t fDeltaTime)
{
}

void CPlayer_PointLight::Update(f32_t fDeltaTime)
{
}

void CPlayer_PointLight::Late_Update(f32_t fDeltaTime)
{
    // 점조명 위치 초기화
    float3_t vPos = m_pPlayer->GetInfo(INFO::POS);
    m_tPointLight.Position = float3_t(vPos.x, vPos.y + 2.f, vPos.z);

    // 조명 상수 버퍼 채우기
    CB_POINTLIGHT cbLight;
    cbLight.tPointLight = m_tPointLight;

    // 갱신하고 PS b2에 꽂기
    m_pContext->UpdateSubresource(m_pLightCB.Get(), 0, nullptr, &cbLight, 0, 0);
    m_pContext->PSSetConstantBuffers(2, 1, m_pLightCB.GetAddressOf());
}

shared_ptr<CPlayer_PointLight> CPlayer_PointLight::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
	auto pInstance = shared_ptr<CPlayer_PointLight>(new CPlayer_PointLight(pDevice, pContext));
	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX("Create Fail : CPlayer_PointLight");
		pInstance.reset();
	}
	return pInstance;
}
