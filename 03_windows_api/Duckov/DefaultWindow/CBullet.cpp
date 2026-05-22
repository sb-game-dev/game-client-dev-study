#include "pch.h"
#include "CBullet.h"

CBullet::CBullet()
{
}

CBullet::~CBullet()
{
	Release();
}

void CBullet::Initialize()
{
	m_tInfo.fCX = 10.f;
	m_tInfo.fCY = 10.f;

	m_fSpeed = 40.f;
}

int CBullet::Update()
{
	if (m_bDead == DEAD)
		return DEAD;
	
	m_tInfo.fX += m_fSpeed * cosf(m_fAngle);
	m_tInfo.fY -= m_fSpeed * sinf(m_fAngle);

	return NONEVENT;
}

void CBullet::LateUpdate()
{
	if (m_tInfo.fX <= 0 || m_tInfo.fX >= WINCX || m_tInfo.fY <= 0 || m_tInfo.fY >= WINCY)
		m_bDead = DEAD;
	if(m_tAbility.fHp<=0)
		m_bDead = DEAD;
}

void CBullet::Render(HDC hDC)
{
	Ellipse(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);
}

void CBullet::Release()
{
}
