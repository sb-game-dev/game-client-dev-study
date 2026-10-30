#include "MapTool_Cam.h"

CMapTool_Cam::CMapTool_Cam(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
	:CCamera{ pDevice, pContext }
{
}

HRESULT CMapTool_Cam::Initialize()
{
	if (FAILED(__super::Initialize()))
		return E_FAIL;
	m_fAspect = static_cast<f32_t>(g_iToolWinSizeX) / g_iToolWinSizeY;
	m_vUp = { 0.f,1.f,0.f };
	m_vEye = { 0.f,0.f,0.f };
	m_vAt = { 0.f,0.f,1.f };
	return S_OK;
}

void CMapTool_Cam::Update(f32_t fDeltaTime)
{
	__super::Update(fDeltaTime);

	KeyInput(fDeltaTime);

	Mouse_Move();
}

void CMapTool_Cam::Late_Update(f32_t fDeltaTime)
{
	__super::Late_Update(fDeltaTime);
}

void CMapTool_Cam::KeyInput(const f32_t fDeltaTime)
{
	if (CGameInstance::Get().Get_DIKeyState(DIK_W))
	{
		vector_t vLook = XMLoadFloat3(&m_vAt) - XMLoadFloat3(&m_vEye);
		vector_t vLength = XMVector3Normalize(vLook) * fDeltaTime * m_fMoveSpeed;
		XMStoreFloat3(&m_vAt, XMLoadFloat3(&m_vAt) + vLength);
		XMStoreFloat3(&m_vEye, XMLoadFloat3(&m_vEye) + vLength);
	}
	if (CGameInstance::Get().Get_DIKeyState(DIK_S))
	{
		vector_t vLook = XMLoadFloat3(&m_vAt) - XMLoadFloat3(&m_vEye);
		vector_t vLength = XMVector3Normalize(vLook) * fDeltaTime * m_fMoveSpeed;
		XMStoreFloat3(&m_vAt, XMLoadFloat3(&m_vAt) - vLength);
		XMStoreFloat3(&m_vEye, XMLoadFloat3(&m_vEye) - vLength);
	}
	if (CGameInstance::Get().Get_DIKeyState(DIK_A))
	{
		vector_t vUp = vector_t{ 0.f,1.f,0.f,0.f };
		vector_t vLook = XMLoadFloat3(&m_vAt) - XMLoadFloat3(&m_vEye);
		vector_t vRight = XMVector3Cross(vUp, vLook);
		vector_t vLength = XMVector3Normalize(vRight) * fDeltaTime * m_fMoveSpeed;
		XMStoreFloat3(&m_vAt, XMLoadFloat3(&m_vAt) - vLength);
		XMStoreFloat3(&m_vEye, XMLoadFloat3(&m_vEye) - vLength);
	}
	if (CGameInstance::Get().Get_DIKeyState(DIK_D))
	{
		vector_t vUp = vector_t{ 0.f,1.f,0.f,0.f };
		vector_t vLook = XMLoadFloat3(&m_vAt) - XMLoadFloat3(&m_vEye);
		vector_t vRight = XMVector3Cross(vUp, vLook);
		vector_t vLength = XMVector3Normalize(vRight) * fDeltaTime * m_fMoveSpeed;
		XMStoreFloat3(&m_vAt, XMLoadFloat3(&m_vAt) + vLength);
		XMStoreFloat3(&m_vEye, XMLoadFloat3(&m_vEye) + vLength);
	}
}

void CMapTool_Cam::Mouse_Move()
{
	if (!CGameInstance::Get().Get_DIMouseState(DIM::RB))
		return;

	int32_t	dwMouseMove = {};
	if (dwMouseMove = CGameInstance::Get().Get_DIMouseMove(DIMM::Y))
	{
		vector_t vUp = vector_t{ 0.f,1.f,0.f,0.f };
		vector_t vLook = XMLoadFloat3(&m_vAt) - XMLoadFloat3(&m_vEye);
		vector_t vRight = XMVector3Cross(vUp, vLook);

		matrix_t matRot = XMMatrixRotationAxis(vRight, XMConvertToRadians(dwMouseMove / 10.f));
		vLook = XMVector3TransformNormal(vLook, matRot);
		XMStoreFloat3(&m_vAt, XMLoadFloat3(&m_vEye) + vLook);
	}
	if (dwMouseMove = CGameInstance::Get().Get_DIMouseMove(DIMM::X))
	{
		vector_t vUp = vector_t{ 0.f,1.f,0.f,0.f };
		vector_t vLook = XMLoadFloat3(&m_vAt) - XMLoadFloat3(&m_vEye);
		vector_t vRight = XMVector3Cross(vUp, vLook);
		vUp = XMVector3Cross(vLook, vRight);

		matrix_t matRot = XMMatrixRotationAxis(vUp, XMConvertToRadians(dwMouseMove / 10.f));
		vLook = XMVector3TransformNormal(vLook, matRot);
		XMStoreFloat3(&m_vAt, XMLoadFloat3(&m_vEye) + vLook);
	}
}

shared_ptr<CMapTool_Cam> CMapTool_Cam::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
	auto pInstance = shared_ptr<CMapTool_Cam>(new CMapTool_Cam(pDevice, pContext));
	if (FAILED(pInstance->Initialize()))
		pInstance.reset();

	return pInstance;
}