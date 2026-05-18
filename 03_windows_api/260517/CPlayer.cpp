#include "pch.h"
#include "CPlayer.h"
#include "CAbstractFactory.h"
CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_tInfo = { (WINCX >> 1) ,(WINCY >> 1) ,100,100 };
	m_fSpeed = 10.f;
	m_tStat.fHp = 100;
	m_tStat.fAttack = 10;
}

bool CPlayer::Update()
{
	if (m_bDead)
		return DEAD;
	KeyDown();
	__super::UpdateRect();
	return NONEVENT;
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
	if (GetAsyncKeyState(VK_RIGHT))
		m_tInfo.fX += m_fSpeed;
	if (GetAsyncKeyState(VK_UP))
		m_tInfo.fY -= m_fSpeed;
	if (GetAsyncKeyState(VK_DOWN))
		m_tInfo.fY += m_fSpeed;
	if (GetAsyncKeyState('W'))
		m_BulletListP->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX,m_tInfo.fY,1,m_tStat.fAttack, DIR_UP));
	if (GetAsyncKeyState('A'))
		m_BulletListP->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, 1, m_tStat.fAttack, DIR_LEFT));
	if (GetAsyncKeyState('S'))
		m_BulletListP->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, 1, m_tStat.fAttack, DIR_DOWN));
	if (GetAsyncKeyState('D'))
		m_BulletListP->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, 1, m_tStat.fAttack, DIR_RIGHT));
	if (GetAsyncKeyState(VK_SPACE))
	{
		m_BulletListP->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, 1, m_tStat.fAttack, DIR_UP));
		m_BulletListP->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, 1, m_tStat.fAttack, DIR_LU));
		m_BulletListP->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, 1, m_tStat.fAttack, DIR_RU));
	}

}


void CPlayer::LateUpdate()
{
	if (m_tStat.fHp <= 0.f)
		m_bDead = DEAD;
}
