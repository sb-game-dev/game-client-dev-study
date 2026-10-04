#include "Orthographic_Cam.h"

COrthographic_Cam::COrthographic_Cam(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
	:CCamera{ pDevice, pContext }
{
}

COrthographic_Cam::~COrthographic_Cam()
{
}

HRESULT COrthographic_Cam::Initialize()
{
	if (FAILED(__super::Initialize()))
		return E_FAIL;
	m_vUp = { 0.f,1.f,0.f };
	m_vEye = { 0.f,0.f,0.f };
	m_vAt = { 0.f,0.f,1.f };

	return S_OK;
}

void COrthographic_Cam::Update(f32_t fDeltaTime)
{
	__super::Update(fDeltaTime);

}

void COrthographic_Cam::Late_Update(f32_t fDeltaTime)
{
	__super::Late_Update(fDeltaTime);

	XMMATRIX	matProj = XMMatrixOrthographicLH(g_iWinSizeX, g_iWinSizeY, m_fNear, m_fFar);
	XMStoreFloat4x4(&m_matProj, matProj);
}

shared_ptr<COrthographic_Cam> COrthographic_Cam::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
	auto pInstance = shared_ptr<COrthographic_Cam>(new COrthographic_Cam(pDevice, pContext));
	if (FAILED(pInstance->Initialize()))
		pInstance.reset();
	return pInstance;
}