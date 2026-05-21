#include "pch.h"
#include "CPlayer.h"
#include "CAbstractFactory.h"
#include "CBullet.h"
#include "CObjMgr.h"
#include "CFollowMgr.h"
#include "CCollisionMgr.h"
CPlayer::CPlayer()
{
	ZeroMemory(&m_tPosin, sizeof(POINT));
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

	m_fDistance = 100.f;

	m_fSpeed = 10.f;
}

int CPlayer::Update()
{
	if (m_bDead == DEAD)
		return DEAD;
	KeyDown();
	return NONEVENT;
}

void CPlayer::LateUpdate()
{
	if (m_tStat.fHp <= 0)
		m_bDead = DEAD;
	/////////////////////////////////////
	CObj* pMouse = CObjMgr::GetInstance()->GetList(OBJ_MOUSE).front();

	float fDstX = pMouse->GetInfo().fX;
	float fDstY = pMouse->GetInfo().fY;

	float fDeltaX = abs(fDstX - m_tInfo.fX);
	float fDeltaY = abs(fDstY - m_tInfo.fY);

	float fDistance = sqrtf(fDeltaX * fDeltaX + fDeltaY * fDeltaY);
	m_fRadian = acosf(fDeltaX / fDistance);
	if (m_tInfo.fY < fDstY)
	{
		// 1사분면
		if (fDstX < m_tInfo.fX)
		{
			m_tPosin.x = LONG(m_tInfo.fX - m_fDistance * cosf(m_fRadian));
			m_tPosin.y = LONG(m_tInfo.fY + m_fDistance * sinf(m_fRadian));
		}
		// 2사분면
		else
		{
			m_tPosin.x = LONG(m_tInfo.fX + m_fDistance * cosf(m_fRadian));
			m_tPosin.y = LONG(m_tInfo.fY + m_fDistance * sinf(m_fRadian));
		}
	}
	else
	{
		// 3사분면
		if (fDstX > m_tInfo.fX)
		{
			m_tPosin.x = LONG(m_tInfo.fX + m_fDistance * cosf(m_fRadian));
			m_tPosin.y = LONG(m_tInfo.fY - m_fDistance * sinf(m_fRadian));
		}
		// 4사분면
		else
		{
			m_tPosin.x = LONG(m_tInfo.fX - m_fDistance * cosf(m_fRadian));
			m_tPosin.y = LONG(m_tInfo.fY - m_fDistance * sinf(m_fRadian));
		}
	}
	if(!CCollisionMgr::CheckCircle(this, pMouse))
		CFollowMgr::Follow(pMouse->GetInfo(), m_tInfo, m_fSpeed);
	////////////////////////////////////
	//m_tPosin.x = LONG(m_tInfo.fX + m_fDistance * cosf(m_fRadian * (PI / 180.f)));
	//m_tPosin.y = LONG(m_tInfo.fY - m_fDistance * sinf(m_fRadian * (PI / 180.f)));
}

void CPlayer::Render(HDC hDC)
{
	Rectangle(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);

	MoveToEx(hDC, (int)m_tInfo.fX, (int)m_tInfo.fY, nullptr);
	LineTo(hDC, m_tPosin.x, m_tPosin.y);
}

void CPlayer::Release()
{
}

void CPlayer::KeyDown()
{
	//if (GetAsyncKeyState(VK_LEFT))
	//{
	//	m_fRadian += 3.f;
	//}
	//if (GetAsyncKeyState(VK_RIGHT))
	//{
	//	m_fRadian -= 3.f;
	//}
	//if (GetAsyncKeyState(VK_UP))
	//{
	//	m_tInfo.fX += m_fSpeed * cos(m_fRadian);
	//	m_tInfo.fY -= m_fSpeed * sin(m_fRadian);
	//}
	//if (GetAsyncKeyState(VK_DOWN))
	//{
	//	m_tInfo.fX += -m_fSpeed * cos(m_fRadian);
	//	m_tInfo.fY -= -m_fSpeed * sin(m_fRadian);
	//}

	if (GetAsyncKeyState(VK_SPACE) & 0x0001)
	{
		CObjMgr::GetInstance()->AddObject(OBJ_BULLET, CreateBullet());
	}
}

CObj* CPlayer::CreateBullet()
{
	CObj* pBullet = CAbstractFactory<CBullet>::Create();

	pBullet->SetPos((float)m_tPosin.x, (float)m_tPosin.y);
	pBullet->SetDir(m_fRadian);
	return pBullet;
}
