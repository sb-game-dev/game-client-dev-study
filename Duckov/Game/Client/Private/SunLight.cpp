#include "SunLight.h"

CSunLight::CSunLight(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
	:CDirectionalLight(pDevice,pContext)
{
}

HRESULT CSunLight::Initialize()
{
	// 방향성 조면 구조체 생성
	m_tDirectionalLight.Ambient		= XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f);
	m_tDirectionalLight.Diffuse		= XMFLOAT4(0.25f, 0.25f, 0.25f, 1.0f);
	m_tDirectionalLight.Specular	= XMFLOAT4(0.25f, 0.25f, 0.25f, 1.0f);
	m_tDirectionalLight.Direction	= XMFLOAT3(0.5f, -0.5f, 0.5f);

	// 방향성 조명 상수 버퍼 생성
	D3D11_BUFFER_DESC LightCBDesc{};
	LightCBDesc.ByteWidth = sizeof(CB_DIRLIGHT);
	LightCBDesc.Usage = D3D11_USAGE_DEFAULT;
	LightCBDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	if (FAILED(m_pDevice->CreateBuffer(&LightCBDesc, nullptr, &m_pLightCB)))
		return E_FAIL;
	return S_OK;
}

void CSunLight::Priority_Update(f32_t fDeltaTime)
{
}

void CSunLight::Update(f32_t fDeltaTime)
{
}

void CSunLight::Late_Update(f32_t fDeltaTime)
{
	// 조명 상수 버퍼 채우기
	CB_DIRLIGHT cbLight;
	cbLight.tDirLight = m_tDirectionalLight;

	// 갱신하고 PS b3에 꽂기
	m_pContext->UpdateSubresource(m_pLightCB.Get(), 0, nullptr, &cbLight, 0, 0);
	m_pContext->PSSetConstantBuffers(3, 1, m_pLightCB.GetAddressOf());
}

shared_ptr<CSunLight> CSunLight::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
	auto pInstance = shared_ptr<CSunLight>(new CSunLight(pDevice,pContext));
	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX("Create Failed : CSunLight");
		pInstance.reset();
	}
	return pInstance;
}
