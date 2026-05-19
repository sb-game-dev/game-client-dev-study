#include "pch.h"
#include "CPlayer.h"
#include "CAbstractFactory.h"
#include "CBullet.h"
CPlayer::CPlayer():m_BulletListp(nullptr)
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

	m_fSpeed = 10.f;
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
	if (GetAsyncKeyState(VK_LEFT))
		m_tInfo.fX -= m_fSpeed;
	if (GetAsyncKeyState(VK_UP))
		m_tInfo.fY -= m_fSpeed;
	if (GetAsyncKeyState(VK_RIGHT))
		m_tInfo.fX += m_fSpeed;
	if (GetAsyncKeyState(VK_DOWN))
		m_tInfo.fY += m_fSpeed;

	if (GetAsyncKeyState('W'))
		m_BulletListp->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_TOP));
	if (GetAsyncKeyState('A'))
		m_BulletListp->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_LEFT));
	if (GetAsyncKeyState('S'))
		m_BulletListp->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_BOTTOM));
	if (GetAsyncKeyState('D'))
		m_BulletListp->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_RIGHT));
	if (GetAsyncKeyState(VK_SPACE))
	{
		m_BulletListp->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_TOP));
		m_BulletListp->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_LU));
		m_BulletListp->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_RU));
	}
}
