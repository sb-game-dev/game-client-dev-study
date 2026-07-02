#include "pch.h"
#include "CStage6.h"
#include "CAbstractFactory.h"
#include "CMaplePlayer.h"
#include "CBmpMgr.h"
#include "CObjMgr.h"
#include "CLineMgr.h"
#include "CScrollMgr.h"
#include "CSoundMgr.h"

CStage6::CStage6()
{
	m_pPlayer	= nullptr;
	m_pLineList = nullptr;
	m_pRopeList = nullptr;
}

CStage6::~CStage6()
{
	Release();
}

void CStage6::Initialize()
{
	CLineMgr::GetInstance()->Initialize();

	m_hDC = GetDC(g_hWnd);
	m_memDC = CreateCompatibleDC(m_hDC);
	m_Bit = CreateCompatibleBitmap(m_hDC, 1920, MWINCY);
	m_Old = (HBITMAP)SelectObject(m_memDC, m_Bit);
	
	m_hBackGround = CBmpMgr::GetInstance()->FindImage(L"MBackGround");
	
	BitBlt(m_memDC,
		0, 0,
		1920, MWINCY,
		m_hBackGround,
		0,
		0,
		SRCCOPY);
	
	CLineMgr::GetInstance()->Render(m_memDC);

	m_pPlayer = CAbstractFactory<CMaplePlayer>::Create(960.f, 500, L"Player_RIGHT");
	CScrollMgr::GetInstance()->SetScrollX(-550.f);
	CScrollMgr::GetInstance()->SetScrollY(2550.f);
	CObjMgr::GetInstance()->AddObject(OBJ_PLAYER, m_pPlayer);
	CSoundMgr::Get_Instance()->PlayBGM(L"MapleBGM.wav", 0.5f);
}

int CStage6::Update()
{
	CObjMgr::GetInstance()->Update();
	CLineMgr::GetInstance()->Update();
	return 0;
}

void CStage6::LateUpdate()
{
	CObjMgr::GetInstance()->LateUpdate();
}

void CStage6::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::GetInstance()->GetScrollX();
	int iScrollY = (int)CScrollMgr::GetInstance()->GetScrollY();

	BitBlt(hDC,
		iScrollX, 0,
		1920, MWINCY,
		m_memDC,
		0,
		MWINCY - 600 - iScrollY,
		SRCCOPY);
	
	CObjMgr::GetInstance()->Render(hDC);

	if (dynamic_cast<CMaplePlayer*>(m_pPlayer)->GetOffsetMove())
	{
		HDC hUI = CBmpMgr::GetInstance()->FindImage(L"MainUI");
		GdiTransparentBlt(hDC,
			0, 0,
			WINCX, WINCY,
			hUI,
			0,
			0, WINCX, WINCY,
			RGB(255, 0, 255));
	}

}

void CStage6::Release()
{
	ReleaseDC(g_hWnd, m_hDC);
}
