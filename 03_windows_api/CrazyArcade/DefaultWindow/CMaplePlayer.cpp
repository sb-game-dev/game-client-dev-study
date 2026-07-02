#include "pch.h"
#include "CMaplePlayer.h"
#include "CKeyMgr.h"
#include "CLineMgr.h"
#include "CBmpMgr.h"
#include "CScrollMgr.h"
#include "CSoundMgr.h"

CMaplePlayer::CMaplePlayer() :m_eCurMotion(MOTION_END), m_ePreMotion(MOTION_END), m_dwFrameCount(GetTickCount64()),
m_time(0), m_ePreMoveState(MOVE_GROUND), m_eMoveState(MOVE_GROUND), m_bJump(false), m_bFalling(false), m_fPrevX(0.f), m_fPrevY(0.f), m_pCurLine(nullptr), m_fJumpPower(10),
m_bMoveFrame(true), m_fOffsetSpeed(0.f), m_bOffsetMove(false)
{
}

CMaplePlayer::~CMaplePlayer()
{
}

void CMaplePlayer::Initialize()
{

	CLine* pLine = CLineMgr::GetInstance()->GetFirstLine();

	float y = pLine->GetLine().tLeft.fY;

	m_tInfo.fY = y;

	m_eRenderID = GAMEOBJECT;

	m_tInfo.fCX = 32.f;
	m_tInfo.fCY = 32.f;

	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 5;
	m_tFrame.iMotion = 0;
	m_tFrame.bLoop = true;
	m_tFrame.iCX = 100;
	m_tFrame.iCY = 100;
	m_tFrame.dwSpeed = 100.f;
	m_tFrame.dwTime = GetTickCount64();

	m_eCurMotion = IDLE;
	ChangeMotion();

	m_fSpeed = 2.f;
}

int CMaplePlayer::Update()
{
	m_fPrevX = m_tInfo.fX;
	m_fPrevY = m_tInfo.fY;

	KeyInput();
	if(m_bMoveFrame)
		MoveFrame();

	//cout << CLineMgr::GetInstance()->CheckRopeLine(m_tInfo.fX, m_tInfo.fY) << endl;
	
	if (m_eMoveState == MOVE_ROPE)
		m_time = 0;
	if (m_eMoveState == MOVE_GROUND)
	{
		m_time = 0;
		if (CLineMgr::GetInstance()->SetLine(m_tInfo.fX, m_tInfo.fY, m_fPrevX, m_fPrevY) == false)
		{
			m_eMoveState = MOVE_FALL;
		}
		else
		{
			m_pCurLine = CLineMgr::GetInstance()->FindCurrentLine(m_tInfo.fX, m_tInfo.fY);
		}
	}

	return 0;
}

void CMaplePlayer::LateUpdate()
{
	switch (m_eMoveState)
	{
	case MOVE_GROUND:
		//cout << "MOVE_GROUND" << endl;
		break;
	case MOVE_JUMP:
		//cout << "MOVE_JUMP" << endl;
		Jump();
		break;
	case MOVE_FALL:
		//cout << "MOVE_FALL" << endl;
		Gravity();
		break;
	case MOVE_DOWNJUMP:
		//cout << "MOVE_DOWNJUMP" << endl;
		DownJump();
		break;
	case MOVE_TAKEDAMAGER:
		//cout << "MOVE_TAKEDAMAGER" << endl;
		TakeDamage();
		break;
	case MOVE_TAKEDAMAGEL:
		//cout << "MOVE_TAKEDAMAGEL" << endl;
		TakeDamage();
		break;
	default:
		break;
	}

	Offset();
}

void CMaplePlayer::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::GetInstance()->GetScrollX();
	int iScrollY = (int)CScrollMgr::GetInstance()->GetScrollY();

	HDC hPlayer = CBmpMgr::GetInstance()->FindImage(m_pFrameKey);
	GdiTransparentBlt(hDC,					// 목적지 DC
		int(m_tInfo.fX - (m_tFrame.iCX / 2.f)) + iScrollX,	// 목적지 LEFT, TOP
		int(m_tInfo.fY - (m_tFrame.iCY - m_tInfo.fCY * 0.5)) + iScrollY,
		m_tFrame.iCX,			// 목적지 공간의 가로, 세로 사이즈
		m_tFrame.iCY,
		hPlayer,						// 원본 이미지 DC
		m_tFrame.iCX * m_tFrame.iStart,	// 원본 이미지 LEFT, TOP
		m_tFrame.iCY * m_tFrame.iMotion,
		m_tFrame.iCX,			// 원본 이미지 가로, 세로 사이즈
		m_tFrame.iCY,
		RGB(0, 255, 0));		// 제거할 픽셀 색상
}

void CMaplePlayer::Release()
{
}

void CMaplePlayer::KeyInput()
{
	if (CKeyMgr::GetInstance()->KeyPressing(VK_RIGHT))
	{
		m_pFrameKey = L"Player_RIGHT";
		m_eCurMotion = RIGHT;
		if (m_eMoveState != MOVE_ROPE)
		{
			m_tInfo.fX += m_fSpeed;
		}
		ChangeMotion();
	}
	else if (CKeyMgr::GetInstance()->KeyPressing(VK_LEFT))
	{
		m_pFrameKey = L"Player_LEFT";
		m_eCurMotion = LEFT; 
		if (m_eMoveState != MOVE_ROPE)
		{
			m_tInfo.fX -= m_fSpeed;
		}
		ChangeMotion();
	}
	else
	{
		m_eCurMotion = IDLE;
		ChangeMotion();
	}

	if (CKeyMgr::GetInstance()->KeyPressing(VK_DOWN))
	{
		if (m_eMoveState == MOVE_GROUND)
		{
			m_eCurMotion = DOWN;
			ChangeMotion();
		}

		if (CKeyMgr::GetInstance()->KeyDown(VK_SPACE) && m_eMoveState == MOVE_GROUND)
		{
			m_time = 0.f;
			m_eMoveState = MOVE_DOWNJUMP;
		}
	}
	if (CKeyMgr::GetInstance()->KeyPressing(VK_SPACE))
	{
		if (m_eMoveState == MOVE_GROUND)
		{
			m_time = 0.f;
			m_eMoveState = MOVE_JUMP;
			m_eCurMotion = JUMP;
			CSoundMgr::Get_Instance()->PlaySound(L"jump.mp3", PLAYER_BUBBLE, 0.4f);
			ChangeMotion();
		}
	}
	if (CLineMgr::GetInstance()->CheckRopeLine(m_tInfo.fX, m_tInfo.fY))
	{
		if (m_eMoveState == MOVE_ROPE)
		{
			m_eCurMotion = ROPE;
			ChangeMotion();
		}
		m_bMoveFrame = false;
		if (CKeyMgr::GetInstance()->KeyPressing(VK_UP))
		{
			m_bMoveFrame = true;
			CLineMgr::GetInstance()->SetRopeLine(m_tInfo.fX, m_tInfo.fY);
				m_tInfo.fY -= m_fSpeed;
			m_eMoveState = MOVE_ROPE;
			if (!CLineMgr::GetInstance()->CheckRopeLine(m_tInfo.fX, m_tInfo.fY))
			{
				m_eMoveState = MOVE_GROUND;
				m_eCurMotion = IDLE;
				ChangeMotion();
			}
		}
		if (CKeyMgr::GetInstance()->KeyPressing(VK_DOWN))
		{
			m_bMoveFrame = true;
			CLineMgr::GetInstance()->SetRopeLine(m_tInfo.fX, m_tInfo.fY);
			m_tInfo.fY += m_fSpeed;
			m_eMoveState = MOVE_ROPE;
			m_eCurMotion = ROPE;
			ChangeMotion();

			if (!CLineMgr::GetInstance()->CheckRopeLine(m_tInfo.fX, m_tInfo.fY))
			{
				m_eMoveState = MOVE_FALL;
				m_eCurMotion = IDLE;
				ChangeMotion();
			}
		}
		if ((CKeyMgr::GetInstance()->KeyPressing(VK_RIGHT) || CKeyMgr::GetInstance()->KeyPressing(VK_LEFT)) && CKeyMgr::GetInstance()->KeyPressing(VK_SPACE))
		{
			m_time = 0.f;
			m_eMoveState = MOVE_FALL;
		}
	}
	else
	{
		m_bMoveFrame = true;
	}
	if (CKeyMgr::GetInstance()->KeyPressing('W'))
	{
		CScrollMgr::GetInstance()->SetScrollY(20.f);
	}
	if (CKeyMgr::GetInstance()->KeyPressing('S'))
	{
		CScrollMgr::GetInstance()->SetScrollY(-20.f);
	}
	if (CKeyMgr::GetInstance()->KeyPressing('A'))
	{
		CScrollMgr::GetInstance()->SetScrollX(20.f);
	}
	if (CKeyMgr::GetInstance()->KeyPressing('D'))
	{
		CScrollMgr::GetInstance()->SetScrollX(-20.f);
	}
}
void CMaplePlayer::ChangeMotion()
{
	if (m_ePreMotion == m_eCurMotion)
		return;
	switch (m_eCurMotion)
	{
	case IDLE:
		cout << "IDLE" << endl;
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 5;
		m_tFrame.iMotion = 0;
		m_tFrame.bLoop = true;
		m_tFrame.dwSpeed = 100.f;
		m_tFrame.dwTime = GetTickCount64();
		break;
	case LEFT:
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 3;
		m_tFrame.iMotion = 1;
		m_tFrame.bLoop = true;
		m_tFrame.dwSpeed = 100.f;
		m_tFrame.dwTime = GetTickCount64();
		break;
	case RIGHT:
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 3;
		m_tFrame.iMotion = 1;
		m_tFrame.bLoop = true;
		m_tFrame.dwSpeed = 100.f;
		m_tFrame.dwTime = GetTickCount64();
		break;
	case JUMP:
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 1;
		m_tFrame.iMotion = 6;
		m_tFrame.bLoop = true;
		m_tFrame.dwSpeed = 100.f;
		m_tFrame.dwTime = GetTickCount64();
		break;
	case DOWN:
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 1;
		m_tFrame.iMotion = 4;
		m_tFrame.bLoop = true;
		m_tFrame.dwSpeed = 100.f;
		m_tFrame.dwTime = GetTickCount64();
		break;
	case ROPE:
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 2;
		m_tFrame.iMotion = 7;
		m_tFrame.bLoop = true;
		m_tFrame.dwSpeed = 150.f;
		m_tFrame.dwTime = GetTickCount64();
		break;
	}
	m_ePreMotion = m_eCurMotion;
}

void CMaplePlayer::CheckFrame()
{

}

void CMaplePlayer::Jump()
{
	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 1;
	m_tFrame.iMotion = 6;
	m_tFrame.bLoop = true;
	m_tFrame.dwSpeed = 100.f;
	m_tFrame.dwTime = GetTickCount64();

	m_time += 0.1f;
	m_tInfo.fY += -m_fJumpPower * m_time + 0.5f * 9.8f * m_time * m_time;

	if (-m_fJumpPower * m_time + 0.5f * 9.8f * m_time * m_time >= 0
		&& CLineMgr::GetInstance()->SetLine(m_tInfo.fX, m_tInfo.fY, m_fPrevX, m_fPrevY))
	{
		m_eMoveState = MOVE_GROUND; 
		m_eCurMotion = IDLE;

		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 5;
		m_tFrame.iMotion = 0;
		m_tFrame.bLoop = true;
		m_tFrame.dwSpeed = 100.f;
		m_tFrame.dwTime = GetTickCount64();
		ChangeMotion();
	}
}

void CMaplePlayer::Gravity()
{
	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 1;
	m_tFrame.iMotion = 6;
	m_tFrame.bLoop = true;
	m_tFrame.dwSpeed = 100.f;
	m_tFrame.dwTime = GetTickCount64();

	m_time += 0.1f;
	m_tInfo.fY += 0.5f * 9.8f * m_time * m_time;
	if (CLineMgr::GetInstance()->SetLine(m_tInfo.fX, m_tInfo.fY, m_fPrevX, m_fPrevY))
	{
		m_eMoveState = MOVE_GROUND;
		m_eCurMotion = IDLE;

		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 5;
		m_tFrame.iMotion = 0;
		m_tFrame.bLoop = true;
		m_tFrame.dwSpeed = 100.f;
		m_tFrame.dwTime = GetTickCount64();
		ChangeMotion();
	}
}

void CMaplePlayer::DownJump()
{
	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 1;
	m_tFrame.iMotion = 6;
	m_tFrame.bLoop = true;
	m_tFrame.dwSpeed = 100.f;
	m_tFrame.dwTime = GetTickCount64();

	m_time += 0.1f;
	m_tInfo.fY += 0.5f * 9.8f * m_time * m_time;
	if (m_pCurLine != nullptr && CLineMgr::GetInstance()->CheckDownJumpLine(m_tInfo.fX, m_tInfo.fY, m_pCurLine))
	{
		m_eMoveState = MOVE_FALL;
	}
}

void CMaplePlayer::TakeDamage()
{
	m_time += 0.1f;
	m_tInfo.fY += -m_fJumpPower * 0.5f * m_time + 0.5f * 9.8f * m_time * m_time;
	if (m_time <= 1.5f)
	{
		if (m_eMoveState == MOVE_TAKEDAMAGEL)
			m_tInfo.fX += m_time + 0.5f * 9.8f * m_time * m_time;
		else
			m_tInfo.fX -= m_time + 0.5f * 9.8f * m_time * m_time;
	}
	if (-m_fJumpPower * 0.5f * m_time + 0.5f * 9.8f * m_time * m_time >= 0
		&& CLineMgr::GetInstance()->SetLine(m_tInfo.fX, m_tInfo.fY, m_fPrevX, m_fPrevY))
	{
		m_eMoveState = MOVE_GROUND;
	}
}

void CMaplePlayer::Offset()
{
	int iOffsetminX = 300;
	int iOffsetmaxX = WINCX - 300;

	int iOffsetminY = 300;
	int iOffsetmaxY = WINCY - 100;

	int iScrollX = (int)CScrollMgr::GetInstance()->GetScrollX();
	int iScrollY = (int)CScrollMgr::GetInstance()->GetScrollY();

	if (iOffsetminX > m_tInfo.fX + iScrollX)
	{
		if (iScrollX < 0)
		{
			CScrollMgr::GetInstance()->SetScrollX((m_fSpeed));
		}
	}
	
	if (iOffsetmaxX < m_tInfo.fX + iScrollX)
	{
		if (iScrollX > -1920)
		{
			CScrollMgr::GetInstance()->SetScrollX(-(m_fSpeed));
		}
	}

	if (iOffsetminY > m_tInfo.fY + iScrollY)
	{
		CScrollMgr::GetInstance()->SetScrollY((m_fSpeed));
	}

	if (iOffsetmaxY < m_tInfo.fY + iScrollY)
	{
		if (iScrollY > 0)
		{
			if(m_bOffsetMove)
				m_fOffsetSpeed += 0.3f;
			CScrollMgr::GetInstance()->SetScrollY(-(m_fSpeed + m_fOffsetSpeed));
		}
	}
	else
	{
		m_fOffsetSpeed = 0;
	}
	if (iScrollY < 0)
		CScrollMgr::GetInstance()->SetScrollYZero();
	if (m_bOffsetMove == false && iScrollY == 0)
	{
		m_bOffsetMove = true;
	}
}