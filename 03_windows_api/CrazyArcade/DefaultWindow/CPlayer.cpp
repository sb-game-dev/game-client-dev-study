#include "pch.h"
#include "CPlayer.h"
#include "CKeyMgr.h"
#include "CImgMgr.h"
#include "CObjMgr.h"
#include "CTile.h"
#include "CAbstractFactory.h"
#include "CBomb.h"
#include "CBmpMgr.h"
#include "CDart.h"
#include "CCollisionMgr.h"
#include "CSoundMgr.h"
CPlayer::CPlayer():m_ePreMotion(MOTION_END), m_eCurMotion(START), m_fWalkSpeed(3.f), m_fBubbleSpeed(0.5f), m_dwFrameCount(GetTickCount64()),
m_fBlockMoveTime(0.f), m_iBombRange(1), m_iBombMax(1), m_iBombCnt(0), m_bShowItemGainEffect(false), m_eItemFrameKey(ITEMTYPE_END),
m_dwItemEffectFrameCount(GetTickCount64()),m_iCtrlSlotCnt(0), m_eCtrlSlot(ITEMTYPE_END), m_dwShieldEffectFrameCount(GetTickCount64())
{
	m_bShowShieldEffect = false;
	m_iShieldFrame = 0;

	m_fKickBombTime = 0.f;
#ifdef _DEBUG
	m_bShoe = true;
#elif NDEBUG
	m_bShoe = false;
#endif // _DEBUG

}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{	
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
#ifdef _DEBUG
	Rectangle(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);
#endif // _DEBUG

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
	if (m_bShowItemGainEffect == true)
	{
		ShowItemGainEffect(hDC);
	}
	if (m_iCtrlSlotCnt > 0)
	{
		ShowCtrlSlot(hDC);
	}
	if (m_bShowShieldEffect == true)
	{
		ShowShield(hDC);
	}

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
		{
			m_fBlockMoveTime = 0.f;
			m_fKickBombTime = 0.f;
		}
		ChangeMotion();
		CheckPushBlock(DIR_RIGHT);
		CheckKickBomb(DIR_RIGHT);
		m_tInfo.fX += m_fSpeed;
	}
	else if (CKeyMgr::GetInstance()->KeyPressing(VK_LEFT) && m_tRect.left > 20)
	{
		if (m_eCurMotion != HIT)
			m_eCurMotion = LEFT;
		if (m_eCurMotion != m_ePreMotion)
		{
			m_fBlockMoveTime = 0.f;
			m_fKickBombTime = 0.f;
		}
		ChangeMotion();
		CheckPushBlock(DIR_LEFT);
		CheckKickBomb(DIR_LEFT);
		m_tInfo.fX -= m_fSpeed;
	}
	else if (CKeyMgr::GetInstance()->KeyPressing(VK_UP) && m_tRect.top > 40)
	{
		if (m_eCurMotion != HIT)
			m_eCurMotion = UP;
		if (m_eCurMotion != m_ePreMotion)
		{
			m_fBlockMoveTime = 0.f;
			m_fKickBombTime = 0.f;
		}
		ChangeMotion();
		CheckPushBlock(DIR_UP);
		CheckKickBomb(DIR_UP);
		m_tInfo.fY -= m_fSpeed;
	}
	else if (CKeyMgr::GetInstance()->KeyPressing(VK_DOWN) && m_tRect.bottom < 560)
	{
		if (m_eCurMotion != HIT)
			m_eCurMotion = DOWN;
		if (m_eCurMotion != m_ePreMotion)
		{
			m_fBlockMoveTime = 0.f;
			m_fKickBombTime = 0.f;
		}
		ChangeMotion();
		CheckPushBlock(DIR_DOWN);
		CheckKickBomb(DIR_DOWN);
		m_tInfo.fY += m_fSpeed;
	}
	else	//IDEL
	{
		m_fBlockMoveTime = 0.f;
		m_fKickBombTime = 0.f;
		if (m_eCurMotion != HIT && m_eCurMotion != REVIVAL)
			m_eCurMotion = IDLE;
		ChangeMotion();
	}
	if (CKeyMgr::GetInstance()->KeyDown(VK_SPACE))
	{
		if (m_eCurMotion == HIT || m_eCurMotion == DEATH)
			return;
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
	if (CKeyMgr::GetInstance()->KeyDown(VK_CONTROL))
	{
		if (m_iCtrlSlotCnt < 1) return;

		if (m_eCtrlSlot == NEEDLE)
		{
			if (m_eCurMotion == HIT)
			{
				//SOUND_NEDDLE
				CSoundMgr::Get_Instance()->PlaySound(L"Neddle_11.wav", SOUND_NEDDLE, 0.3f);
				--m_iCtrlSlotCnt;
				m_eCurMotion = REVIVAL;
				ChangeMotion();
			}
		}
		else if (m_eCtrlSlot == SHIELD)
		{
			if (m_bShowShieldEffect == true || m_eCurMotion == HIT || m_eCurMotion == DEATH)
				return;
			--m_iCtrlSlotCnt;
			m_bShowShieldEffect = true;
			m_iShieldFrame = 0;
			m_dwShieldEffectFrameCount = GetTickCount64(); 
			m_dwFrameCount = GetTickCount64();
		}
		else if (m_eCtrlSlot == DART)
		{
			if (m_eCurMotion == HIT || m_eCurMotion == DEATH)
				return;
			--m_iCtrlSlotCnt;
			CreateDart();
		}
		else if (m_eCtrlSlot == TRAMPOLINE)
		{
			if (m_eCurMotion == HIT || m_eCurMotion == DEATH)
				return;
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
		CSoundMgr::Get_Instance()->PlaySound(L"PlayerGetBubble.wav", PLAYER_BUBBLE, 0.3f);
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
		CSoundMgr::Get_Instance()->PlaySound(L"PlayerDead_12.wav", PLAYER_DEAD, 0.3f);
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
		m_tFrame.dwSpeed = 130.f;
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
		CSoundMgr::Get_Instance()->PlayBGM(L"Pirate.wav", 0.1f);
		m_eCurMotion = DOWN;
		ChangeMotion();
	}
	else if (m_eCurMotion == HIT 
		&& m_dwFrameCount + m_tFrame.dwSpeed * m_tFrame.iEnd <= GetTickCount64())
	{
		m_eCurMotion = DEATH;
		ChangeMotion();
	}
	else if (m_eCurMotion == DEATH
		&& m_dwFrameCount + m_tFrame.dwSpeed * m_tFrame.iEnd <= GetTickCount64())
	{
		CSoundMgr::Get_Instance()->StopAll();
		CSoundMgr::Get_Instance()->PlaySound(L"Loss_8.wav", STAGE_LOSE, 0.1f);
		m_bDead = DEAD;
	}
	else if (m_eCurMotion == REVIVAL
		&& m_dwFrameCount + m_tFrame.dwSpeed * m_tFrame.iEnd <= GetTickCount64()) //m_tFrame.iStart - 1 >= m_tFrame.iEnd
	{
		m_eCurMotion = DOWN;
		m_pFrameKey = L"player_down";
		ChangeMotion();
	}

	if (m_bShowItemGainEffect == true
		&& m_dwItemEffectFrameCount + 800 <= GetTickCount64())
	{
		m_bShowItemGainEffect = false;
		m_eItemFrameKey = ITEMTYPE_END;
	}
	if (m_bShowShieldEffect == true
		&& m_dwFrameCount + 2500 <= GetTickCount64())
	{
		m_bShowShieldEffect = false;
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
	if (fCheckX<=40 || fCheckX >= 600 || fCheckY <=60 || fCheckY >= 540)
		return;
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

void CPlayer::CheckKickBomb(DIRECTION eDIR)
{
	if (m_bShoe == false)
		return;
	float tempx = 0.f;
	for (auto& pBomb : CObjMgr::GetInstance()->GetList(OBJ_BOMB))
	{
		CBomb* pTempBomb = dynamic_cast<CBomb*>(pBomb);
		if (pTempBomb->GetPlayerCollision() == false)
			continue;
		if (fabsf(m_tInfo.fX - pTempBomb->GetInfo()->fX) <= 36.f
			&& fabsf(m_tInfo.fY - pTempBomb->GetInfo()->fY) <= 36.f)
		{
			m_fKickBombTime += 1.f;

			if (m_fKickBombTime >= 5.f)
			{
				m_fKickBombTime = 0;
				pTempBomb->SetCanMove(true);
				pTempBomb->SetDirection(eDIR);
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
	CSoundMgr::Get_Instance()->PlaySound(L"PutDownbomb1.wav", BOMB_PUTDOWN, 0.3f);
}

void CPlayer::CreateDart()
{
	CObj* pDart = CAbstractFactory<CDart>::Create(m_tInfo.fX, m_tInfo.fY, L"dart_obj");

	if (!lstrcmp(m_pFrameKey, L"player_down"))
		pDart->SetDirection(DIR_DOWN);
	else if (!lstrcmp(m_pFrameKey, L"player_up"))
		pDart->SetDirection(DIR_UP);
	else if (!lstrcmp(m_pFrameKey, L"player_left"))
		pDart->SetDirection(DIR_LEFT);
	else if (!lstrcmp(m_pFrameKey, L"player_right"))
		pDart->SetDirection(DIR_RIGHT);

	CObjMgr::GetInstance()->AddObject(OBJ_DART, pDart);
	CSoundMgr::Get_Instance()->PlaySound(L"dart.wav", SOUND_DART, 0.3f);
}

void CPlayer::ShowItemGainEffect(HDC hDC)
{
	HDC hItem_Effect = nullptr;
	int iItemStat = 0;

	if (m_eItemFrameKey == BUBBLE)
	{
		if (m_iBombMax > 6)
		{
			m_bShowItemGainEffect = false;
			m_iBombMax = 6;
			return;
		}
		else
		{
			hItem_Effect = CBmpMgr::GetInstance()->FindImage(L"UI_Bomb");
			iItemStat = m_iBombMax - 2;
		}
	}
	else if (m_eItemFrameKey == FLUID)
	{
		if (m_iBombRange > 7)
		{
			m_bShowItemGainEffect = false;
			m_iBombRange = 7;
			return;
		}
		else
		{
			hItem_Effect = CBmpMgr::GetInstance()->FindImage(L"UI_Liquid2");
			iItemStat = m_iBombRange - 2;
		}
	}
	else if (m_eItemFrameKey == ROLLER)
	{
		if (m_fWalkSpeed > 7)
		{
			m_bShowItemGainEffect = false;
			m_fWalkSpeed = 7;
			return;
		}
		else
		{
			hItem_Effect = CBmpMgr::GetInstance()->FindImage(L"UI_Skate");
			iItemStat = m_fWalkSpeed - 4;
		}
	}
	else {
		return;
	}
	GdiTransparentBlt(hDC,					// 목적지 DC
		int(m_tInfo.fX - 55),				// 목적지 LEFT, TOP
		int(m_tInfo.fY - (m_tFrame.iCY - m_tInfo.fCY * 0.5) - 31),
		111,								// 목적지 공간의 가로, 세로 사이즈
		30,
		hItem_Effect,						// 원본 이미지 DC
		iItemStat * 111,					// 원본 이미지 LEFT, TOP
		0,
		111,								// 원본 이미지 가로, 세로 사이즈
		30,
		RGB(255, 0, 255));					// 제거할 픽셀 색상
}

void CPlayer::ShowCtrlSlot(HDC hDC)
{
	//L"stage_ctrlItem"
	HDC hItem_Effect = CBmpMgr::GetInstance()->FindImage(L"stage_ctrlItem");
	int iItemType = 0;
	if (m_eCtrlSlot == SHIELD)
		iItemType = 0;
	else if (m_eCtrlSlot == DART)
		iItemType = 1;
	else if (m_eCtrlSlot == NEEDLE)
		iItemType = 2;
	else if (m_eCtrlSlot == TRAMPOLINE)
		iItemType = 3;
	else 
		return;
	GdiTransparentBlt(hDC,					// 목적지 DC
		639,				// 목적지 LEFT, TOP
		450,
		157,								// 목적지 공간의 가로, 세로 사이즈
		105,
		hItem_Effect,						// 원본 이미지 DC
		(m_iCtrlSlotCnt-1) * 157,					// 원본 이미지 LEFT, TOP
		iItemType * 105,
		157,								// 원본 이미지 가로, 세로 사이즈
		105,
		RGB(255, 0, 255));					// 제거할 픽셀 색상
}

void CPlayer::ShowShield(HDC hDC)
{
	HDC hShield = CBmpMgr::GetInstance()->FindImage(L"shieldEffects");
	if (m_dwShieldEffectFrameCount + 100 <= GetTickCount64())
	{
		m_dwShieldEffectFrameCount = GetTickCount64();
		m_iShieldFrame = (m_iShieldFrame + 1) % 10;
	}
	GdiTransparentBlt(hDC,					// 목적지 DC
		int(m_tInfo.fX - (88 / 2) + 3),	// 목적지 LEFT, TOP
		int(m_tInfo.fY - (80 - m_tInfo.fCY * 0.5)),
		88,			// 목적지 공간의 가로, 세로 사이즈
		101,
		hShield,						// 원본 이미지 DC
		m_iShieldFrame * 88,	// 원본 이미지 LEFT, TOP
		0,
		88,			// 원본 이미지 가로, 세로 사이즈
		101,
		RGB(255, 0, 255));		// 제거할 픽셀 색상
}

void CPlayer::PickUpItem(const WCHAR* pItemFrameKey)
{
	if (m_eCurMotion == HIT)
		return;
	//SOUND_ITEMGAIN
	CSoundMgr::Get_Instance()->PlaySound(L"ItemGain_5.wav", SOUND_ITEMGAIN, 0.3f);
	if (!lstrcmp(pItemFrameKey, L"bubble"))
	{
		m_eItemFrameKey = BUBBLE;
		m_bShowItemGainEffect = true;
		m_dwItemEffectFrameCount = GetTickCount64();
		m_iBombMax++;
	}
	else if (!lstrcmp(pItemFrameKey, L"dart"))
	{
		m_eCtrlSlot = DART;
		m_iCtrlSlotCnt = 3;
	}
	else if (!lstrcmp(pItemFrameKey, L"fluid"))
	{
		m_eItemFrameKey = FLUID;
		m_bShowItemGainEffect = true;
		m_dwItemEffectFrameCount = GetTickCount64();
		m_iBombRange++;
	}
	else if (!lstrcmp(pItemFrameKey, L"needle"))
	{
		m_eCtrlSlot = NEEDLE;
		m_iCtrlSlotCnt = 1;
	}
	else if (!lstrcmp(pItemFrameKey, L"roller"))
	{
		m_eItemFrameKey = ROLLER;
		m_bShowItemGainEffect = true;
		m_dwItemEffectFrameCount = GetTickCount64();
		m_fWalkSpeed++;
	}
	else if (!lstrcmp(pItemFrameKey, L"shield"))
	{
		m_eCtrlSlot = SHIELD;
		m_iCtrlSlotCnt = 2;
	}
	else if (!lstrcmp(pItemFrameKey, L"shoe"))
	{
		m_bShoe = true;
	}
	else if (!lstrcmp(pItemFrameKey, L"trampoline"))
	{
		m_eCtrlSlot = TRAMPOLINE;
		m_iCtrlSlotCnt = 3;
	}
}
