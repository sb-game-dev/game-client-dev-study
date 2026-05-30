#include "pch.h"
#include "CPlayer.h"
#include "CAbstractFactory.h"
#include "CBomb.h"
#include "CObjMgr.h"
#include "CCollisionMgr.h"
#include "CKeyMgr.h"
#include "CBmpMgr.h"
CPlayer::CPlayer() :m_iBombRange(2), m_iBombMax(2), m_iFrame(0),m_dwTime(GetTickCount()), m_tMoveState(MOVE_DOWN)
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	CBmpMgr::GetInstance()->InsertBmp(L"../Image/크레이지 아케이드 리소스/Resource/Player/playermove.bmp", L"Player");
	m_tInfo = { (WINCX >> 1),(WINCY >> 1),70.f,70.f };
	m_fSpeed = 3.f;
}

int CPlayer::Update()
{
	if (m_bDead == DEAD)
		return DEAD;
	
	if (KeyDown())
	{
		switch (m_tMoveState)
		{
		case CPlayer::MOVE_UP:
			m_tRectInfo = { 0, 4, 100,0,0 };
			break;
		case CPlayer::MOVE_DOWN:
			m_tRectInfo = { 0, 4, 100,0,70 };
			break;
		case CPlayer::MOVE_RIGHT:
			m_tRectInfo = { 0, 3, 100,0,140 };
			break;
		case CPlayer::MOVE_LEFT:
			m_tRectInfo = { 0, 3, 100,0,210 };
			break;
		case CPlayer::MOVE_END:
			break;
		default:
			break;
		}
		if (m_dwTime + 100 <= GetTickCount())
		{
			m_dwTime = GetTickCount();

			m_iFrame = (m_iFrame + 1) % m_tRectInfo.iFrameEnd;
		}
	}
	return NONEVENT;
}

void CPlayer::LateUpdate()
{
	
}

void CPlayer::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::GetInstance()->FindImage(L"Player");
	GdiTransparentBlt(hDC,
		m_tRect.left,
		m_tRect.top,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hMemDC,
		m_iFrame + m_tRectInfo.iRectStartX,
		m_tRectInfo.iRectStartY,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(0, 255, 0));
}

void CPlayer::Release()
{
}

bool CPlayer::KeyDown()
{
	bool bReturn = false;
	if (CKeyMgr::GetInstance()->KeyPressing(VK_LEFT))
	{
		bReturn = true;
		m_tMoveState = MOVE_LEFT;
		m_tInfo.fX -= m_fSpeed;
	}
	else if (CKeyMgr::GetInstance()->KeyPressing(VK_UP))
	{
		bReturn = true;
		m_tMoveState = MOVE_UP;
		m_tInfo.fY -= m_fSpeed;
	}
	else if (CKeyMgr::GetInstance()->KeyPressing(VK_RIGHT))
	{
		bReturn = true;
		m_tMoveState = MOVE_RIGHT;
		m_tInfo.fX += m_fSpeed;
	}
	else if (CKeyMgr::GetInstance()->KeyPressing(VK_DOWN))
	{
		bReturn = true;
		m_tMoveState = MOVE_DOWN;
		m_tInfo.fY += m_fSpeed;
	}

	if (CKeyMgr::GetInstance()->KeyDown(VK_SPACE))
	{
		if (CObjMgr::GetInstance()->GetList(OBJ_BOMB).size() < m_iBombMax)
		{
			bReturn = true;
			CObjMgr::GetInstance()->AddObject(OBJ_BOMB, CreateBomb());
		}
	}
	return bReturn;
}

CObj* CPlayer::CreateBomb()
{
	CObj* pBomb = CAbstractFactory<CBomb>::Create(m_tInfo.fX, m_tInfo.fY);

	pBomb->AdjustPos(m_tInfo.fX, m_tInfo.fY);
	dynamic_cast<CBomb*>(pBomb)->SetBombRange(m_iBombRange);
	return pBomb;
}


