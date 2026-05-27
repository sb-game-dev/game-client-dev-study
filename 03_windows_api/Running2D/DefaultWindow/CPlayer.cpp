#include "pch.h"
#include "CPlayer.h"
#include "CLineMgr.h"
#include "CScrollMgr.h"

CPlayer::CPlayer() :m_time(0), m_eMoveState(MOVE_GROUND), m_bJump(false), m_bFalling(false), m_fPrevX(0.f), m_fPrevY(0.f), m_pCurLine(nullptr)
{
	m_fJumpPower = 12;
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_tInfo = { float(WINCX >> 1), float(WINCY >> 1), 40.f, 40.f };
	m_fSpeed = 5.f;
}

int CPlayer::Update()
{
	if (m_bDead == DEAD)
		return DEAD;
	m_fPrevX = m_tInfo.fX;
	m_fPrevY = m_tInfo.fY;

	KeyInput();
	if (m_eMoveState == MOVE_ROPE)
		m_time = 0;
	if (m_eMoveState == MOVE_GROUND)
	{
		m_time = 0;
		if (CLineMgr::GetInstance()->SetLine(m_tInfo.fX, m_tInfo.fY,m_fPrevX, m_fPrevY) == false)
		{
			m_eMoveState = MOVE_FALL;
		}
		else
		{
			m_pCurLine = CLineMgr::GetInstance()->FindCurrentLine(m_tInfo.fX,m_tInfo.fY);
		}
	}
	__super::Update_Rect();
	return NONEVENT;
}

void CPlayer::LateUpdate()
{
	switch (m_eMoveState)
	{
	case CPlayer::MOVE_GROUND:
		break;
	case CPlayer::MOVE_JUMP:
		Jump();
		break;
	case CPlayer::MOVE_FALL:
		Gravity();
		break;
	case CPlayer::MOVE_DOWNJUMP:
		DownJump();
		break;
	default:
		break;
	}
	if (m_tInfo.fY > WINCY)
		m_bDead = DEAD;
}
void CPlayer::Render(HDC hDC)
{
	float fScrollX = CScrollMgr::GetInstance()->GetScrollX();
	Rectangle(hDC,
		m_tRect.left + fScrollX,
		m_tRect.top,
		m_tRect.right + fScrollX,
		m_tRect.bottom);

	//if (m_pCurLine)
	//{
	//	TCHAR	szBuff[32] = L"";
	//	swprintf_s(szBuff, L"m_eMoveState : %.2f", m_pCurLine->GetLine().tLeft.fX);
	//	TextOut(hDC, 50, 75, szBuff, lstrlen(szBuff));
	//}
	//else
	//{
	//	TCHAR	szBuff[32] = L"";
	//	swprintf_s(szBuff, L"m_eMoveState : %.d", 0);
	//	TextOut(hDC, 50, 75, szBuff, lstrlen(szBuff));
	//}
	//TCHAR	szBuff[32] = L"";
	//swprintf_s(szBuff, L"m_eMoveState : %d", m_eMoveState);
	//TextOut(hDC, 50, 50, szBuff, lstrlen(szBuff));
	//
	//TCHAR	szBuff2[32] = L"";
	//swprintf_s(szBuff2, L"b_Rope : %d", CLineMgr::GetInstance()->CheckRopeLine(m_tInfo.fX, m_tInfo.fY));
	//TextOut(hDC, 50, 100, szBuff2, lstrlen(szBuff2));
	//
	//TCHAR	szBuff3[32] = L"";
	//swprintf_s(szBuff3, L"m_time : %.f", m_time);
	//TextOut(hDC, 50, 125, szBuff3, lstrlen(szBuff3));

	TCHAR	szPlayerX[32] = L"";
	swprintf_s(szPlayerX, L"PlayerX : %.f", m_tInfo.fX);
	TextOut(hDC, 50, 50, szPlayerX, lstrlen(szPlayerX));

	TCHAR	szPlayerY[32] = L"";
	swprintf_s(szPlayerY, L"PlayerY : %.f", m_tInfo.fY);
	TextOut(hDC, 50, 75, szPlayerY, lstrlen(szPlayerY));

}

void CPlayer::Release()
{
}

void CPlayer::KeyInput()
{
	if (GetAsyncKeyState(VK_RIGHT))
	{
		if (m_eMoveState != MOVE_ROPE)
		{
			CScrollMgr::GetInstance()->SetScrollX(-m_fSpeed);
			m_tInfo.fX += m_fSpeed;
		}
		if (m_eMoveState == MOVE_GROUND)
			CLineMgr::GetInstance()->SetLine(m_tInfo.fX, m_tInfo.fY, m_fPrevX, m_fPrevY);
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
		if (m_eMoveState != MOVE_ROPE)
		{	
			CScrollMgr::GetInstance()->SetScrollX(m_fSpeed);
			m_tInfo.fX -= m_fSpeed;
		}
		if (m_eMoveState == MOVE_GROUND)
			CLineMgr::GetInstance()->SetLine(m_tInfo.fX, m_tInfo.fY, m_fPrevX, m_fPrevY);
	}
	if (GetAsyncKeyState(VK_DOWN)&& GetAsyncKeyState(VK_SPACE))
	{
		if (m_eMoveState == MOVE_GROUND)
		{
			m_time = 0.f;
			m_eMoveState = MOVE_DOWNJUMP;
		}
	}
	else if (GetAsyncKeyState(VK_SPACE))
	{
		if(m_eMoveState == MOVE_GROUND)
		{
			m_time = 0.f;
			m_eMoveState = MOVE_JUMP;
		}
		if (m_eMoveState == MOVE_ROPE && (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState(VK_LEFT)))
		{
			m_time = 0.f;
			m_eMoveState = MOVE_JUMP;
		}
	}
	if (CLineMgr::GetInstance()->CheckRopeLine(m_tInfo.fX, m_tInfo.fY))
	{
		if (GetAsyncKeyState(VK_UP))
		{
			CLineMgr::GetInstance()->SetRopeLine(m_tInfo.fX, m_tInfo.fY);
			m_tInfo.fY -= m_fSpeed;
			m_eMoveState = MOVE_ROPE;

			if (!CLineMgr::GetInstance()->CheckRopeLine(m_tInfo.fX, m_tInfo.fY))
			{
				m_eMoveState = MOVE_GROUND;
			}
		}
		if (GetAsyncKeyState(VK_DOWN))
		{
			CLineMgr::GetInstance()->SetRopeLine(m_tInfo.fX, m_tInfo.fY);
			m_tInfo.fY += m_fSpeed;
			m_eMoveState = MOVE_ROPE;

			if (!CLineMgr::GetInstance()->CheckRopeLine(m_tInfo.fX, m_tInfo.fY))
			{
				m_eMoveState = MOVE_FALL;
			}
		}
	}
}

void CPlayer::Jump()
{
	m_time += 0.1f;
	m_tInfo.fY += -m_fJumpPower * m_time + 0.5f * 9.8f * m_time * m_time;
	if (-m_fJumpPower * m_time + 0.5f * 9.8f * m_time * m_time >= 0
		&& CLineMgr::GetInstance()->SetLine(m_tInfo.fX, m_tInfo.fY, m_fPrevX, m_fPrevY))
	{
		m_eMoveState = MOVE_GROUND;
	}
}

void CPlayer::Gravity()
{
	m_time += 0.1f;
	m_tInfo.fY += 0.5f * 9.8f * m_time * m_time;
	if (CLineMgr::GetInstance()->SetLine(m_tInfo.fX, m_tInfo.fY, m_fPrevX, m_fPrevY))
	{
		m_eMoveState = MOVE_GROUND;
	}
}

void CPlayer::DownJump()
{
	m_time += 0.1f;
	m_tInfo.fY += 0.5f * 9.8f * m_time * m_time;
	if (m_pCurLine != nullptr && CLineMgr::GetInstance()->CheckDownJumpLine(m_tInfo.fX, m_tInfo.fY, m_pCurLine))
	{
		m_eMoveState = MOVE_FALL;
	}
}

