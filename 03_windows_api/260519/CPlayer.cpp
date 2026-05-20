#include "pch.h"
#include "CPlayer.h"
#include "CAbstractFactory.h"
#include "CBullet.h"
#include "CBarrel.h"
CPlayer::CPlayer():m_BulletListp(nullptr), m_pBarrel(nullptr)
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_tInfo = { (WINCX >> 1),(WINCY >> 1),100,100 };

	m_tStat.fAttack = 10;
	m_tStat.fHp = 10;

	m_fSpeed = 1.f;
}

int CPlayer::Update()
{
	if (m_bDead == DEAD)
		return DEAD;
	KeyDown();
	__super::UpdateRect();
	return NONEVENT;
}

void CPlayer::LateUpdate()
{
	if (m_tStat.fHp <= 0)
		m_bDead = DEAD;
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

void CPlayer::KeyDown()
{
	//if (GetAsyncKeyState(VK_LEFT))
	//{
	//	if (GetAsyncKeyState(VK_UP))
	//	{
	//		m_tInfo.fX -= m_fSpeed;
	//		m_tInfo.fY -= m_fSpeed;
	//	}
	//	else if (GetAsyncKeyState(VK_DOWN))
	//	{
	//		m_tInfo.fX -= m_fSpeed;
	//		m_tInfo.fY += m_fSpeed;
	//	}
	//	else
	//		m_tInfo.fX -= m_fSpeed;
	//}
	//else if (GetAsyncKeyState(VK_RIGHT))
	//{
	//	if (GetAsyncKeyState(VK_UP))
	//	{
	//		m_tInfo.fX += m_fSpeed;
	//		m_tInfo.fY -= m_fSpeed;
	//	}
	//	else if (GetAsyncKeyState(VK_DOWN))
	//	{
	//		m_tInfo.fX += m_fSpeed;
	//		m_tInfo.fY += m_fSpeed;
	//	}
	//	else
	//		m_tInfo.fX += m_fSpeed;
	//}
	//else if (GetAsyncKeyState(VK_UP))
	//{
	//	m_tInfo.fY -= m_fSpeed;
	//}
	//else if (GetAsyncKeyState(VK_DOWN))
	//{
	//	m_tInfo.fY += m_fSpeed;
	//}

	
	m_tInfo.fX += m_fSpeed * cos(dynamic_cast<CBarrel*>(m_pBarrel)->GetRadian());
	m_tInfo.fY -= m_fSpeed * sin(dynamic_cast<CBarrel*>(m_pBarrel)->GetRadian());
	if (GetAsyncKeyState(VK_SPACE))
	{
		m_BulletListp->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, dynamic_cast<CBarrel*>(m_pBarrel)->GetRadian()));
	}
}
