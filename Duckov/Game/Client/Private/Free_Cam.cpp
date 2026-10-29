#include "Free_Cam.h"

CFree_Cam::CFree_Cam(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
	:CCamera{ pDevice, pContext }
{
}

HRESULT CFree_Cam::Initialize()
{
	if (FAILED(__super::Initialize()))
		return E_FAIL;

	m_vUp = { 0.f,1.f,0.f };
	m_vEye = { 0.f,0.f,0.f };
	m_vAt = { 0.f,0.f,1.f };
	return S_OK;
}

void CFree_Cam::Update(f32_t fDeltaTime)
{
	__super::Update(fDeltaTime);
	
	KeyInput(fDeltaTime);
	if (m_bFix)
	{
		Mouse_Move();
		Mouse_Fix();
	}
}

void CFree_Cam::Late_Update(f32_t fDeltaTime)
{
	__super::Late_Update(fDeltaTime);
}

void CFree_Cam::KeyInput(const f32_t fDeltaTime)
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
	if (CGameInstance::Get().Key_Down(DIK_TAB))
	{
		m_bFix = !m_bFix;
	}
}

void CFree_Cam::Mouse_Move()
{
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

void CFree_Cam::Mouse_Fix()
{
	POINT		ptMouse{ g_iWinSizeX >> 1, g_iWinSizeY >> 1 };

	ClientToScreen(g_hWnd, &ptMouse);
	SetCursorPos(ptMouse.x, ptMouse.y);
}

shared_ptr<CFree_Cam> CFree_Cam::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
	auto pInstance = shared_ptr<CFree_Cam>(new CFree_Cam(pDevice, pContext));
	if (FAILED(pInstance->Initialize()))
		pInstance.reset();

	return pInstance;
}