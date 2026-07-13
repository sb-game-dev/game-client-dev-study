#include "pch.h"
#include "CCameraMgr.h"
CCameraMgr* CCameraMgr::m_pInstance = nullptr;
CCameraMgr::CCameraMgr():m_pTarget(nullptr)
{
	ZeroMemory(&m_vPos, sizeof(m_vPos));
	ZeroMemory(&m_matView, sizeof(m_matView));
	D3DXMatrixIdentity(&m_matView);
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
	D3DXVECTOR3 vTargetPos = m_pTarget->GetInfo().vPos;
	//D3DXVECTOR3 vTargetPos = { 0, 0, 0 };
	m_vPos = { vTargetPos.x,vTargetPos.y,-1.f };
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