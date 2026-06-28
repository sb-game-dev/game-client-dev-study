#include "pch.h"
#include "CMaplePlayer.h"
#include "CKeyMgr.h"
#include "CLineMgr.h"
#include "CBmpMgr.h"

CMaplePlayer::CMaplePlayer():m_eCurMotion(MOTION_END), m_ePreMotion(MOTION_END),m_dwFrameCount(GetTickCount64())
{
}

CMaplePlayer::~CMaplePlayer()
{
}

void CMaplePlayer::Initialize()
{
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

	m_fSpeed = 3.f;
}

int CMaplePlayer::Update()
{
	KeyInput();
	MoveFrame();
	return 0;
}

void CMaplePlayer::LateUpdate()
{

}

void CMaplePlayer::Render(HDC hDC)
{
	HDC hPlayer = CBmpMgr::GetInstance()->FindImage(m_pFrameKey);
	cout << "PlayerRender" << endl;
	GdiTransparentBlt(hDC,					// 목적지 DC
		int(m_tInfo.fX - (m_tFrame.iCX / 2)),	// 목적지 LEFT, TOP
		int(m_tInfo.fY - (m_tFrame.iCY - m_tInfo.fCY * 0.5)),
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
		m_eMoveState = MOVE_GROUND;
		
		m_tInfo.fX += m_fSpeed;
		ChangeMotion();
	}
	else if (CKeyMgr::GetInstance()->KeyPressing(VK_LEFT))
	{
		m_pFrameKey = L"Player_LEFT";
		m_eMoveState = MOVE_GROUND;
		
		m_tInfo.fX -= m_fSpeed; 
		ChangeMotion();
	}
	else
	{
		m_eMoveState = MOVE_IDLE;
		ChangeMotion();
	}
	if (CKeyMgr::GetInstance()->KeyPressing(VK_MENU))
	{
		//Jump();
		m_eMoveState = MOVE_JUMP;
		ChangeMotion();
	}
}
void CMaplePlayer::ChangeMotion()
{
	if (m_ePreMoveState == m_eMoveState)
		return;
	switch (m_eMoveState)
	{
	case MOVE_IDLE:
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 5;
		m_tFrame.iMotion = 0;
		m_tFrame.bLoop = true;
		m_tFrame.dwSpeed = 100.f;
		m_tFrame.dwTime = GetTickCount64();
		break;
	case MOVE_GROUND:
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 3;
		m_tFrame.iMotion = 1;
		m_tFrame.bLoop = true;
		m_tFrame.dwSpeed = 100.f;
		m_tFrame.dwTime = GetTickCount64();
		break;
	case MOVE_JUMP:
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 1;
		m_tFrame.iMotion = 6;
		m_tFrame.bLoop = true;
		m_tFrame.dwSpeed = 100.f;
		m_tFrame.dwTime = GetTickCount64();
		break;
	case MOVE_FALL:
		break;
	}
	m_ePreMoveState = m_eMoveState;
}

void CMaplePlayer::CheckFrame()
{

}

void CMaplePlayer::Jump()
{
	m_time += 0.1f;
	m_tInfo.fY += -m_fJumpPower * m_time + 0.5f * 9.8f * m_time * m_time;
	if (-m_fJumpPower * m_time + 0.5f * 9.8f * m_time * m_time >= 0
		&& CLineMgr::GetInstance()->SetLine(m_tInfo.fX, m_tInfo.fY, m_fPrevX, m_fPrevY))
	{
		m_eMoveState = MOVE_GROUND;
	}
}

void CMaplePlayer::Gravity()
{
	m_time += 0.1f;
	m_tInfo.fY += 0.5f * 9.8f * m_time * m_time;
	if (CLineMgr::GetInstance()->SetLine(m_tInfo.fX, m_tInfo.fY, m_fPrevX, m_fPrevY))
	{
		m_eMoveState = MOVE_GROUND;
	}
}

void CMaplePlayer::DownJump()
{
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