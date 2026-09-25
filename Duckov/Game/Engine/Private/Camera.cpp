#include "Camera.h"

CCamera::CCamera(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
	: m_pDevice{ pDevice }
	, m_pContext{ pContext }
{
	XMMATRIX matI = XMMatrixIdentity();
	XMStoreFloat4x4(&m_matView, matI);
	XMStoreFloat4x4(&m_matProj, matI);
}
HRESULT CCamera::Initialize()
{
	D3D11_BUFFER_DESC	CBDesc{};
	CBDesc.ByteWidth = sizeof(CB_CAMERA);
	CBDesc.Usage = D3D11_USAGE_DEFAULT;
	CBDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	if (FAILED(m_pDevice->CreateBuffer(&CBDesc, nullptr, m_pCB.GetAddressOf())))
		return E_FAIL;
	return S_OK;
}
void CCamera::Update(f32_t fDeltTime)
{

}
void CCamera::LateUpdate(f32_t fDeltTime)
{
	XMMATRIX	matView = XMMatrixLookAtLH(XMLoadFloat3(&m_vEye), XMLoadFloat3(&m_vAt), XMLoadFloat3(&m_vUp));
	XMMATRIX	matProj = XMMatrixPerspectiveFovLH(m_fFov, m_fAspect, m_fNear, m_fFar);

	XMStoreFloat4x4(&m_matView, matView);
	XMStoreFloat4x4(&m_matProj, matProj);
}
HRESULT CCamera::Render()
{
	return S_OK;
}

HRESULT CCamera::Bind()
{
	CB_CAMERA	cbData;
	XMStoreFloat4x4(&cbData.ViewMatrix, XMMatrixTranspose(XMLoadFloat4x4(&m_matView)));
	XMStoreFloat4x4(&cbData.ProjMatrix, XMMatrixTranspose(XMLoadFloat4x4(&m_matProj)));

	m_pContext->UpdateSubresource(m_pCB.Get(), 0, nullptr, &cbData, 0, 0);
	m_pContext->VSSetConstantBuffers(1, 1, m_pCB.GetAddressOf());
	return S_OK;
}


shared_ptr<CCamera> CCamera::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
	auto pInstance = shared_ptr<CCamera>(new CCamera(pDevice, pContext));
	if (FAILED(pInstance->Initialize()))
		pInstance.reset();
	return pInstance;
}