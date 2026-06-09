#include "pch.h"
#include "CPlayer.h"
#include "CKeyMgr.h"
#include "CImgMgr.h"
CPlayer::CPlayer():m_ePreMotion(MOTION_END), m_eCurMotion(START), m_fWalkSpeed(3.f), m_fBubbleSpeed(0.5f), m_dwFrameCount(GetTickCount64())
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	CImgMgr::GetInstance()->InsertImg(L"../Resource/Player/player_start2.png", L"player_start");

	CImgMgr::GetInstance()->InsertImg(L"../Resource/Player/player_down.png", L"player_down");
	CImgMgr::GetInstance()->InsertImg(L"../Resource/Player/player_up.png", L"player_up");
	CImgMgr::GetInstance()->InsertImg(L"../Resource/Player/player_left.png", L"player_left");
	CImgMgr::GetInstance()->InsertImg(L"../Resource/Player/player_right.png", L"player_right");


	CImgMgr::GetInstance()->InsertImg(L"../Resource/Player/player_hit.png", L"player_hit");
	CImgMgr::GetInstance()->InsertImg(L"../Resource/Player/player_death.png", L"player_death");
	CImgMgr::GetInstance()->InsertImg(L"../Resource/Player/player_live2.png", L"player_live");

	m_tInfo = { float(WINCX >> 1), float(WINCY >> 1), 40.f, 40.f };

	m_fSpeed = 0;
	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 18;
	m_tFrame.iMotion = 0;
	m_tFrame.bLoop = false;
	m_tFrame.iCX = PLAYER_CX;
	m_tFrame.iCY = 67;
	m_tFrame.dwSpeed = 50.f;
	m_tFrame.dwTime = GetTickCount64();

}

int CPlayer::Update()
{
	if (m_bDead == DEAD)
		return DEAD;

	if (m_eCurMotion != DEATH && m_eCurMotion != START)
		KeyInput();
	CheckFrame();
	MoveFrame();

	return NOEVENT;
}


void CPlayer::LateUpdate()
{
	
}

void CPlayer::Render(Graphics* _pGraphics)
{
	Font myFont(L"Arial", 16, FontStyleRegular, UnitPixel);
	
	SolidBrush redBrush(Color(255, 255, 255, 255));
	_pGraphics->DrawString(m_pFrameKey, -1, &myFont, PointF(10.0f, 20.0f), &redBrush);

	Pen BlackPen(Color(255, 0, 0, 0), 1.0f);
	Rect playerRect = { m_tRect.left,m_tRect.top,int(m_tInfo.fCX),(int)m_tInfo.fCY};
	_pGraphics->DrawRectangle(&BlackPen, playerRect); //(&BlackPen, 0, 0, 60, 30);

	Gdiplus::Image* pImg = CImgMgr::GetInstance()->FindImg(m_pFrameKey);

	Rect rect = {int(m_tInfo.fX - (m_tFrame.iCX/2)),
				int(m_tInfo.fY - (m_tFrame.iCY - m_tInfo.fCY*0.5)),
				m_tFrame.iCX,
				m_tFrame.iCY };

	ImageAttributes attr;
	attr.SetColorKey(
		Color(255,0, 255),
		Color(255,0, 255));

	_pGraphics->DrawImage(pImg, rect,
		m_tFrame.iCX * m_tFrame.iStart, m_tFrame.iCY * m_tFrame.iMotion,
		m_tFrame.iCX, m_tFrame.iCY,
		UnitPixel,
		&attr);
}

void CPlayer::Release()
{
}



void CPlayer::KeyInput()
{
	if (CKeyMgr::GetInstance()->KeyPressing(VK_RIGHT) && m_tRect.right < 620)
	{
		if(m_eCurMotion != HIT)
			m_eCurMotion = RIGHT;
		ChangeMotion();
		m_tInfo.fX += m_fSpeed;
	}
	else if (CKeyMgr::GetInstance()->KeyPressing(VK_LEFT) && m_tRect.left > 20)
	{
		if (m_eCurMotion != HIT)
			m_eCurMotion = LEFT;
		ChangeMotion();
		m_tInfo.fX -= m_fSpeed;
	}
	else if (CKeyMgr::GetInstance()->KeyPressing(VK_UP) && m_tRect.top > 40)
	{
		if (m_eCurMotion != HIT)
			m_eCurMotion = UP;
		ChangeMotion();
		m_tInfo.fY -= m_fSpeed;
	}
	else if (CKeyMgr::GetInstance()->KeyPressing(VK_DOWN) && m_tRect.bottom < 560)
	{
		if (m_eCurMotion != HIT)
			m_eCurMotion = DOWN;
		ChangeMotion();
		m_tInfo.fY += m_fSpeed;
	}
	// Test
	else if (CKeyMgr::GetInstance()->KeyDown(VK_SPACE))
	{
		if (m_eCurMotion != HIT)
			m_eCurMotion = HIT;
		else if(m_eCurMotion == HIT)
			m_eCurMotion = REVIVAL;
		ChangeMotion();
	}
	else
	{
		if (m_eCurMotion != HIT && m_eCurMotion != REVIVAL)
			m_eCurMotion = IDLE;
		ChangeMotion();
	}
	

	
}

void CPlayer::ChangeMotion()
{
	if (m_ePreMotion == m_eCurMotion)
		return;
	switch (m_eCurMotion)
	{
	case IDLE:
		m_fSpeed = m_fWalkSpeed;
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 1;
		m_tFrame.iMotion = 0;
		m_tFrame.bLoop = false;
		m_tFrame.iCX = PLAYER_CX;
		m_tFrame.iCY = PLAYER_CY;
		m_tFrame.dwSpeed = 100.f;
		m_tFrame.dwTime = GetTickCount64();
		break;
	case LEFT:
		m_fSpeed = m_fWalkSpeed;
		m_pFrameKey = L"player_left";
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 6;
		m_tFrame.iMotion = 0;
		m_tFrame.bLoop = true;
		m_tFrame.iCX = PLAYER_CX;
		m_tFrame.iCY = PLAYER_CY;
		m_tFrame.dwSpeed = 100.f;
		m_tFrame.dwTime = GetTickCount64();
		break;
	case RIGHT:
		m_fSpeed = m_fWalkSpeed;
		m_pFrameKey = L"player_right";
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 6;
		m_tFrame.iMotion = 0;
		m_tFrame.bLoop = true;
		m_tFrame.iCX = PLAYER_CX;
		m_tFrame.iCY = PLAYER_CY;
		m_tFrame.dwSpeed = 100.f;
		m_tFrame.dwTime = GetTickCount64();
		break;
	case UP:
		m_fSpeed = m_fWalkSpeed;
		m_pFrameKey = L"player_up";
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 8;
		m_tFrame.iMotion = 0;
		m_tFrame.bLoop = true;
		m_tFrame.iCX = PLAYER_CX;
		m_tFrame.iCY = PLAYER_CY;
		m_tFrame.dwSpeed = 100.f;
		m_tFrame.dwTime = GetTickCount64();
		break;
	case DOWN:
		m_fSpeed = m_fWalkSpeed;
		m_pFrameKey = L"player_down";
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 8;
		m_tFrame.iMotion = 0;
		m_tFrame.bLoop = true;
		m_tFrame.iCX = PLAYER_CX;
		m_tFrame.iCY = PLAYER_CY;
		m_tFrame.dwSpeed = 100.f;
		m_tFrame.dwTime = GetTickCount64();
		break;
	case HIT:
		m_fSpeed = m_fBubbleSpeed;
		m_pFrameKey = L"player_hit";
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 13;
		m_tFrame.iMotion = 0;
		m_tFrame.bLoop = false;
		m_tFrame.iCX = 88;
		m_tFrame.iCY = 114;
		m_tFrame.dwSpeed = 150.f;
		m_tFrame.dwTime = GetTickCount64();
		m_dwFrameCount = GetTickCount64();
		break;
	case DEATH:
		m_fSpeed = 0;
		m_pFrameKey = L"player_death";
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 15;
		m_tFrame.iMotion = 0;
		m_tFrame.bLoop = false;
		m_tFrame.iCX = 88;
		m_tFrame.iCY = 144;
		m_tFrame.dwSpeed = 100.f;
		m_tFrame.dwTime = GetTickCount64();
		m_dwFrameCount = GetTickCount64();
		break;
	case REVIVAL:
		m_fSpeed = 0;
		m_pFrameKey = L"player_live";
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 5;
		m_tFrame.iMotion = 0;
		m_tFrame.bLoop = false;
		m_tFrame.iCX = 88;
		m_tFrame.iCY = 116;
		m_tFrame.dwSpeed = 100.f;
		m_tFrame.dwTime = GetTickCount64();
		m_dwFrameCount = GetTickCount64();
		break;
	case MOTION_END:
		break;
	default:
		break;
	}
	m_ePreMotion = m_eCurMotion;
}

void CPlayer::CheckFrame()
{
	if (m_eCurMotion == START
		&& m_dwFrameCount + m_tFrame.dwSpeed * m_tFrame.iEnd <= GetTickCount64())
	{
		m_eCurMotion = DOWN;
		ChangeMotion();
	}
	if (m_eCurMotion == HIT 
		&& m_dwFrameCount + m_tFrame.dwSpeed * m_tFrame.iEnd <= GetTickCount64())
	{
		m_eCurMotion = DEATH;
		ChangeMotion();
	}
	if (m_eCurMotion == DEATH 
		&& m_dwFrameCount + m_tFrame.dwSpeed * m_tFrame.iEnd <= GetTickCount64())
	{
		m_bDead = DEAD;
	}
	if (m_eCurMotion == REVIVAL
		&& m_dwFrameCount + m_tFrame.dwSpeed * m_tFrame.iEnd <= GetTickCount64()) //m_tFrame.iStart - 1 >= m_tFrame.iEnd
	{
		m_eCurMotion = DOWN;
		m_pFrameKey = L"player_down";
		ChangeMotion();
	}
}
