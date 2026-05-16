#include "pch.h"
#include "CBullet.h"

CBullet::CBullet(const char& key) :m_fXSpeed(0), m_fYSpeed(0)
{
	if (key == 'W') m_fYSpeed = 20.f;
	else if (key == 'A') m_fXSpeed = 20.f;
	else if (key == 'S') m_fYSpeed = -20.f;
	else if (key == 'D') m_fXSpeed = -20.f;
	else if (key == 'Q')
	{
		m_fYSpeed = 20.f;
		m_fXSpeed = 20.f;
	}
	else if (key == 'E')
	{
		m_fYSpeed = 20.f;
		m_fXSpeed = -20.f;
	}
}

CBullet::~CBullet()
{
	Release();
}

void CBullet::Initialize()
{
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;
}

void CBullet::Update()
{
	m_tInfo.fX -= m_fXSpeed;
	m_tInfo.fY -= m_fYSpeed;
	__super::UpdateRect();
}

void CBullet::Render(HDC hDC)
{
	Ellipse(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom
	);
}

void CBullet::Release()
{
}

bool CBullet::CheckColiision()
{
	if (m_tInfo.fX < 50 || m_tInfo.fY < 50 || m_tInfo.fX > WINCX - 50 || m_tInfo.fY > WINCY - 50)
		return true;
	return false;
}
