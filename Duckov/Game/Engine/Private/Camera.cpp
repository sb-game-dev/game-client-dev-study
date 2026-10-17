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
void CCamera::Priority_Update(f32_t fDeltTime)
{
}
void CCamera::Update(f32_t fDeltTime)
{
}
void CCamera::Late_Update(f32_t fDeltTime)
{
	XMMATRIX	matView = XMMatrixLookAtLH(XMLoadFloat3(&m_vEye), XMLoadFloat3(&m_vAt), XMLoadFloat3(&m_vUp));
	XMMATRIX	matProj = XMMatrixPerspectiveFovLH(m_fFov, m_fAspect, m_fNear, m_fFar);

	XMStoreFloat4x4(&m_matView, matView);
	XMStoreFloat4x4(&m_matProj, matProj);
}

HRESULT CCamera::Bind()
{
	CB_CAMERA	cbData;
	XMStoreFloat4x4(&cbData.ViewMatrix, XMMatrixTranspose(XMLoadFloat4x4(&m_matView)));
	XMStoreFloat4x4(&cbData.ProjMatrix, XMMatrixTranspose(XMLoadFloat4x4(&m_matProj)));
	cbData.vEye = m_vEye;

	m_pContext->UpdateSubresource(m_pCB.Get(), 0, nullptr, &cbData, 0, 0);
	m_pContext->VSSetConstantBuffers(1, 1, m_pCB.GetAddressOf());
	m_pContext->GSSetConstantBuffers(1, 1, m_pCB.GetAddressOf());
	m_pContext->PSSetConstantBuffers(1, 1, m_pCB.GetAddressOf());
	return S_OK;
}

void CCamera::Update_Frustum()
{
	// 원근 투영행렬을 이용하여 절두체 생성 (뷰스페이스에 있는 절두체)
	// 직교투영행렬을 사용하여 그리는 UI들은 절두체 컬링을 사용하지 않아야한다
	matrix_t	matPorj = XMLoadFloat4x4(&m_matProj);
	BoundingFrustum::CreateFromMatrix(m_tViewFrustum, matPorj); 
	
	// 절두체를 월드로 보내기 위한 뷰 역행렬 저장
	matrix_t	matView = XMLoadFloat4x4(&m_matView);
	XMStoreFloat4x4(&m_MatInvView, XMMatrixInverse(nullptr, matView));
}
