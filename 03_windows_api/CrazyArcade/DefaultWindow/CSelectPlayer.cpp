#include "pch.h"
#include "CSelectPlayer.h"
#include "CBmpMgr.h"
#include "CAbstractFactory.h"
#include "CButton.h"
#include "CKeyMgr.h"
#include "CSoundMgr.h"
#include "CSceneMgr.h"
#include "CInven.h"
#include "CInven2.h"

CSelectPlayer* CSelectPlayer::m_pInstance = nullptr;

CSelectPlayer::CSelectPlayer(): m_bDraw(false)
{
	m_pButtonSelectPlayer1	= CAbstractFactory<CButton>::Create(511.5f, 303.5f, L"button_SelectPlayer1");
	m_pButtonSelectPlayer2	= CAbstractFactory<CButton>::Create(511.5f, 330.5f, L"button_SelectPlayer2");
	m_pExitSelectPlayer		= CAbstractFactory<CButton>::Create(400.f, 380.f, L"button_ExitSelectPlayer");

	m_iButtonSelectPlayer1Frame = 0;
	m_iButtonSelectPlayer2Frame = 0;
	m_iExitSelectPlayerFrame = 0;

	m_bButtonPreState = false;
	m_bButtonCurState = false;

	m_eSelectPlayerID = PLAYERID_END;

	m_eStageState = STAGESTATE_END;
}

CSelectPlayer::~CSelectPlayer()
{
	Release();
}

void CSelectPlayer::Update()
{

}
void CSelectPlayer::LateUpdate()
{
	POINT		ptMouse{};
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);

	m_bButtonPreState = m_bButtonCurState;
	RECT rcButtonSelectPlayer1 = { 471,293,552,314 };
	RECT rcButtonSelectPlayer2 = { 471,320,552,341 };
	RECT rcExitSelectPlayer = { 349,365,451,395 };
	if (PtInRect(&rcButtonSelectPlayer1, ptMouse))
	{
		m_bButtonCurState = true;
		m_iButtonSelectPlayer1Frame = 1;
		if (CKeyMgr::GetInstance()->KeyDown(VK_LBUTTON))
		{
			m_bDraw = false;
			CSoundMgr::Get_Instance()->PlaySound(L"buttonClick_2.wav", BUTTON_CLICK, 0.3f);
			m_eSelectPlayerID = PLAYER1;

			if (m_eStageState == SHOP)
			{
				CSceneMgr::GetInstance()->SceneChangeReserve(SC_SHOP);
			}
			else if (m_eStageState == MYPAGE)
			{
				CInven::GetInstance()->SetDraw(true);
			}

		}
	}
	else if (PtInRect(&rcButtonSelectPlayer2, ptMouse))
	{
		m_bButtonCurState = true;
		m_iButtonSelectPlayer2Frame = 1;
		if (CKeyMgr::GetInstance()->KeyDown(VK_LBUTTON))
		{
			m_bDraw = false;
			CSoundMgr::Get_Instance()->PlaySound(L"buttonClick_2.wav", BUTTON_CLICK, 0.3f);
			m_eSelectPlayerID = PLAYER2;

			if (m_eStageState == SHOP)
			{
				CSceneMgr::GetInstance()->SceneChangeReserve(SC_SHOP);
			}
			else if (m_eStageState == MYPAGE)
			{
				CInven2::GetInstance()->SetDraw(true);
			}
		}
	}
	else if (PtInRect(&rcExitSelectPlayer, ptMouse))
	{
		m_bButtonCurState = true;
		m_iExitSelectPlayerFrame = 1;
		if (CKeyMgr::GetInstance()->KeyDown(VK_LBUTTON))
		{
			m_bDraw = false;
			CSoundMgr::Get_Instance()->PlaySound(L"buttonClick_2.wav", BUTTON_CLICK, 0.3f);
		}
	}
	else
	{
		m_iButtonSelectPlayer1Frame = 0;
		m_iButtonSelectPlayer2Frame = 0;
		m_iExitSelectPlayerFrame = 0;
		m_bButtonCurState = false;
	}
	if (m_bButtonCurState && !m_bButtonPreState)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"buttonCursor_0.wav", BUTTON_CURSOR, 0.1f);
	}
}
void CSelectPlayer::Render(HDC hDC)
{
	if (m_bDraw == false)
		return;

	HDC hSelect = CBmpMgr::GetInstance()->FindImage(L"UserSelect");
	GdiTransparentBlt(hDC, 225, 189, 350, 221, hSelect, 0, 0, 350, 221, RGB(255, 0, 255));


	HDC button_SelectPlayer1 = CBmpMgr::GetInstance()->FindImage(L"button_SelectPlayer1");
	BitBlt(hDC, 471, 293, 81, 21, button_SelectPlayer1, m_iButtonSelectPlayer1Frame * 81, 0, SRCCOPY);

	HDC button_SelectPlayer2 = CBmpMgr::GetInstance()->FindImage(L"button_SelectPlayer2");
	BitBlt(hDC, 471, 320, 81, 21, button_SelectPlayer2, m_iButtonSelectPlayer2Frame * 81, 0, SRCCOPY);

	HDC button_ExitSelectPlayer = CBmpMgr::GetInstance()->FindImage(L"button_ExitSelectPlayer");
	BitBlt(hDC, 349, 365, 102, 30, button_ExitSelectPlayer, m_iExitSelectPlayerFrame * 102, 0, SRCCOPY);

}
void CSelectPlayer::Release()
{
	Safe_Delete(m_pButtonSelectPlayer1);
	Safe_Delete(m_pButtonSelectPlayer2);
	Safe_Delete(m_pExitSelectPlayer);
}


