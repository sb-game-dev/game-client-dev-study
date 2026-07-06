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
	m_tInfo.vPos = { 100.f, 600.f, 0.f };
	m_tInfo.vLook = { 1.f, 1.f, 0.f };
	x = 100.f;
	y = 100.f;

	m_fSpeed = 2.f;

	m_fRadian = 0.f;
}

void CMonster::Update()
{
	m_tInfo.vDir = m_pPlayer->GetInfo().vPos - m_tInfo.vPos;
	
	//// 벡터의 정규화 과정
	float	fLength = sqrtf(m_tInfo.vDir.x * m_tInfo.vDir.x + m_tInfo.vDir.y * m_tInfo.vDir.y);
	
	m_tInfo.vDir.x /= fLength;
	m_tInfo.vDir.y /= fLength;
	m_tInfo.vDir.z = 0.f;

	//m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;

	//if (m_tInfo.vDir.x * m_pPlayer->GetInfo().vDir.x < 0)
	//		m_tInfo.vDir.x *= -1;
	//if (m_tInfo.vDir.y * m_pPlayer->GetInfo().vDir.y < 0)
	//		m_tInfo.vDir.y *= -1;
	

	float fRadian = acosf(GetCos(m_tInfo.vDir, m_pPlayer->GetInfo().vDir));
	float fAngle = fRadian * 180.f / PI;
	if (m_tInfo.vPos.y < m_pPlayer->GetInfo().vPos.y)
		fAngle *= -1;
	
	m_tInfo.vPos.x += cosf(fAngle * PI / 180.f) * m_fSpeed;
	m_tInfo.vPos.y -= sinf(fAngle * PI / 180.f) * m_fSpeed;
}

void CMonster::Render(HDC hDC)
{
	Ellipse(hDC,
		m_tInfo.vPos.x - 50.f,
		m_tInfo.vPos.y - 50.f,
		m_tInfo.vPos.x + 50.f,
		m_tInfo.vPos.y + 50.f);

	//MoveToEx(hDC, (int)m_tInfo.vPos.x, (int)m_tInfo.vPos.y, nullptr);
	//LineTo(hDC, (int)m_tInfo.vPos.x + (int)(m_tInfo.vDir.x * 80), (int)m_tInfo.vPos.y + (int)(m_tInfo.vDir.y * 80));
}

void CMonster::Release()
{
}
