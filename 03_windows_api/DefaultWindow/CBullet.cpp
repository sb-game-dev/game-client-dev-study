#include "pch.h"
#include "CBullet.h"

CBullet::CBullet():m_fXSpeed(0)
{
}

CBullet::CBullet(const char& key):m_fXSpeed(0)
{
	if (key == 'A')
		m_fXSpeed = 20.f;
	if (key == 'D')
		m_fXSpeed = -20.f;
}

CBullet::~CBullet()
{
}

void CBullet::Initialize()
{
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;
	m_fSpeed = 20.f;
}

void CBullet::Update()
{
	m_tInfo.fY -= m_fSpeed;
	m_tInfo.fX -= m_fXSpeed;
	__super::UpdateRect();
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

bool CBullet::CheckCollison()
{
	if (m_tInfo.fX<50 || m_tInfo.fX>WINCX - 50 || m_tInfo.fY<50 || m_tInfo.fY>WINCY - 50)
		return true;
	return false;
}
