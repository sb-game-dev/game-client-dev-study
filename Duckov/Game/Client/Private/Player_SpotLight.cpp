#include "Player_SpotLight.h"
#include "GameObject.h"

CPlayer_SpotLight::CPlayer_SpotLight(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    : CSpotLight{ pDevice,pContext }
{
}

HRESULT	 CPlayer_SpotLight::Initialize()
{
    // 스포트라이트 조명 구조체 초기화
    m_tSpotLight.Ambient = float4_t(0.3f, 0.3f, 0.3f, 1.f);
    m_tSpotLight.Diffuse = float4_t(0.7f, 0.7f, 0.7f, 1.f);
    m_tSpotLight.Specular = float4_t(0.7f, 0.7f, 0.7f, 1.f);
    m_tSpotLight.Att = float3_t(1.f, 0.1f, 0.05f);   // a0 = 1: 가까워도 과노출 안 됨
    m_tSpotLight.Range = 100.f;
    m_tSpotLight.Spot = 10.f;   // 원뿔이 얼마나 좁은지 정하는 지수

    // 스포트라이트 조명 상수 버퍼 생성
    D3D11_BUFFER_DESC LightCBDesc{};
    LightCBDesc.ByteWidth = sizeof(CB_SPOTLIGHT);
    LightCBDesc.Usage = D3D11_USAGE_DEFAULT;
    LightCBDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

    if (FAILED(m_pDevice->CreateBuffer(&LightCBDesc, nullptr, &m_pLightCB)))
        return E_FAIL;
    return S_OK;
}

void CPlayer_SpotLight::Priority_Update(f32_t fDeltaTime)
{
}

void CPlayer_SpotLight::Update(f32_t fDeltaTime)
{
}

void CPlayer_SpotLight::Late_Update(f32_t fDeltaTime)
{
    // 스포트라이트 조명 위치, 방향 초기화
    float3_t vPos = m_pPlayer->GetInfo(INFO::POS);
    m_tSpotLight.Position = float3_t(vPos.x, vPos.y + 2.f, vPos.z);
    m_tSpotLight.Direction = m_pPlayer->GetInfo(INFO::LOOK);

    // 조명 상수 버퍼 채우기
    CB_SPOTLIGHT cbLight;
    cbLight.tSpotLight = m_tSpotLight;

    // 갱신하고 PS b4에 꽂기
    m_pContext->UpdateSubresource(m_pLightCB.Get(), 0, nullptr, &cbLight, 0, 0);
    m_pContext->PSSetConstantBuffers(4, 1, m_pLightCB.GetAddressOf());
}

shared_ptr<CPlayer_SpotLight> CPlayer_SpotLight::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
    auto pInstance = shared_ptr<CPlayer_SpotLight>(new CPlayer_SpotLight(pDevice, pContext));
    if (FAILED(pInstance->Initialize()))
    {
        MSG_BOX("Create Fail : CPlayer_SpotLight");
        pInstance.reset();
    }
    return pInstance;
}
