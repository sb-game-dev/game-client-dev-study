#include "pch.h"
#include "CPlayer.h"
#include "CAbstractFactory.h"
#include "CBomb.h"
CPlayer::CPlayer():m_iBombPower(2), m_iMaxBomb(2),m_BombListp(nullptr)
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_tInfo = { (WINCX >> 1),(WINCY >> 1),100.f,100.f };
	m_tStat = { 100.f,10.f };
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
	for (auto& Bomb : *m_BombListp)
	{
		if (dynamic_cast<CBomb*> (Bomb)->GetState() == ST_EXPLODE_READY)
		{
			dynamic_cast<CBomb*> (Bomb)->SetState(ST_EXPLODE_ING);
			float fX = Bomb->GetInfo().fX;
			float fY = Bomb->GetInfo().fY;
			for (int i = 1; i <= m_iBombPower; ++i)
			{
				CObj* pBomb = CAbstractFactory<CBomb>::Create(fX + Bomb->GetInfo().fCX * i, fY, 1, 1000);
				dynamic_cast<CBomb*> (pBomb)->SetState(ST_EXPLODE_ING);
				m_BombListp->push_back(pBomb);
			}
			for (int i = 1; i <= m_iBombPower; ++i)
			{
				CObj* pBomb = CAbstractFactory<CBomb>::Create(fX - Bomb->GetInfo().fCX * i, fY, 1, 1000);
				dynamic_cast<CBomb*> (pBomb)->SetState(ST_EXPLODE_ING);
				m_BombListp->push_back(pBomb);
			}
			for (int i = 1; i <= m_iBombPower; ++i)
			{
				CObj* pBomb = CAbstractFactory<CBomb>::Create(fX, fY + Bomb->GetInfo().fCX * i, 1, 1000);
				dynamic_cast<CBomb*> (pBomb)->SetState(ST_EXPLODE_ING);
				m_BombListp->push_back(pBomb);
			}
			for (int i = 1; i <= m_iBombPower; ++i)
			{
				CObj* pBomb = CAbstractFactory<CBomb>::Create(fX, fY - Bomb->GetInfo().fCX * i, 1, 1000);
				dynamic_cast<CBomb*> (pBomb)->SetState(ST_EXPLODE_ING);
				m_BombListp->push_back(pBomb);
			}
		}
	}
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
	if (GetAsyncKeyState(VK_SPACE) & 0x001)
		if(m_BombListp->size()< m_iMaxBomb)
			m_BombListp->push_back(CAbstractFactory<CBomb>::Create(m_tInfo.fX, m_tInfo.fY, 1, 1000));
}
