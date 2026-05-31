#include "pch.h"
#include "CPlayer.h"
#include "CAbstractFactory.h"
#include "CBomb.h"
#include "CObjMgr.h"
#include "CCollisionMgr.h"
#include "CKeyMgr.h"
#include "CBmpMgr.h"
#include "CBlock.h"
CPlayer::CPlayer() :m_iBombRange(2), m_iBombMax(2), m_tMoveState(MOVE_DOWN), m_bBubble(false), m_fBlockMoveTime(0.f), m_ePrevKey(DIR_END),m_eCurKey(DIR_END)
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	CBmpMgr::GetInstance()->InsertBmp(L"../Image/크레이지 아케이드 리소스/Resource/Player/playermove.bmp", L"Player");
	CBmpMgr::GetInstance()->InsertBmp(L"../Image/크레이지 아케이드 리소스/Resource/Player/playerbubble.bmp", L"PlayerBubble");
	m_tInfo = { (WINCX >> 1),(WINCY >> 1),40.f,40.f };
	m_fSpeed = 3.f;
}

int CPlayer::Update()
{
	if (m_bDead == DEAD)
		return DEAD;
	m_ePrevKey = m_eCurKey;
	if (m_bBubble == true)
	{
		m_tRenderInfo = { 0, 4, 1000,0,0 };
		m_fSpeed = 0.5f;
	}
	else
	{
		m_fSpeed = 3.f;
	}

	if (KeyDown() && m_bBubble == false)
	{
		switch (m_tMoveState)
		{
		case CPlayer::MOVE_UP:
			m_tRenderInfo = { 0, 4, 100,0,0 };
			break;
		case CPlayer::MOVE_DOWN:
			m_tRenderInfo = { 0, 4, 100,0,70 };
			break;
		case CPlayer::MOVE_RIGHT:
			m_tRenderInfo = { 0, 3, 100,0,140 };
			break;
		case CPlayer::MOVE_LEFT:
			m_tRenderInfo = { 0, 3, 100,0,210 };
			break;
		case CPlayer::MOVE_END:
			break;
		default:
			break;
		}
		if (!m_bBubble && m_dwAniTime + m_tRenderInfo.dwFrameSpeed <= GetTickCount())
		{
			m_dwAniTime = GetTickCount();

			m_iFrame = (m_iFrame + 1) % m_tRenderInfo.iFrameEnd;
		}
	}
	else if(m_bBubble == true)
	{
		if (m_dwAniTime + m_tRenderInfo.dwFrameSpeed <= GetTickCount())
		{
			m_dwAniTime = GetTickCount();

			m_iFrame++;
			if (m_iFrame == m_tRenderInfo.iFrameEnd)
				m_bDead = DEAD;
		}
	}
	else
	{
		m_fBlockMoveTime = 0;
		m_iFrame = 0;
	}
	return NONEVENT;
}

void CPlayer::LateUpdate()
{
	
}
void CPlayer::Update_Rect()
{
	m_tRect.left	= LONG(m_tInfo.fX - (m_tInfo.fCX / 2.f));
	m_tRect.top		= LONG(m_tInfo.fY - 5.f);					//(m_tInfo.fCY / 2.f)
	m_tRect.right	= LONG(m_tInfo.fX + (m_tInfo.fCX / 2.f));
	m_tRect.bottom	= LONG(m_tInfo.fY + 35.f);					//(m_tInfo.fCY / 2.f)

}
void CPlayer::Render(HDC hDC)
{
	HDC hMemDC = nullptr;
	if (m_bBubble == true)
	{
		hMemDC = CBmpMgr::GetInstance()->FindImage(L"PlayerBubble");
	}
	else
	{
		hMemDC = CBmpMgr::GetInstance()->FindImage(L"Player");
	}
	Rectangle(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);
	GdiTransparentBlt(hDC,
		m_tRect.left - 15.f,
		m_tRect.top - 30.f,
		70,//(int)m_tInfo.fCX
		70,//(int)m_tInfo.fCY
		hMemDC,
		m_tRenderInfo.iRectStartX + 70 * m_iFrame ,
		m_tRenderInfo.iRectStartY,
		70,//(int)m_tInfo.fCX
		70,//(int)m_tInfo.fCY
		RGB(0, 255, 0));
	//TCHAR	szBuff[32] = L"";
	//swprintf_s(szBuff, L"PlayerX : %.0f", m_tInfo.fX);
	//TextOut(hDC, 50, 50, szBuff, lstrlen(szBuff));
	//
	//TCHAR	szBuff2[32] = L"";
	//swprintf_s(szBuff2, L"PlayerY : %.0f", m_tInfo.fY);
	//TextOut(hDC, 50, 75, szBuff2, lstrlen(szBuff2));

	//TCHAR	szBuff2[32] = L"";
	//swprintf_s(szBuff2, L"m_fBlockMoveTime : %.0f", m_fBlockMoveTime);
	//TextOut(hDC, 50, 75, szBuff2, lstrlen(szBuff2));
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
		m_eCurKey = DIR_LEFT;
		if (m_ePrevKey != m_eCurKey) m_fBlockMoveTime = 0.f;
		CheckPushBlock(DIR_LEFT);
	}
	else if (CKeyMgr::GetInstance()->KeyPressing(VK_UP))
	{
		bReturn = true;
		m_tMoveState = MOVE_UP;
		m_tInfo.fY -= m_fSpeed;
		m_eCurKey = DIR_UP;
		if (m_ePrevKey != m_eCurKey) m_fBlockMoveTime = 0.f;
		CheckPushBlock(DIR_UP);
	}
	else if (CKeyMgr::GetInstance()->KeyPressing(VK_RIGHT))
	{
		bReturn = true;
		m_tMoveState = MOVE_RIGHT;
		m_tInfo.fX += m_fSpeed;
		m_eCurKey = DIR_RIGHT;
		if (m_ePrevKey != m_eCurKey) m_fBlockMoveTime = 0.f;
		CheckPushBlock(DIR_RIGHT);
	}
	else if (CKeyMgr::GetInstance()->KeyPressing(VK_DOWN))
	{
		bReturn = true;
		m_tMoveState = MOVE_DOWN;
		m_tInfo.fY += m_fSpeed;
		m_eCurKey = DIR_DOWN;
		if (m_ePrevKey != m_eCurKey) m_fBlockMoveTime = 0.f;
		CheckPushBlock(DIR_DOWN);
	}

	if (m_bBubble == false && CKeyMgr::GetInstance()->KeyDown(VK_SPACE))
	{
		if (CObjMgr::GetInstance()->GetList(OBJ_BOMB).size() < m_iBombMax)
		{
			for (auto& pBomb : CObjMgr::GetInstance()->GetList(OBJ_BOMB))
			{
				if ((((int)m_tInfo.fX / 40) * 40.f + 20) == pBomb->GetInfo().fX &&
					(((int)m_tInfo.fY / 40) * 40.f + 20) == pBomb->GetInfo().fY)
					return false;
			}
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

void CPlayer::CheckPushBlock(DIRECTION eDIR)
{
	float fCheckX = m_tInfo.fX;
	float fCheckY = m_tInfo.fY;
	switch (eDIR)
	{
	case DIR_LEFT:
		fCheckX -= 40.f;
		break;
	case DIR_UP:
		fCheckY -= 40.f;
		break;
	case DIR_RIGHT:
		fCheckX += 40.f;
		break;
	case DIR_DOWN:
		fCheckY += 40.f;
		break;
	}

	for (auto& pBlock : CObjMgr::GetInstance()->GetList(OBJ_BLOCK))
	{
		CBlock* pTempBlock = dynamic_cast<CBlock*>(pBlock);
		if (pTempBlock && pTempBlock->GetBT() != BT_PUSH)
			return;
		if (fabsf(fCheckX - pBlock->GetInfo().fX) <= 20.f
			&& fabsf(fCheckY - pBlock->GetInfo().fY) <= 20.f)
		{
			m_fBlockMoveTime += 1.f;

			if (m_fBlockMoveTime >= 20.f)
			{
				m_fBlockMoveTime = 0;
				dynamic_cast<CBlock*>(pBlock)->SetMove(eDIR);
			}
		}
	}
	
}


