#include "pch.h"
#include "CButton.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CImgMgr.h"
#include "CObjMgr.h"
#include "CBmpMgr.h"
#include "CSoundMgr.h"
#include "CInven.h"
#include "CNotice.h"
#include "CSelectPlayer.h"
#include "CInven2.h"

CButton::CButton():m_bCurState(false), m_bPreState(false)
{
}

CButton::~CButton()
{
	Release();
}

void CButton::Initialize()
{
	m_eRenderID = UI;
	if (!lstrcmp(L"button_edit", m_pFrameKey))
	{
		m_tInfo.fCX = 34.f;
		m_tInfo.fCY = 34.f;
		m_tFrame.iCX = int(m_tInfo.fCX);
		m_tFrame.iCY = int(m_tInfo.fCY);
		m_tFrame.iEnd = TILE_END;
	}
	else if (!lstrcmp(L"Login_2P", m_pFrameKey))
	{
		m_tInfo.fCX = 95.f;
		m_tInfo.fCY = 116.f;
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 2;
		m_tFrame.iMotion = 0;
		m_tFrame.bLoop = false;
		m_tFrame.iCX = int(m_tInfo.fCX);
		m_tFrame.iCY = int(m_tInfo.fCY);
	}
	else if (!lstrcmp(L"button_SelectPlayer1", m_pFrameKey) || !lstrcmp(L"button_SelectPlayer2", m_pFrameKey))
	{
		m_tInfo.fCX = 81.f;
		m_tInfo.fCY = 21.f;
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 2;
		m_tFrame.iMotion = 0;
		m_tFrame.bLoop = false;
		m_tFrame.iCX = int(m_tInfo.fCX);
		m_tFrame.iCY = int(m_tInfo.fCY);
	}
	else if (!lstrcmp(L"button_ExitSelectPlayer", m_pFrameKey))
	{
		m_tInfo.fCX = 102.f;
		m_tInfo.fCY = 30.f;
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 2;
		m_tFrame.iMotion = 0;
		m_tFrame.bLoop = false;
		m_tFrame.iCX = int(m_tInfo.fCX);
		m_tFrame.iCY = int(m_tInfo.fCY);
	}
	else if (!lstrcmp(L"Login_1P", m_pFrameKey))
	{
		m_tInfo.fCX = 95.f;
		m_tInfo.fCY = 118.f;
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 2;
		m_tFrame.iMotion = 0;
		m_tFrame.bLoop = false;
		m_tFrame.iCX = int(m_tInfo.fCX);
		m_tFrame.iCY = int(m_tInfo.fCY);
	}
	else if (!lstrcmp(L"button_exit", m_pFrameKey))
	{
		m_tInfo.fCX = 30.f;
		m_tInfo.fCY = 24.f;
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 2;
		m_tFrame.iMotion = 0;
		m_tFrame.bLoop = false;
		m_tFrame.iCX = int(m_tInfo.fCX);
		m_tFrame.iCY = int(m_tInfo.fCY);
	}
	else if (!lstrcmp(L"button_ExitGame", m_pFrameKey))
	{
		m_tInfo.fCX = 102.f;
		m_tInfo.fCY = 30.f;
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 2;
		m_tFrame.iMotion = 0;
		m_tFrame.bLoop = false;
		m_tFrame.iCX = int(m_tInfo.fCX);
		m_tFrame.iCY = int(m_tInfo.fCY);
	}
	else if (!lstrcmp(L"button_ExitNotice", m_pFrameKey))
	{
		m_tInfo.fCX = 23.f;
		m_tInfo.fCY = 20.f;
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 2;
		m_tFrame.iMotion = 0;
		m_tFrame.bLoop = false;
		m_tFrame.iCX = int(m_tInfo.fCX);
		m_tFrame.iCY = int(m_tInfo.fCY);
	}
	else if (!lstrcmp(L"button_ReLogin", m_pFrameKey))
	{
		m_tInfo.fCX = 102.f;
		m_tInfo.fCY = 30.f;
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 2;
		m_tFrame.iMotion = 0;
		m_tFrame.bLoop = false;
		m_tFrame.iCX = int(m_tInfo.fCX);
		m_tFrame.iCY = int(m_tInfo.fCY);
	}
	else if (!lstrcmp(L"button_myPage", m_pFrameKey))
	{
		m_tInfo.fCX = 65.f;
		m_tInfo.fCY = 22.f;
		m_tFrame.iCX = int(m_tInfo.fCX);
		m_tFrame.iCY = int(m_tInfo.fCY);
	}
	else if (!lstrcmp(L"button_back", m_pFrameKey))
	{
		m_tInfo.fCX = 29.f;
		m_tInfo.fCY = 21.f;
		m_tFrame.iCX = int(m_tInfo.fCX);
		m_tFrame.iCY = int(m_tInfo.fCY);
	}
	else if (!lstrcmp(L"button_buy0", m_pFrameKey)
		|| !lstrcmp(L"button_buy1", m_pFrameKey)
		|| !lstrcmp(L"button_buy2", m_pFrameKey)
		|| !lstrcmp(L"button_buy3", m_pFrameKey))
	{
		m_tInfo.fCX = 41.f;
		m_tInfo.fCY = 19.f;
		m_tFrame.iCX = int(m_tInfo.fCX);
		m_tFrame.iCY = int(m_tInfo.fCY);
	}
	else if (!lstrcmp(L"Slot1", m_pFrameKey))
	{
		m_tInfo.fCX = 33.f;
		m_tInfo.fCY = 31.f;
		m_tRect = { 569,175,602,206 };
		m_tFrame.iCX = int(m_tInfo.fCX);
		m_tFrame.iCY = int(m_tInfo.fCY);
	}
	else if (!lstrcmp(L"Slot2", m_pFrameKey))
	{
		m_tInfo.fCX = 33.f;
		m_tInfo.fCY = 31.f;
		m_tRect = { 489,235,522,266 };
		m_tFrame.iCX = int(m_tInfo.fCX);
		m_tFrame.iCY = int(m_tInfo.fCY);
	}
	else if (!lstrcmp(L"Slot3", m_pFrameKey))
	{
		m_tInfo.fCX = 33.f;
		m_tInfo.fCY = 31.f;
		m_tRect = { 569,295,602,326 };
		m_tFrame.iCX = int(m_tInfo.fCX);
		m_tFrame.iCY = int(m_tInfo.fCY);
	}
	else if (!lstrcmp(L"Slot4", m_pFrameKey))
	{
		m_tInfo.fCX = 33.f;
		m_tInfo.fCY = 31.f;
		m_tRect = { 649,235,682,266 };
		m_tFrame.iCX = int(m_tInfo.fCX);
		m_tFrame.iCY = int(m_tInfo.fCY);
	}
	else if (!lstrcmp(L"InvenItem", m_pFrameKey))
	{
		m_tInfo.fCX = 33.f;
		m_tInfo.fCY = 31.f;
		m_tRect = { LONG(m_tInfo.fX - 16.5f) ,
					LONG(m_tInfo.fY - 15.5f),
					LONG(m_tInfo.fX + 16.5f) ,
					LONG(m_tInfo.fY - 15.5f) };
		m_tFrame.iCX = int(m_tInfo.fCX);
		m_tFrame.iCY = int(m_tInfo.fCY);
	}
	else if (!lstrcmp(L"button_shop", m_pFrameKey))
	{
		m_tInfo.fCX = 61.f;
		m_tInfo.fCY = 22.f;
		m_tFrame.iCX = int(m_tInfo.fCX);
		m_tFrame.iCY = int(m_tInfo.fCY);
	}
	else if (!lstrcmp(L"button_InvenExit", m_pFrameKey))
	{
		m_tInfo.fCX = 137.f;
		m_tInfo.fCY = 31.f;
		m_tRect = {238,505,369,536};
		m_tFrame.iCX = int(m_tInfo.fCX);
		m_tFrame.iCY = int(m_tInfo.fCY);
	}
	else if (!lstrcmp(L"button_creator", m_pFrameKey))
	{
		m_tInfo.fCX = 124;
		m_tInfo.fCY = 48;

		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 4;
		m_tFrame.iMotion = 0;
		m_tFrame.bLoop = true;
		m_tFrame.iCX = int(m_tInfo.fCX);
		m_tFrame.iCY = int(m_tInfo.fCY);
		m_tFrame.dwSpeed = ULONGLONG(100);
		m_tFrame.dwTime = GetTickCount64();
	}
	else if (!lstrcmp(L"button_exitEdit", m_pFrameKey))
	{
		m_tInfo.fCX = 24;
		m_tInfo.fCY = 20;

		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 2;
		m_tFrame.iMotion = 0;
		m_tFrame.bLoop = true;
		m_tFrame.iCX = int(m_tInfo.fCX);
		m_tFrame.iCY = int(m_tInfo.fCY);
		m_tFrame.dwSpeed = ULONGLONG(100.f);
		m_tFrame.dwTime = GetTickCount64();
	}
	else if (!lstrcmp(L"button_stageStart", m_pFrameKey))
	{
		m_tInfo.fCX = 188;
		m_tInfo.fCY = 54;

		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 5;
		m_tFrame.iMotion = 0;
		m_tFrame.bLoop = true;
		m_tFrame.iCX = int(m_tInfo.fCX);
		m_tFrame.iCY = int(m_tInfo.fCY);
		m_tFrame.dwSpeed = ULONGLONG(100.f);
		m_tFrame.dwTime = GetTickCount64();
	}
	else if (!lstrcmp(L"button_stageExit", m_pFrameKey))
	{
		m_tInfo.fCX = 143;
		m_tInfo.fCY = 33;

		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 2;
		m_tFrame.iMotion = 0;
		m_tFrame.bLoop = true;
		m_tFrame.iCX = int(m_tInfo.fCX);
		m_tFrame.iCY = int(m_tInfo.fCY);
		m_tFrame.dwSpeed = ULONGLONG(100.f);
		m_tFrame.dwTime = GetTickCount64();
	}
	else if (!lstrcmp(L"button_FirstStage", m_pFrameKey))
	{
		m_tInfo.fCX = 141;
		m_tInfo.fCY = 128;

		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 2;
		m_tFrame.iMotion = 0;
		m_tFrame.bLoop = false;
		m_tFrame.iCX = int(m_tInfo.fCX);
		m_tFrame.iCY = int(m_tInfo.fCY);
		m_tFrame.dwSpeed = ULONGLONG(100.f);
		m_tFrame.dwTime = GetTickCount64();
	}
	else if (!lstrcmp(L"button_SecondStage", m_pFrameKey))
	{
		m_tInfo.fCX = 141;
		m_tInfo.fCY = 128;

		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 2;
		m_tFrame.iMotion = 0;
		m_tFrame.bLoop = false;
		m_tFrame.iCX = int(m_tInfo.fCX);
		m_tFrame.iCY = int(m_tInfo.fCY);
		m_tFrame.dwSpeed = ULONGLONG(100.f);
		m_tFrame.dwTime = GetTickCount64();
	}

	else if (!lstrcmp(L"button_ThirdStage", m_pFrameKey))
	{
		m_tInfo.fCX = 141;
		m_tInfo.fCY = 128;

		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 2;
		m_tFrame.iMotion = 0;
		m_tFrame.bLoop = false;
		m_tFrame.iCX = int(m_tInfo.fCX);
		m_tFrame.iCY = int(m_tInfo.fCY);
		m_tFrame.dwSpeed = ULONGLONG(100.f);
		m_tFrame.dwTime = GetTickCount64();
		}
	else if (!lstrcmp(L"button_save", m_pFrameKey))
	{
		m_tInfo.fCX = 162;
		m_tInfo.fCY = 38;

		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 2;
		m_tFrame.iMotion = 0;
		m_tFrame.bLoop = true;
		m_tFrame.iCX = int(m_tInfo.fCX);
		m_tFrame.iCY = int(m_tInfo.fCY);
		m_tFrame.dwSpeed = ULONGLONG(100.f);
		m_tFrame.dwTime = GetTickCount64();
	}
}

int CButton::Update()
{
	if (CInven::GetInstance()->GetDraw() == true 
		|| CInven2::GetInstance()->GetDraw() == true
		|| CNotice::GetInstance()->GetDraw() == true 
		|| CSelectPlayer::GetInstance()->GetDraw() == true)
		return 0;
	POINT		ptMouse{};
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);

	m_bPreState = m_bCurState;
	if (PtInRect(&m_tRect, ptMouse))
	{
		if (lstrcmp(L"button_edit", m_pFrameKey))
		{
			m_bCurState = true;

			if (m_tFrame.iEnd > 2)
				MoveFrame();
			else
				m_tFrame.iStart = 1;
		}
		if (CKeyMgr::GetInstance()->KeyDown(VK_LBUTTON))
		{
			CSoundMgr::Get_Instance()->PlaySound(L"buttonClick_2.wav", BUTTON_CLICK, 0.3f);

			if (!lstrcmp(L"button_creator", m_pFrameKey))
			{
				CSceneMgr::GetInstance()->SceneChangeReserve(SC_EDIT);
			}
			else if (!lstrcmp(L"button_buy0", m_pFrameKey))
			{
				if (CSelectPlayer::GetInstance()->GetSelectPlayerID() == PLAYER1)
				{
					if (CInven::GetInstance()->GetGold() - 2750 > 0)
					{
						CInven::GetInstance()->SetGold(-2750);
						CInven::GetInstance()->AddItemToStorage(IT_NEEDLE);
					}
				}
				else
				{
					if (CInven2::GetInstance()->GetGold() - 2750 > 0)
					{
						CInven2::GetInstance()->SetGold(-2750);
						CInven2::GetInstance()->AddItemToStorage(IT_NEEDLE);
					}
				}
			}
			else if (!lstrcmp(L"button_buy1", m_pFrameKey))
			{
				if (CSelectPlayer::GetInstance()->GetSelectPlayerID() == PLAYER1)
				{
					if (CInven::GetInstance()->GetGold() - 1650 > 0)
					{
						CInven::GetInstance()->SetGold(-1650);
						CInven::GetInstance()->AddItemToStorage(IT_DART);
					}
				}
				else
				{
					if (CInven2::GetInstance()->GetGold() - 1650 > 0)
					{
						CInven2::GetInstance()->SetGold(-1650);
						CInven2::GetInstance()->AddItemToStorage(IT_DART);
					}
				}
			}
			else if (!lstrcmp(L"button_buy2", m_pFrameKey))
			{
				if (CSelectPlayer::GetInstance()->GetSelectPlayerID() == PLAYER1)
				{
					if (CInven::GetInstance()->GetGold() - 2500 > 0)
					{
						CInven::GetInstance()->SetGold(-2500);
						CInven::GetInstance()->AddItemToStorage(IT_SHIELD);
					}
				}
				else
				{
					if (CInven2::GetInstance()->GetGold() - 2500 > 0)
					{
						CInven2::GetInstance()->SetGold(-2500);
						CInven2::GetInstance()->AddItemToStorage(IT_SHIELD);
					}
				}
			}
			else if (!lstrcmp(L"button_back", m_pFrameKey))
			{
				CSceneMgr::GetInstance()->SceneChangeReserve(SC_MENU);
			}
			else if (!lstrcmp(L"button_shop", m_pFrameKey))
			{
				if (*CSceneMgr::GetInstance()->GetPlayModePtr() == MODE2P)
				{
					CSelectPlayer::GetInstance()->SetNextStage(SHOP);
					CSelectPlayer::GetInstance()->SetDraw(true);
				}
				else
					CSceneMgr::GetInstance()->SceneChangeReserve(SC_SHOP);
			}
			else if (!lstrcmp(L"button_exitEdit", m_pFrameKey))
			{
				CSceneMgr::GetInstance()->SceneChangeReserve(SC_MENU);
			}
			else if (!lstrcmp(L"button_stageExit", m_pFrameKey))
			{
				CSceneMgr::GetInstance()->SceneChangeReserve(SC_MENU);
			}
			else if (!lstrcmp(L"button_save", m_pFrameKey))
			{
				CObjMgr::GetInstance()->SaveTile(0);
			}
			else if (!lstrcmp(L"button_myPage", m_pFrameKey))
			{
				if (*CSceneMgr::GetInstance()->GetPlayModePtr() == MODE2P)
				{
					switch (CSelectPlayer::GetInstance()->GetNextStage())
					{
					case MYPAGE:
						CSelectPlayer::GetInstance()->SetNextStage(MYPAGE);
						CSelectPlayer::GetInstance()->SetDraw(true);
						break;
					case SHOP:
						if(CSelectPlayer::GetInstance()->GetSelectPlayerID() == PLAYER1)
							CInven::GetInstance()->SetDraw(true);
						else
							CInven2::GetInstance()->SetDraw(true);
						break;
					case STAGESTATE_END:
						CSelectPlayer::GetInstance()->SetNextStage(MYPAGE);
						CSelectPlayer::GetInstance()->SetDraw(true);
						break;
					default:
						break;
					}
				}
				else
					CInven2::GetInstance()->SetDraw(true);
			}
			else if (!lstrcmp(L"button_exit", m_pFrameKey) && CNotice::GetInstance()->GetDraw() == false)
			{
				CNotice::GetInstance()->SetDraw(true);
			}
		}
	}
	else
	{
		m_bCurState = false;
		if (lstrcmp(L"button_edit", m_pFrameKey) && (lstrcmp(L"button_FirstStage", m_pFrameKey) && lstrcmp(L"button_SecondStage", m_pFrameKey) && lstrcmp(L"button_ThirdStage", m_pFrameKey)))
			m_tFrame.iStart = 0;
	}
	if (m_bCurState == true && (m_bCurState != m_bPreState))
	{
		CSoundMgr::Get_Instance()->PlaySound(L"buttonCursor_0.wav", BUTTON_CURSOR, 0.1f);
	}
	return 0;
}

void CButton::LateUpdate()
{
}

void CButton::Render(HDC hDC)
{
	if (!lstrcmp(L"button_InvenExit", m_pFrameKey))
		return;
	HDC hButton = CBmpMgr::GetInstance()->FindImage(m_pFrameKey);
	GdiTransparentBlt(hDC,					// 목적지 DC
		m_tRect.left,		// 목적지 LEFT,RIGHT
		m_tRect.top,
		(int)m_tFrame.iCX,				// 원본 DC에서 가져올 영역의 크기
		(int)m_tFrame.iCY,
		hButton,						// 원본 이미지 DC
		m_tFrame.iCX * m_tFrame.iStart,	// 원본 이미지 LEFT, TOP
		0,
		m_tFrame.iCX,			// 원본 이미지 가로, 세로 사이즈
		m_tFrame.iCY,
		RGB(255, 0, 255));		// 제거할 픽셀 색상
}

void CButton::Release()
{
}
