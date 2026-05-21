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
	m_tInfo.fCX = 40.f;
	m_tInfo.fCY = 40.f;

	m_fSpeed = 8.f;
}

int CMonster::Update()
{
	if (m_bDead == DEAD)
		return DEAD;
	//m_tInfo.fX += m_fSpeed;
	return NONEVENT;
}

void CMonster::LateUpdate()
{
	//if (m_tInfo.fX <= 0 || m_tInfo.fX >= WINCX)
	//	m_fSpeed *= -1;
	if (m_tStat.fHp <= 0)
		m_bDead = DEAD;
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
