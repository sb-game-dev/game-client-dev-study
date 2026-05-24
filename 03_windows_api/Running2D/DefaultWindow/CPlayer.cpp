#include "pch.h"
#include "CPlayer.h"

CPlayer::CPlayer()
{
	ZeroMemory(&m_Point1, sizeof(POINT));
	ZeroMemory(&m_Point2, sizeof(POINT));
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_tInfo = { float(WINCX >> 1), float(WINCY >> 1), 100.f, 100.f };
	m_fSpeed = 10.f;

	m_Point1 = { long(250),long(400) };
	m_Point2 = { long(550),long(200) };
}

int CPlayer::Update()
{
	if (m_bDead == DEAD)
		return DEAD;
	KeyInput();

	__super::Update_Rect();		// 상속 관계에서 최상위 클래스를 지칭하는 지시자
	return NONEVENT;
}

void CPlayer::LateUpdate()
{
}
void CPlayer::Render(HDC hDC)
{
	Rectangle(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);
}

void CPlayer::Release()
{
}

void CPlayer::KeyInput()
{
	if (GetAsyncKeyState(VK_RIGHT))
		m_tInfo.fX += m_fSpeed;

	if (GetAsyncKeyState(VK_LEFT))
		m_tInfo.fX -= m_fSpeed;

	if (m_tInfo.fX <= 250)
	{
		m_tInfo.fY = m_Point1.y;
	}
	else if(m_tInfo.fX <=550)
	{
		m_tInfo.fY = float(m_Point1.y - m_Point2.y) / float(m_Point1.x - m_Point2.x) * (m_tInfo.fX - m_Point1.x) + m_Point1.y;
	}
	else
	{
		m_tInfo.fY = m_Point2.y;
	}

	//if (GetAsyncKeyState(VK_UP))
	//	m_tInfo.fY -= m_fSpeed;
	//
	//if (GetAsyncKeyState(VK_DOWN))
	//	m_tInfo.fY += m_fSpeed;

}

