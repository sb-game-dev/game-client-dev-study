#include "pch.h"
#include "CShield.h"
#include "CCameraMgr.h"

CShield::CShield():m_pPlayer(nullptr)
{
}

CShield::~CShield()
{
	Release();
}

void CShield::Initialize()
{
	m_vLocalBody[0] = { -10.f,	-10.f,	0.f };
	m_vLocalBody[1] = { 10.f,	-10.f,	0.f };
	m_vLocalBody[2] = { 10.f,	10.f,	0.f };
	m_vLocalBody[3] = { -10.f,	10.f,	0.f };
}

void CShield::Update()
{
	m_fAngle += D3DXToRadian(3.f);


	D3DXMATRIX matView;
	matView = CCameraMgr::GetInstance()->GetMatView();
	m_tInfo.matView = matView;

}

void CShield::LateUpdate()
{

	float fParentDistance = 120.f;

	D3DXMATRIX matScale, matRotZ2, matParentDistance, matRotZ, matTrans;
	D3DXVECTOR3	vParentPos = m_pPlayer->GetInfo().vPos;
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixRotationZ(&matRotZ2, -m_fAngle);
	D3DXMatrixTranslation(&matParentDistance, 0.f, fParentDistance, 0.f);
	D3DXMatrixRotationZ(&matRotZ, m_fAngle);
	D3DXMatrixTranslation(&matTrans, vParentPos.x, vParentPos.y, vParentPos.z);

	m_tInfo.matWorld = matScale * matRotZ2 * matParentDistance * matRotZ * matTrans;

	for (int i = 0; i < 4; ++i)
		D3DXVec3TransformCoord(&m_vWorldBody[i], &m_vLocalBody[i], &m_tInfo.matWorld);

	for (int i = 0; i < 4; ++i)
		D3DXVec3TransformCoord(&m_vViewBody[i], &m_vWorldBody[i], &m_tInfo.matView);

	for (int i = 0; i < 4; ++i) {
		m_vViewBody[i] += {WINCX / 2, WINCY / 2, 0};
	}
}

void CShield::Render(HDC hDC)
{
	Ellipse(hDC,
		m_vViewBody[0].x,
		m_vViewBody[0].y,
		m_vViewBody[2].x,
		m_vViewBody[2].y);
}

void CShield::Release()
{
}
