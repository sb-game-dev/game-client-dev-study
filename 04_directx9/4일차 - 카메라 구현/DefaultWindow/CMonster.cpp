#include "pch.h"
#include "CMonster.h"
#include "CCameraMgr.h"

CMonster::CMonster()
{
}

CMonster::~CMonster()
{
}

void CMonster::Initialize()
{
	m_vLocalBody[0] = { -50.f,	-50.f,	0.f };
	m_vLocalBody[1] = { 50.f,	-50.f,	0.f };
	m_vLocalBody[2] = { 50.f,	50.f,	0.f };
	m_vLocalBody[3] = { -50.f,	50.f,	0.f };

	m_tInfo.vPos = { 100.f, 100.f, 0.f };
}

void CMonster::Update()
{
	m_tInfo.matView = CCameraMgr::GetInstance()->GetMatView();
	m_tInfo.matProj = CCameraMgr::GetInstance()->GetMatProj();
}
void CMonster::LateUpdate()
{
	D3DXMATRIX matScale, matRotZ, matTrans;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixRotationZ(&matRotZ, m_fAngle);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	m_tInfo.matWorld = matScale * matRotZ * matTrans;

	for (int i = 0; i < 4; ++i)
		D3DXVec3TransformCoord(&m_vWorldBody[i], &m_vLocalBody[i], &m_tInfo.matWorld);
	for (int i = 0; i < 4; ++i)
		D3DXVec3TransformCoord(&m_vViewBody[i], &m_vWorldBody[i], &m_tInfo.matView);
	for (int i = 0; i < 4; ++i)
		D3DXVec3TransformCoord(&m_vViewBody[i], &m_vViewBody[i], &m_tInfo.matProj);

	// ºäÆ÷Æ® º¯È¯
	for (int i = 0; i < 4; ++i) {
		m_vViewBody[i] += {WINCX / 2, WINCY / 2, 0};
		//m_vViewBody[i].x = (m_vViewBody[i].x + 1) * WINCX;
		//m_vViewBody[i].y = (-m_vViewBody[i].y + 1) * WINCY;
	}
}

void CMonster::Render(HDC hDC)
{
	Ellipse(hDC,
		m_vViewBody[0].x,
		m_vViewBody[0].y,
		m_vViewBody[2].x,
		m_vViewBody[2].y);
}

void CMonster::Release()
{
}
