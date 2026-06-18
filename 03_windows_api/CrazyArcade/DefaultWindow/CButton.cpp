#include "pch.h"
#include "CButton.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CImgMgr.h"
#include "CObjMgr.h"
#include "CBmpMgr.h"
#include "CSoundMgr.h"
#include "CInven.h"

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
		m_tFrame.iCX = m_tInfo.fCX;
		m_tFrame.iCY = m_tInfo.fCY;
	}
	else if (!lstrcmp(L"button_back", m_pFrameKey))
	{
		m_tInfo.fCX = 29.f;
		m_tInfo.fCY = 21.f;
		m_tFrame.iCX = m_tInfo.fCX;
		m_tFrame.iCY = m_tInfo.fCY;
	}
	else if (!lstrcmp(L"button_buy0", m_pFrameKey)
		|| !lstrcmp(L"button_buy1", m_pFrameKey) 
		|| !lstrcmp(L"button_buy2", m_pFrameKey)
		|| !lstrcmp(L"button_buy3", m_pFrameKey))
	{
		m_tInfo.fCX = 41.f;
		m_tInfo.fCY = 19.f;
		m_tFrame.iCX = m_tInfo.fCX;
		m_tFrame.iCY = m_tInfo.fCY;
	}
	else if (!lstrcmp(L"button_shop", m_pFrameKey))
	{
		m_tInfo.fCX = 61.f;
		m_tInfo.fCY = 22.f;
		m_tFrame.iCX = m_tInfo.fCX;
		m_tFrame.iCY = m_tInfo.fCY;
	}
	else if (!lstrcmp(L"button2_edit", m_pFrameKey))
	{
		m_tInfo.fCX = 34.f;
		m_tInfo.fCY = 34.f;
		m_tFrame.iCX = m_tInfo.fCX;
		m_tFrame.iCY = m_tInfo.fCY;
	}
	else if (!lstrcmp(L"button_creator", m_pFrameKey))
	{
		m_tInfo.fCX = 124;
		m_tInfo.fCY = 48;

		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 4;
		m_tFrame.iMotion = 0;
		m_tFrame.bLoop = true;
		m_tFrame.iCX = m_tInfo.fCX;
		m_tFrame.iCY = m_tInfo.fCY;
		m_tFrame.dwSpeed = 100.f;
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
		m_tFrame.iCX = m_tInfo.fCX;
		m_tFrame.iCY = m_tInfo.fCY;
		m_tFrame.dwSpeed = 100.f;
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
		m_tFrame.iCX = m_tInfo.fCX;
		m_tFrame.iCY = m_tInfo.fCY;
		m_tFrame.dwSpeed = 100.f;
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
		m_tFrame.iCX = m_tInfo.fCX;
		m_tFrame.iCY = m_tInfo.fCY;
		m_tFrame.dwSpeed = 100.f;
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
		m_tFrame.iCX = m_tInfo.fCX;
		m_tFrame.iCY = m_tInfo.fCY;
		m_tFrame.dwSpeed = 100.f;
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
		m_tFrame.iCX = m_tInfo.fCX;
		m_tFrame.iCY = m_tInfo.fCY;
		m_tFrame.dwSpeed = 100.f;
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
		m_tFrame.iCX = m_tInfo.fCX;
		m_tFrame.iCY = m_tInfo.fCY;
		m_tFrame.dwSpeed = 100.f;
		m_tFrame.dwTime = GetTickCount64();
	}
}

int CButton::Update()
{
	POINT		ptMouse{};
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);

	
	m_bPreState = m_bCurState;
	if (PtInRect(&m_tRect, ptMouse))
	{
		if(lstrcmp(L"button_edit", m_pFrameKey) && lstrcmp(L"button2_edit", m_pFrameKey))
			m_bCurState = true;
		if (m_tFrame.iEnd > 2)
			MoveFrame();
		else
			m_tFrame.iStart = 1;
		if (CKeyMgr::GetInstance()->KeyDown(VK_LBUTTON))
		{
			CSoundMgr::Get_Instance()->PlaySound(L"buttonClick_2.wav", BUTTON_CLICK, 0.3f);

			if (!lstrcmp(L"button_creator", m_pFrameKey))
			{
				CSceneMgr::GetInstance()->SceneChangeReserve(SC_EDIT);
			}
			else if (!lstrcmp(L"button_buy0", m_pFrameKey))
			{
				if(CInven::GetInstance()->GetGold() - 2750 > 0)
					CInven::GetInstance()->SetGold(-2750);
			}
			else if (!lstrcmp(L"button_buy1", m_pFrameKey))
			{
				if (CInven::GetInstance()->GetGold() - 1650 > 0)
					CInven::GetInstance()->SetGold(-1650);
			}
			else if (!lstrcmp(L"button_buy2", m_pFrameKey))
			{
				if (CInven::GetInstance()->GetGold() - 2750 > 0)
					CInven::GetInstance()->SetGold(-2750);
			}
			else if (!lstrcmp(L"button_buy3", m_pFrameKey))
			{
				if (CInven::GetInstance()->GetGold() - 2500 > 0)
					CInven::GetInstance()->SetGold(-2500);
			}
			else if (!lstrcmp(L"button_back", m_pFrameKey))
			{
				CSceneMgr::GetInstance()->SceneChangeReserve(SC_MENU);
			}
			else if (!lstrcmp(L"button_shop", m_pFrameKey))
			{
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
			else if (!lstrcmp(L"button_stageExit", m_pFrameKey))
			{
				CObjMgr::GetInstance()->SaveTile(0);
			}
		}
	}
	else
	{
		m_bCurState = false;
		if (lstrcmp(L"button_edit", m_pFrameKey) && (lstrcmp(L"button_FirstStage", m_pFrameKey) && lstrcmp(L"button_SecondStage", m_pFrameKey)))
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
