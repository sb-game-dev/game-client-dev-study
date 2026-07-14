#include "pch.h"
#include "CCameraMgr.h"
CCameraMgr* CCameraMgr::m_pInstance = nullptr;
CCameraMgr::CCameraMgr():m_pTarget(nullptr)
{
	ZeroMemory(&m_vPos, sizeof(m_vPos));
	ZeroMemory(&m_matView, sizeof(m_matView));
	D3DXMatrixIdentity(&m_matView);
	D3DXMatrixIdentity(&m_matProj);
	m_vPos = { 0.f,0.f,-1.f };
	m_vUp = { 0.f,1.f,0.f };
}

CCameraMgr::~CCameraMgr()
{

}

void CCameraMgr::Initialize() 
{

}

void CCameraMgr::Update()
{
	KeyInput();
	D3DXVECTOR3 vTargetPos = m_pTarget->GetInfo().vPos;
	m_vPos.x = vTargetPos.x;
	m_vPos.y = vTargetPos.y;


	//D3DXMatrixLookAtLH(
	//	&m_matView,
	//	&m_vPos, {0, 0, -1}
	//	&vTargetPos, {0, 0, 0}
	//	&m_vUp {0, 1, 0}
	//);
	D3DXMatrixLookAtLH(
		&m_matView,
		&m_vPos,
		&vTargetPos,
		&m_vUp
	);
	D3DXMatrixPerspectiveFovLH(
		&m_matProj,
		PI * 0.5,
		WINCX / WINCY,
		1.0f,
		1000.f);
}
void CCameraMgr::LateUpdate()
{
}

void CCameraMgr::Render(HDC hDC)
{

}

void CCameraMgr::Release()
{

}

void	CCameraMgr::KeyInput()
{
	if (GetAsyncKeyState(VK_UP))
	{
		m_vPos.z += 0.02f;
		if (m_vPos.z >= -1)
			m_vPos.z = -1.f;
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		m_vPos.z -= 0.02f;
		if (m_vPos.z <= -2)
			m_vPos.z = -2.f;
	}
}