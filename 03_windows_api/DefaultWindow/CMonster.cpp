#include "pch.h"
#include "CMonster.h"

CMonster::CMonster()
{
}

CMonster::~CMonster()
{
}

void CMonster::Initialize()
{
	m_tInfo = { (WINCX >> 1),100,100.f,100.f};
	m_fSpeed = 5.f;
}

void CMonster::Update()
{
	if (m_tInfo.fX > WINCX - 100)
		m_fSpeed = -5.f;
	if (m_tInfo.fX < 100)
		m_fSpeed = 5.f;

	m_tInfo.fX += m_fSpeed;

	__super::UpdateRect();
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
