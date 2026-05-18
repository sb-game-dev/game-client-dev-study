#include "pch.h"
#include "CPlayer.h"
#include "CAbstractFactory.h"
CPlayer::CPlayer():dwTime(GetTickCount()), m_iMaxBomb(2), m_iBombPower(3)
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
	m_tStat.fAttack = 100;
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
	//if (GetAsyncKeyState('W'))
	//	m_BulletListP->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX,m_tInfo.fY,1,m_tStat.fAttack, DIR_UP));
	//if (GetAsyncKeyState('A'))
	//	m_BulletListP->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, 1, m_tStat.fAttack, DIR_LEFT));
	//if (GetAsyncKeyState('S'))
	//	m_BulletListP->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, 1, m_tStat.fAttack, DIR_DOWN));
	//if (GetAsyncKeyState('D'))
	//	m_BulletListP->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, 1, m_tStat.fAttack, DIR_RIGHT));
	if (GetAsyncKeyState(VK_SPACE) & 0x001)
	{
		if(m_BulletListP->size() < m_iMaxBomb)
			m_BulletListP->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, 1, m_tStat.fAttack, DIR_UP));
		//m_BulletListP->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, 1, m_tStat.fAttack, DIR_LU));
		//m_BulletListP->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, 1, m_tStat.fAttack, DIR_RU));
	}

}

void CPlayer::CreateBullet()
{
	CObj* pBullet = CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, 1, m_tStat.fAttack, DIR_UP);
	m_BulletListP->push_back(pBullet);

	
}



void CPlayer::LateUpdate()
{
	if (m_tStat.fHp <= 0.f)
		m_bDead = DEAD;
	for (auto &pBullet : *(m_BulletListP))
	{
		if (dynamic_cast<CBullet*> (pBullet)->GetState() == EXPLODE)
		{
			dynamic_cast<CBullet*> (pBullet)->SetState(EXPLODE_END);
			float fX = pBullet->GetInfo().fX;
			float fY = pBullet->GetInfo().fY;
			for (int i = 1; i <= m_iBombPower; i++)
			{
				CObj* ptempBullet = CAbstractFactory<CBullet>::Create(fX + 30 * i, fY, 1, m_tStat.fAttack, DIR_UP);
				dynamic_cast<CBullet*> (ptempBullet)->SetState(EXPLODE_END);
				m_BulletListP->push_back(ptempBullet);
			}
			for (int i = 1; i <= m_iBombPower; i++)
			{
				CObj* ptempBullet = CAbstractFactory<CBullet>::Create(fX - 30 * i, fY, 1, m_tStat.fAttack, DIR_UP);
				dynamic_cast<CBullet*> (ptempBullet)->SetState(EXPLODE_END);
				m_BulletListP->push_back(ptempBullet);
			}
			for (int i = 1; i <= m_iBombPower; i++)
			{
				CObj* ptempBullet = CAbstractFactory<CBullet>::Create(fX, fY + 30 * i, 1, m_tStat.fAttack, DIR_UP);
				dynamic_cast<CBullet*> (ptempBullet)->SetState(EXPLODE_END);
				m_BulletListP->push_back(ptempBullet);
			}
			for (int i = 1; i <= m_iBombPower; i++)
			{
				CObj* ptempBullet = CAbstractFactory<CBullet>::Create(fX, fY - 30 * i, 1, m_tStat.fAttack, DIR_UP);
				dynamic_cast<CBullet*> (ptempBullet)->SetState(EXPLODE_END);
				m_BulletListP->push_back(ptempBullet);
			}
		}
	}
}
