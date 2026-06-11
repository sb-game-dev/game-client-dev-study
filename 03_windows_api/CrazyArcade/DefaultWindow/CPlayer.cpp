#include "pch.h"
#include "CPlayer.h"
#include "CKeyMgr.h"
#include "CImgMgr.h"
#include "CObjMgr.h"
#include "CTile.h"
#include "CAbstractFactory.h"
#include "CBomb.h"
#include "CBmpMgr.h"
CPlayer::CPlayer():m_ePreMotion(MOTION_END), m_eCurMotion(START), m_fWalkSpeed(3.f), m_fBubbleSpeed(0.5f), m_dwFrameCount(GetTickCount64()),
m_fBlockMoveTime(0.f), m_iBombRange(2), m_iBombMax(2)
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Player/player_start.bmp", L"player_start");
	
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Player/player_down.bmp", L"player_down");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Player/player_up.bmp", L"player_up");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Player/player_left.bmp", L"player_left");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Player/player_right.bmp", L"player_right");
	
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Player/player_hit.bmp", L"player_hit");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Player/player_death.bmp", L"player_death");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Player/player_live2.bmp", L"player_live");
	
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;

	m_fSpeed = 0;
	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 18;
	m_tFrame.iMotion = 0;
	m_tFrame.bLoop = false;
	m_tFrame.iCX = PLAYER_CX;
	m_tFrame.iCY = 67;
	m_tFrame.dwSpeed = 50.f;
	m_tFrame.dwTime = GetTickCount64();

	m_eRenderID = GAMEOBJECT;
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

void CPlayer::Render(HDC hDC)
{
	Rectangle(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);

	HDC hPlayer = CBmpMgr::GetInstance()->FindImage(m_pFrameKey);

	GdiTransparentBlt(hDC,					// 목적지 DC
		int(m_tInfo.fX - (m_tFrame.iCX / 2)),	// 목적지 LEFT, TOP
		int(m_tInfo.fY - (m_tFrame.iCY - m_tInfo.fCY * 0.5)),
		m_tFrame.iCX,			// 목적지 공간의 가로, 세로 사이즈
		m_tFrame.iCY,
		hPlayer,						// 원본 이미지 DC
		m_tFrame.iCX * m_tFrame.iStart,	// 원본 이미지 LEFT, TOP
		0,
		m_tFrame.iCX,			// 원본 이미지 가로, 세로 사이즈
		m_tFrame.iCY,
		RGB(255, 0, 255));		// 제거할 픽셀 색상

	//Graphics* _pGraphics = Graphics::FromHDC(hDC);
	//Gdiplus::Image* pImg = CImgMgr::GetInstance()->FindImg(m_pFrameKey);
	//
	//Rect rect = {int(m_tInfo.fX - (m_tFrame.iCX/2)),
	//			int(m_tInfo.fY - (m_tFrame.iCY - m_tInfo.fCY*0.5)),
	//			m_tFrame.iCX,
	//			m_tFrame.iCY };
	//
	//ImageAttributes attr;
	//attr.SetColorKey(
	//	Color(255,0, 255),
	//	Color(255,0, 255));
	//
	//_pGraphics->DrawImage(pImg, rect,
	//	m_tFrame.iCX * m_tFrame.iStart, m_tFrame.iCY * m_tFrame.iMotion,
	//	m_tFrame.iCX, m_tFrame.iCY,
	//	UnitPixel,
	//	&attr);

	//int x = (AdjustPosX(m_tInfo.fX) - MAP_LEFT) / TILECX;
	//int y = (AdjustPosY(m_tInfo.fY) - MAP_TOP) / TILECX;
	//
	//int Index = y * MAP_CNT_X + x;
	//
	//TCHAR	szBuff[32] = L"";
	//swprintf_s(szBuff, L"PlayerX : %.0f", m_tInfo.fX);
	//TextOut(hDC, 50, 50, szBuff, lstrlen(szBuff));
	//TCHAR	szBuff2[32] = L"";
	//swprintf_s(szBuff2, L"PlayerY : %.0f", m_tInfo.fY);
	//TextOut(hDC, 50, 75, szBuff2, lstrlen(szBuff2));
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

		if (m_eCurMotion != m_ePreMotion)
			m_fBlockMoveTime = 0.f;
		ChangeMotion();
		CheckPushBlock(DIR_RIGHT);
		m_tInfo.fX += m_fSpeed;
	}
	else if (CKeyMgr::GetInstance()->KeyPressing(VK_LEFT) && m_tRect.left > 20)
	{
		if (m_eCurMotion != HIT)
			m_eCurMotion = LEFT;
		if (m_eCurMotion != m_ePreMotion)
			m_fBlockMoveTime = 0.f;
		ChangeMotion();
		CheckPushBlock(DIR_LEFT);
		m_tInfo.fX -= m_fSpeed;
	}
	else if (CKeyMgr::GetInstance()->KeyPressing(VK_UP) && m_tRect.top > 40)
	{
		if (m_eCurMotion != HIT)
			m_eCurMotion = UP;
		if (m_eCurMotion != m_ePreMotion)
			m_fBlockMoveTime = 0.f;
		ChangeMotion();
		CheckPushBlock(DIR_UP);
		m_tInfo.fY -= m_fSpeed;
	}
	else if (CKeyMgr::GetInstance()->KeyPressing(VK_DOWN) && m_tRect.bottom < 560)
	{
		if (m_eCurMotion != HIT)
			m_eCurMotion = DOWN;
		if (m_eCurMotion != m_ePreMotion)
			m_fBlockMoveTime = 0.f;
		ChangeMotion();
		CheckPushBlock(DIR_DOWN);
		m_tInfo.fY += m_fSpeed;
	}
	else
	{
		m_fBlockMoveTime = 0.f;
		if (m_eCurMotion != HIT && m_eCurMotion != REVIVAL)
			m_eCurMotion = IDLE;
		ChangeMotion();
	}
	if (CKeyMgr::GetInstance()->KeyDown(VK_SPACE))
	{
		if (CObjMgr::GetInstance()->GetList(OBJ_BOMB).size() < m_iBombMax)
		{
			for (auto& pBomb : CObjMgr::GetInstance()->GetList(OBJ_BOMB))
			{
				if (AdjustPosX(m_tInfo.fX) == pBomb->GetInfo()->fX 
					&& AdjustPosY(m_tInfo.fY) == pBomb->GetInfo()->fY)
					return;
			}
			CreateBomb();
		}
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
		m_tFrame.iCX = 70;
		m_tFrame.iCY = 89;
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
		m_tFrame.iCX = 70;
		m_tFrame.iCY = 115;
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
		m_tFrame.iCX = 70;
		m_tFrame.iCY = 91;
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

	for (auto& pTile : CObjMgr::GetInstance()->GetTile())
	{
		CTile* pTempTile = dynamic_cast<CTile*>(pTile);
		if (pTempTile->GetFrame().iStart == 2)
		{
			if (fabsf(fCheckX - pTempTile->GetInfo()->fX) <= 15.f
				&& fabsf(fCheckY - pTempTile->GetInfo()->fY) <= 15.f)
			{
				m_fBlockMoveTime += 1.f;

				if (m_fBlockMoveTime >= 20.f)
				{
					m_fBlockMoveTime = 0;
					pTempTile->SetMove(eDIR);
				}
			}
		}
	}

}

void CPlayer::CreateBomb()
{
	float fX = AdjustPosX(m_tInfo.fX);
	float fY = AdjustPosY(m_tInfo.fY);
	CObj* pBomb = CAbstractFactory<CBomb>::Create(fX, fY, L"BlueBubble");
	pBomb->SetCanMove(false);
	dynamic_cast<CBomb*>(pBomb)->SetBombRange(m_iBombRange);
	CObjMgr::GetInstance()->AddObject(OBJ_BOMB, pBomb);
}
