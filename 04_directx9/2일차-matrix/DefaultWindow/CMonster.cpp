#include "pch.h"
#include "CMonster.h"

CMonster::CMonster()
{
}

CMonster::~CMonster()
{
	Release();
}

void CMonster::Initialize()
{
	m_tInfo.vPos = { 100.f, 100.f, 0.f };
	m_tInfo.vLook = { 1.f, 0.f, 0.f };
}

void CMonster::Update()
{
	m_tInfo.vDir = m_pPlayer->GetInfo().vPos - m_tInfo.vPos;

	// 벡터의 정규화 과정
	float	fLength = sqrtf(m_tInfo.vDir.x * m_tInfo.vDir.x + m_tInfo.vDir.y * m_tInfo.vDir.y);

	m_tInfo.vDir.x /= fLength;
	m_tInfo.vDir.y /= fLength;
	m_tInfo.vDir.z = 0.f;

	m_tInfo.vPos += m_tInfo.vDir * 2.f;

	// m_tInfo.vPos.x += cos() * m_fSpeed;
	// m_tInfo.vPos.y -= sin() * m_fSpeed;
}

void CMonster::Render(HDC hDC)
{
	Ellipse(hDC,
		m_tInfo.vPos.x - 50.f,
		m_tInfo.vPos.y - 50.f,
		m_tInfo.vPos.x + 50.f,
		m_tInfo.vPos.y + 50.f);
}

void CMonster::Release()
{
}
