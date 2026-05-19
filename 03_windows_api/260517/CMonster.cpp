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
	m_tInfo = { WINCX >> 1,100,80,80 };
	m_fSpeed = 8.f;
}

bool CMonster::Update()
{
	if (m_bDead)
		return DEAD;
	m_tInfo.fX += m_fSpeed;
	__super::UpdateRect();
	return NONEVENT;
}

void CMonster::Render(HDC hDC)
{
	Rectangle(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);
}

void CMonster::Release()
{
}

void CMonster::LateUpdate()
{
	if (m_tInfo.fX <= 0 || m_tInfo.fX >= WINCX)
		m_fSpeed *= -1;
	if (m_tStat.fHp <= 0.f)
		m_bDead = DEAD;	
}
