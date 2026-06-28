#include "pch.h"
#include "CPlayer2.h"
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
#include "CInven.h"
#include "CSceneMgr.h"
#include "CUI.h"
CPlayer2::CPlayer2() :m_ePreMotion(MOTION_END), m_eCurMotion(START), m_fWalkSpeed(3.f), m_fBubbleSpeed(0.5f), m_dwFrameCount(GetTickCount64()),
m_fBlockMoveTime(0.f), m_iBombRange(1), m_iBombMax(1), m_iBombCnt(0), m_bShowItemGainEffect(false), m_eItemFrameKey(ITEMTYPE_END),
m_dwItemEffectFrameCount(GetTickCount64()), m_iCtrlSlotCnt(0), m_eCtrlSlot(ITEMTYPE_END), m_dwShieldEffectFrameCount(GetTickCount64()), m_pTileVector(nullptr),
m_bRide(false), m_fKartSpeed(6.f), m_fRemainGas(300.f), m_fRespawnTime(2000.f), m_pRespawnPoint(nullptr), m_bBlur(false)
{
	m_iMaxVecSize = 5;
	m_iVecSize = 0;
	m_FrameKeyvector.reserve(m_iMaxVecSize);

	m_bShowShieldEffect = false;
	m_iShieldFrame = 0;

	m_fKickBombTime = 0.f;
#ifdef _DEBUG
	m_bShoe = true;
#elif NDEBUG
	m_bShoe = false;
#endif // _DEBUG
}

CPlayer2::~CPlayer2()
{
	Release();
}

void CPlayer2::Initialize()
{
	m_eRenderID = GAMEOBJECT;

	m_ePlayerID = PLAYER2;

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

	m_pTileVector = CObjMgr::GetInstance()->GetTilePtr();
	m_pRespawnPoint = CAbstractFactory<CUI>::Create(m_tInfo.fX, m_tInfo.fY - 38.5f, L"UI_Respawn");
	m_pRespawnPoint->SetDraw(false);
	CObjMgr::GetInstance()->AddObject(OBJ_UI, m_pRespawnPoint);
}

int CPlayer2::Update()
{
	if (m_bDead == DEAD)
		return DEAD;
	if (m_eCurMotion != DEATH && m_eCurMotion != START && m_eCurMotion != WIN && m_eCurMotion != RESPAWN && m_eCurMotion != LOSE)
		KeyInput();
	CheckFrame();
	MoveFrame();
	if (m_bRide == true)
	{
		if (m_fRemainGas > 200)
		{
			m_fKartSpeed = 6.f;
		}
		else if (m_fRemainGas > 100)
		{
			m_fKartSpeed = 4.f;
		}
		else
		{
			m_fKartSpeed = 2.f;
		}
	}
	//cout << "m_fSpeed : " << m_fSpeed << "\tm_fRemainGas: " << m_fRemainGas << endl;
	return NOEVENT;
}


void CPlayer2::LateUpdate()
{
}

void CPlayer2::Render(HDC hDC)
{
#ifdef _DEBUG
	Rectangle(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);
#endif // _DEBUG
	if (m_bDraw == true)
	{
		if (m_bBlur)
		{
			ShowBlur(hDC);
		}
		else
		{
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

		}
		HDC hArrow = CBmpMgr::GetInstance()->FindImage(L"PlayerArrow2");

		GdiTransparentBlt(hDC,					// 목적지 DC
			int(m_tInfo.fX - 9),	// 목적지 LEFT, TOP
			int(m_tInfo.fY - (m_tFrame.iCY - m_tInfo.fCY * 0.5) - 33),
			18,			// 목적지 공간의 가로, 세로 사이즈
			30,
			hArrow,						// 원본 이미지 DC
			0,	// 원본 이미지 LEFT, TOP
			0,
			18,			// 원본 이미지 가로, 세로 사이즈
			30,
			RGB(255, 0, 255));		// 제거할 픽셀 색상
	}
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

void CPlayer2::Release()
{
}



void CPlayer2::KeyInput()
{
	if (m_eCurMotion == DISMOUNT)
		return;
	float fDeltaGas = 0.2f;
	if (CKeyMgr::GetInstance()->KeyPressing('G') && m_tRect.right < 620)
	{
		if (m_eCurMotion != HIT)
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
		if (m_bRide && m_fRemainGas > 0)
			m_fRemainGas -= fDeltaGas;
	}
	else if (CKeyMgr::GetInstance()->KeyPressing('D') && m_tRect.left > 20)
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
		if (m_bRide && m_fRemainGas > 0)
			m_fRemainGas -= fDeltaGas;
	}
	else if (CKeyMgr::GetInstance()->KeyPressing('R') && m_tRect.top > 40)
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
		if (m_bRide && m_fRemainGas > 0)
			m_fRemainGas -= fDeltaGas;
	}
	else if (CKeyMgr::GetInstance()->KeyPressing('F') && m_tRect.bottom < 560)
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
		if (m_bRide && m_fRemainGas > 0)
			m_fRemainGas -= fDeltaGas;
	}
	else	//IDEL
	{
		m_fBlockMoveTime = 0.f;
		m_fKickBombTime = 0.f;
		if (m_eCurMotion != HIT && m_eCurMotion != REVIVAL && m_eCurMotion != DISMOUNT)
			m_eCurMotion = IDLE;
		ChangeMotion();
	}
	if (CKeyMgr::GetInstance()->KeyDown(VK_LSHIFT))
	{
		if (m_eCurMotion == HIT || m_eCurMotion == DEATH)
			return;
		if (CObjMgr::GetInstance()->GetList(OBJ_BOMB2).size() < m_iBombMax)
		{
			for (auto& pBomb : CObjMgr::GetInstance()->GetList(OBJ_BOMB2))
			{
				if (AdjustPosX(m_tInfo.fX) == pBomb->GetInfo()->fX
					&& AdjustPosY(m_tInfo.fY) == pBomb->GetInfo()->fY)
					return;
			}
			CreateBomb();
		}
	}
	if (CKeyMgr::GetInstance()->KeyDown(VK_LCONTROL))
	{
		if (m_iCtrlSlotCnt < 1) return;

		if (m_eCtrlSlot == NEEDLE)
		{
			if (m_eCurMotion == HIT)
			{
				CSoundMgr::Get_Instance()->PlaySound(L"Neddle_11.wav", SOUND_NEDDLE, 0.2f);
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
			CSoundMgr::Get_Instance()->PlaySound(L"Shield.wav", SOUND_NEDDLE, 0.8f);
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
	if (CKeyMgr::GetInstance()->KeyDown('1'))
	{
		switch (CInven::GetInstance()->GetItemSlot()[0]->GetFrame().iStart)
		{
		case 1:
			if (m_eCurMotion == HIT && CInven::GetInstance()->GetInven().iNeedleCnt > 0)
			{
				CSoundMgr::Get_Instance()->PlaySound(L"Neddle_11.wav", SOUND_NEDDLE, 0.2f);
				CInven::GetInstance()->SetNeedleCnt(-1);
				m_eCurMotion = REVIVAL;
				ChangeMotion();
			}
			break;
		case 2:
			if (m_eCurMotion == HIT || m_eCurMotion == DEATH)
				return;
			if (CInven::GetInstance()->GetInven().iDartCnt > 0)
			{
				CreateDart();
				CInven::GetInstance()->SetDartCnt(-1);
			}
			break;
		case 3:
			if (m_bShowShieldEffect == true || m_eCurMotion == HIT || m_eCurMotion == DEATH)
				return;
			if (CInven::GetInstance()->GetInven().iShieldCnt > 0)
			{
				CSoundMgr::Get_Instance()->PlaySound(L"Shield.wav", SOUND_NEDDLE, 0.8f);
				m_bShowShieldEffect = true;
				m_iShieldFrame = 0;
				m_dwShieldEffectFrameCount = GetTickCount64();
				m_dwFrameCount = GetTickCount64();
				CInven::GetInstance()->SetShieldCnt(-1);
			}
			break;
		default:
			break;
		}
	}
	if (CKeyMgr::GetInstance()->KeyDown('2'))
	{
		switch (CInven::GetInstance()->GetItemSlot()[1]->GetFrame().iStart)
		{
		case 1:
			if (m_eCurMotion == HIT && CInven::GetInstance()->GetInven().iNeedleCnt > 0)
			{
				CSoundMgr::Get_Instance()->PlaySound(L"Neddle_11.wav", SOUND_NEDDLE, 0.8f);
				CInven::GetInstance()->SetNeedleCnt(-1);
				m_eCurMotion = REVIVAL;
				ChangeMotion();
			}
			break;
		case 2:
			if (m_eCurMotion == HIT || m_eCurMotion == DEATH)
				return;
			if (CInven::GetInstance()->GetInven().iDartCnt > 0)
			{
				CreateDart();
				CInven::GetInstance()->SetDartCnt(-1);
			}
			break;
		case 3:
			if (m_bShowShieldEffect == true || m_eCurMotion == HIT || m_eCurMotion == DEATH)
				return;
			if (CInven::GetInstance()->GetInven().iShieldCnt > 0)
			{
				CSoundMgr::Get_Instance()->PlaySound(L"Shield.wav", SOUND_NEDDLE, 0.8f);
				m_bShowShieldEffect = true;
				m_iShieldFrame = 0;
				m_dwShieldEffectFrameCount = GetTickCount64();
				m_dwFrameCount = GetTickCount64();
				CInven::GetInstance()->SetShieldCnt(-1);
			}
			break;
		default:
			break;
		}
	}
	if (CKeyMgr::GetInstance()->KeyDown('3'))
	{
		switch (CInven::GetInstance()->GetItemSlot()[2]->GetFrame().iStart)
		{
		case 1:
			if (m_eCurMotion == HIT && CInven::GetInstance()->GetInven().iNeedleCnt > 0)
			{
				CSoundMgr::Get_Instance()->PlaySound(L"Neddle_11.wav", SOUND_NEDDLE, 0.2f);
				CInven::GetInstance()->SetNeedleCnt(-1);
				m_eCurMotion = REVIVAL;
				ChangeMotion();
			}
			break;
		case 2:
			if (m_eCurMotion == HIT || m_eCurMotion == DEATH)
				return;
			if (CInven::GetInstance()->GetInven().iDartCnt > 0)
			{
				CreateDart();
				CInven::GetInstance()->SetDartCnt(-1);
			}
			break;
		case 3:
			if (m_bShowShieldEffect == true || m_eCurMotion == HIT || m_eCurMotion == DEATH)
				return;

			if (CInven::GetInstance()->GetInven().iShieldCnt > 0)
			{
				CSoundMgr::Get_Instance()->PlaySound(L"Shield.wav", SOUND_NEDDLE, 0.8f);
				m_bShowShieldEffect = true;
				m_iShieldFrame = 0;
				m_dwShieldEffectFrameCount = GetTickCount64();
				m_dwFrameCount = GetTickCount64();
				CInven::GetInstance()->SetShieldCnt(-1);
			}
			break;
		default:
			break;
		}
	}
	if (CKeyMgr::GetInstance()->KeyDown('4'))
	{
		switch (CInven::GetInstance()->GetItemSlot()[3]->GetFrame().iStart)
		{
		case 1:
			if (m_eCurMotion == HIT && CInven::GetInstance()->GetInven().iNeedleCnt > 0)
			{
				CSoundMgr::Get_Instance()->PlaySound(L"Neddle_11.wav", SOUND_NEDDLE, 0.2f);
				CInven::GetInstance()->SetNeedleCnt(-1);
				m_eCurMotion = REVIVAL;
				ChangeMotion();
			}
			break;
		case 2:
			if (m_eCurMotion == HIT || m_eCurMotion == DEATH)
				return;
			if (CInven::GetInstance()->GetInven().iDartCnt > 0)
			{
				CreateDart();
				CInven::GetInstance()->SetDartCnt(-1);
			}
			break;
		case 3:
			if (m_bShowShieldEffect == true || m_eCurMotion == HIT || m_eCurMotion == DEATH)
				return;
			if (CInven::GetInstance()->GetInven().iShieldCnt > 0)
			{
				CSoundMgr::Get_Instance()->PlaySound(L"Shield.wav", SOUND_NEDDLE, 0.8f);
				m_bShowShieldEffect = true;
				m_iShieldFrame = 0;
				m_dwShieldEffectFrameCount = GetTickCount64();
				m_dwFrameCount = GetTickCount64();
				CInven::GetInstance()->SetShieldCnt(-1);
			}
			break;
		default:
			break;
		}
	}
}

void CPlayer2::ChangeMotion()
{
	if (m_ePreMotion == m_eCurMotion)
		return;
	switch (m_eCurMotion)
	{
	case START:
		m_pRespawnPoint->SetDraw(false);
		m_fSpeed = 0;
		m_pFrameKey = L"player_start2";
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 18;
		m_tFrame.iMotion = 0;
		m_tFrame.bLoop = false;
		m_tFrame.iCX = PLAYER_CX;
		m_tFrame.iCY = 67;
		m_tFrame.dwSpeed = 50.f;
		m_tFrame.dwTime = GetTickCount64();
		m_dwFrameCount = GetTickCount64();
		break;

	case IDLE:
		if (m_bRide == false)
		{
			m_fSpeed = m_fWalkSpeed;
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 1;
			m_tFrame.iMotion = 0;
			m_tFrame.bLoop = false;
			m_tFrame.iCX = PLAYER_CX;
			m_tFrame.iCY = PLAYER_CY;
			m_tFrame.dwSpeed = 100.f;
			m_tFrame.dwTime = GetTickCount64();
		}
		else
		{
			m_fSpeed = m_fKartSpeed;
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 1;
			m_tFrame.iMotion = 0;
			m_tFrame.bLoop = false;
			m_tFrame.dwSpeed = 100.f;
			m_tFrame.dwTime = GetTickCount64();
		}
		break;
	case LEFT:
		if (m_bRide == false)
		{
			m_fSpeed = m_fWalkSpeed;
			m_pFrameKey = L"player_left2";
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 6;
			m_tFrame.iMotion = 0;
			m_tFrame.bLoop = true;
			m_tFrame.iCX = PLAYER_CX;
			m_tFrame.iCY = PLAYER_CY;
			m_tFrame.dwSpeed = 100.f;
			m_tFrame.dwTime = GetTickCount64();
		}
		else
		{
			m_fSpeed = m_fKartSpeed;
			m_pFrameKey = L"kart_left";
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 4;
			m_tFrame.iMotion = 0;
			m_tFrame.bLoop = true;
			m_tFrame.iCX = 47;
			m_tFrame.iCY = 80;
			m_tFrame.dwSpeed = 100.f;
			m_tFrame.dwTime = GetTickCount64();
		}
		break;
	case RIGHT:
		if (m_bRide == false)
		{
			m_fSpeed = m_fWalkSpeed;
			m_pFrameKey = L"player_right2";
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 6;
			m_tFrame.iMotion = 0;
			m_tFrame.bLoop = true;
			m_tFrame.iCX = PLAYER_CX;
			m_tFrame.iCY = PLAYER_CY;
			m_tFrame.dwSpeed = 100.f;
			m_tFrame.dwTime = GetTickCount64();
		}
		else
		{
			m_fSpeed = m_fKartSpeed;
			m_pFrameKey = L"kart_right";
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 4;
			m_tFrame.iMotion = 0;
			m_tFrame.bLoop = true;
			m_tFrame.iCX = 47;
			m_tFrame.iCY = 80;
			m_tFrame.dwSpeed = 100.f;
			m_tFrame.dwTime = GetTickCount64();
		}
		break;
	case UP:
		if (m_bRide == false)
		{
			m_fSpeed = m_fWalkSpeed;
			m_pFrameKey = L"player_up2";
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 8;
			m_tFrame.iMotion = 0;
			m_tFrame.bLoop = true;
			m_tFrame.iCX = PLAYER_CX;
			m_tFrame.iCY = PLAYER_CY;
			m_tFrame.dwSpeed = 100.f;
			m_tFrame.dwTime = GetTickCount64();
		}
		else
		{
			m_fSpeed = m_fKartSpeed;
			m_pFrameKey = L"kart_up";
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 4;
			m_tFrame.iMotion = 0;
			m_tFrame.bLoop = true;
			m_tFrame.iCX = 44;
			m_tFrame.iCY = 80;
			m_tFrame.dwSpeed = 100.f;
			m_tFrame.dwTime = GetTickCount64();
		}
		break;
	case DOWN:

		if (m_bRide == false)
		{
			m_fSpeed = m_fWalkSpeed;
			m_pFrameKey = L"player_down2";
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 8;
			m_tFrame.iMotion = 0;
			m_tFrame.bLoop = true;
			m_tFrame.iCX = PLAYER_CX;
			m_tFrame.iCY = PLAYER_CY;
			m_tFrame.dwSpeed = 100.f;
			m_tFrame.dwTime = GetTickCount64();
		}
		else
		{
			m_fSpeed = m_fKartSpeed;
			m_pFrameKey = L"kart_down";
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 4;
			m_tFrame.iMotion = 0;
			m_tFrame.bLoop = true;
			m_tFrame.iCX = 44;
			m_tFrame.iCY = 80;
			m_tFrame.dwSpeed = 100.f;
			m_tFrame.dwTime = GetTickCount64();
		}
		break;
	case DISMOUNT:
		m_fSpeed = 0;
		m_pFrameKey = L"kart_dismount";
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 12;
		m_tFrame.iMotion = 0;
		m_tFrame.bLoop = false;
		m_tFrame.iCX = 44;
		m_tFrame.iCY = 113;
		m_tFrame.dwSpeed = 100.f;
		m_tFrame.dwTime = GetTickCount64();
		m_dwFrameCount = GetTickCount64();
		break;
	case HIT:
		CSoundMgr::Get_Instance()->PlaySound(L"PlayerGetBubble.wav", PLAYER_BUBBLE, 0.2f);
		m_fSpeed = m_fBubbleSpeed;
		m_pFrameKey = L"player_hit2";
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
	case RESPAWN:
		m_pRespawnPoint->SetDraw(true);
		cout << "Player2RespawnCheckMotion" << endl;
		m_fSpeed = 0;
		m_dwFrameCount = GetTickCount64();
		m_bDraw = false;
		break;
	case DEATH:
		CSoundMgr::Get_Instance()->PlaySound(L"PlayerDead_12.wav", PLAYER_DEAD, 0.2f);
		m_fSpeed = 0;
		m_pFrameKey = L"player_death2";
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
	case WIN:
		m_fSpeed = 0;
		m_pFrameKey = L"player_win2";
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 8;
		m_tFrame.iMotion = 0;
		m_tFrame.bLoop = true;
		m_tFrame.iCX = 64;
		m_tFrame.iCY = 80;
		m_tFrame.dwSpeed = 130.f;
		m_tFrame.dwTime = GetTickCount64();
		break;
	case LOSE:
		m_pFrameKey = L"player_down2";
		m_fSpeed = 0;
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 1;
		m_tFrame.iMotion = 0;
		m_tFrame.bLoop = false;
		m_tFrame.dwSpeed = 100.f;
		m_tFrame.dwTime = GetTickCount64();

		break;
	case MOTION_END:
		break;
	default:
		break;
	}
	m_ePreMotion = m_eCurMotion;
}

void CPlayer2::CheckFrame()
{
	if (m_eCurMotion == START
		&& m_dwFrameCount + m_tFrame.dwSpeed * m_tFrame.iEnd <= GetTickCount64())
	{
		m_eCurMotion = DOWN;
		ChangeMotion();
	}
	else if (m_eCurMotion == HIT
		&& m_dwFrameCount + m_tFrame.dwSpeed * m_tFrame.iEnd <= GetTickCount64())
	{
		m_eCurMotion = DEATH;
		ChangeMotion();
	}
	else if (m_eCurMotion == DISMOUNT
		&& m_dwFrameCount + m_tFrame.dwSpeed * m_tFrame.iEnd <= GetTickCount64())
	{
		m_eCurMotion = DOWN;
		m_bRide = false;
		ChangeMotion();
	}
	else if (m_eCurMotion == DEATH
		&& m_dwFrameCount + m_tFrame.dwSpeed * m_tFrame.iEnd <= GetTickCount64())
	{
		switch (CSceneMgr::GetInstance()->GetCurScene())
		{
		case SC_STAGE1:
		case SC_STAGE2:
		case SC_STAGE3:
			m_bDead = DEAD;
			break;
		case SC_STAGE4:
		case SC_STAGE5:
			m_eCurMotion = RESPAWN;
			break;
		default:
			break;
		}
		ChangeMotion();
	}
	else if (m_eCurMotion == RESPAWN
		&& m_dwFrameCount + m_fRespawnTime <= GetTickCount64())
	{
		m_eCurMotion = START;
		m_bDraw = true;

		int iPlayer2_StartX = 0;
		int iPlayer2_StartY = 0;
		switch (CSceneMgr::GetInstance()->GetCurScene())
		{
		case SC_STAGE4:
			iPlayer2_StartX = 4;
			iPlayer2_StartY = 9; 
			break;
		case SC_STAGE5:
			iPlayer2_StartX = 4;
			iPlayer2_StartY = 8; 
			break;
		default:
			break;
		}
		m_tInfo.fX = (iPlayer2_StartX * 40) + 40;
		m_tInfo.fY = (iPlayer2_StartY * 40) + 60;
		ChangeMotion();
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
	if (m_bBlur == true
		&& m_dwFrameCount + 30000 <= GetTickCount64())
	{
		m_fSpeed = m_fWalkSpeed;
		m_bBlur = false;
	}
}

void CPlayer2::CheckPushBlock(DIRECTION eDIR)
{
	float fCheckX = AdjustPosX(m_tInfo.fX);
	float fCheckY = AdjustPosY(m_tInfo.fY);
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
	if (fCheckX <= 40 || fCheckX >= 600 || fCheckY <= 60 || fCheckY >= 540)
		return;

	//int x = (fCheckX - MAP_LEFT) / TILECX;
	//int y = (fCheckY - MAP_TOP) / TILECX;
	//
	//int iIndex = y * MAP_CNT_X + x;
	//CTile* pTempTile = dynamic_cast<CTile*>((*m_pTileVector)[iIndex]);
	//if (pTempTile->GetFrame().iStart == 2 && pTempTile->GetMove() == false)
	//{
	//	m_fBlockMoveTime += 1.f;
	//
	//	if (m_fBlockMoveTime >= 50.f)
	//	{
	//		m_fBlockMoveTime = 0;
	//		pTempTile->SetMove(eDIR);
	//	}
	//}

	for (auto& pTile : *m_pTileVector)
	{
		CTile* pTempTile = dynamic_cast<CTile*>(pTile);
		if (pTempTile->GetFrame().iStart == 2)
		{
			if (fabsf(fCheckX - pTempTile->GetInfo()->fX) <= 20.f
				&& fabsf(fCheckY - pTempTile->GetInfo()->fY) <= 20.f)
			{
				m_fBlockMoveTime += 1.f;

				if (m_fBlockMoveTime >= 22.f)
				{
					m_fBlockMoveTime = 0;
					pTempTile->SetMove(eDIR);
				}
			}
		}
	}
}

void CPlayer2::CheckKickBomb(DIRECTION eDIR)
{
	if (m_bShoe == false)
		return;
	//float tempx = 0.f;
	float fCheckX = AdjustPosX(m_tInfo.fX);
	float fCheckY = AdjustPosY(m_tInfo.fY);
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
	for (auto& pBomb : CObjMgr::GetInstance()->GetList(OBJ_BOMB2))
	{
		CBomb* pTempBomb = dynamic_cast<CBomb*>(pBomb);
		if (pTempBomb->GetPlayerCollision() == false)
			continue;
		if (fabsf(fCheckX - pTempBomb->GetInfo()->fX) <= 35.f
			&& fabsf(fCheckY - pTempBomb->GetInfo()->fY) <= 35.f)
		{
			m_fKickBombTime += 1.f;

			if (m_fKickBombTime >= 15.f)
			{
				cout << m_fKickBombTime << endl;
				m_fKickBombTime = 0;
				pTempBomb->SetCanMove(true);
				pTempBomb->SetDirection(eDIR);
			}
		}
	}
}
void CPlayer2::SetHit()
{
	if (m_bRide == false)
	{
		m_eCurMotion = HIT;
		ChangeMotion();
	}
	else if (m_bRide == true)
	{
		m_eCurMotion = DISMOUNT;
		ChangeMotion();
	}
}
void CPlayer2::CreateBomb()
{
	if (m_bDraw == false)
		return;
	float fX = AdjustPosX(m_tInfo.fX);
	float fY = AdjustPosY(m_tInfo.fY);
	CObj* pBomb = CAbstractFactory<CBomb>::Create(fX, fY, L"BlueBubble");
	pBomb->SetCanMove(false);
	pBomb->SetPlayerID(PLAYER2);
	dynamic_cast<CBomb*>(pBomb)->SetBombRange(m_iBombRange);
	CObjMgr::GetInstance()->AddObject(OBJ_BOMB2, pBomb);
	CSoundMgr::Get_Instance()->PlaySound(L"PutDownbomb1.wav", BOMB_PUTDOWN, 0.3f);
}

void CPlayer2::CreateDart()
{
	CObj* pDart = CAbstractFactory<CDart>::Create(m_tInfo.fX, m_tInfo.fY, L"dart_obj");

	if (!lstrcmp(m_pFrameKey, L"player_down2"))
		pDart->SetDirection(DIR_DOWN);
	else if (!lstrcmp(m_pFrameKey, L"player_up2"))
		pDart->SetDirection(DIR_UP);
	else if (!lstrcmp(m_pFrameKey, L"player_left2"))
		pDart->SetDirection(DIR_LEFT);
	else if (!lstrcmp(m_pFrameKey, L"player_right2"))
		pDart->SetDirection(DIR_RIGHT);

	cout << "CreateDart" << endl;
	CObjMgr::GetInstance()->AddObject(OBJ_DART, pDart);
	CSoundMgr::Get_Instance()->PlaySound(L"dart.wav", SOUND_DART, 0.3f);
}

void CPlayer2::ShowItemGainEffect(HDC hDC)
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

void CPlayer2::ShowCtrlSlot(HDC hDC)
{
	HDC hItem_Effect = CBmpMgr::GetInstance()->FindImage(L"stage_ctrlItemP1");
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
	BitBlt(hDC,					// 목적지 DC
		653,				// 목적지 LEFT, TOP
		468,
		63,								// 목적지 공간의 가로, 세로 사이즈
		81,
		hItem_Effect,						// 원본 이미지 DC
		(m_iCtrlSlotCnt - 1) * 63,					// 원본 이미지 LEFT, TOP
		iItemType * 81,
		SRCCOPY);					// 제거할 픽셀 색상
}

void CPlayer2::ShowShield(HDC hDC)
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
void CPlayer2::ShowBlur(HDC hDC)
{
	if (m_iVecSize < 4)
	{
		++m_iVecSize;
	}
	else
	{
		m_PosVector.erase(m_PosVector.begin());
		m_FrameKeyvector.erase(m_FrameKeyvector.begin());
	}
	m_PosVector.push_back({ m_tInfo.fX,m_tInfo.fY });
	m_FrameKeyvector.push_back(m_pFrameKey);
	float fAlpha = 0.2f;
	for (int i = 0; i < m_iVecSize; ++i)
	{
		Graphics* _pGraphics = Graphics::FromHDC(hDC);
		Gdiplus::Image* hBlur = CImgMgr::GetInstance()->FindImg(m_FrameKeyvector[i]);

		Rect rect = {
			int(m_PosVector[i].first - (m_tFrame.iCX / 2)),
			int(m_PosVector[i].second - (m_tFrame.iCY - m_tInfo.fCY * 0.5)),
			m_tFrame.iCX,
			m_tFrame.iCY,
		};

		ImageAttributes attr;
		attr.SetColorKey(
			Color(255, 0, 255),
			Color(255, 0, 255));

		MakeAlphaAttr(attr, fAlpha);

		_pGraphics->DrawImage(hBlur, rect,
			m_tFrame.iCX * m_tFrame.iStart, 0,
			m_tFrame.iCX,
			m_tFrame.iCY,
			UnitPixel,
			&attr);
		fAlpha += 0.2;
	}
}
void CPlayer2::PickUpItem(const WCHAR* pItemFrameKey)
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
	else if (!lstrcmp(pItemFrameKey, L"joystick"))
	{
		m_ePreMotion = MOTION_END;
		m_bRide = true;
		m_fRemainGas = 300.f;
		ChangeMotion();
	}
	else if (!lstrcmp(pItemFrameKey, L"blur"))
	{
		m_bBlur = true;
		m_dwFrameCount = GetTickCount64();
		m_fSpeed = 7.f;
	}
	else if (!lstrcmp(pItemFrameKey, L"trampoline"))
	{
		m_eCtrlSlot = TRAMPOLINE;
		m_iCtrlSlotCnt = 3;
	}
}
