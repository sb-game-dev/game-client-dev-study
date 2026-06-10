#include "pch.h"
#include "CMainGame.h"
#include "CSceneMgr.h"
#include "CObjMgr.h"
#include "CKeyMgr.h"
#include "CImgMgr.h"
#include "CMouse.h"
#include "CAbstractFactory.h"
#include "CBmpMgr.h"
CMainGame::CMainGame() :m_hDC(NULL), m_memDC(NULL), m_Bit(NULL), m_Old(NULL),m_pGraphics(NULL), m_iFPS(0),m_dwTime(GetTickCount64())
{
	ZeroMemory(&m_szFPS, sizeof(m_szFPS));
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);

	CObjMgr::GetInstance()->AddObject(OBJ_MOUSE, CAbstractFactory<CMouse>::Create(0.f, 0.f));

	m_memDC = CreateCompatibleDC(m_hDC);
	m_Bit = CreateCompatibleBitmap(m_hDC, WINCX, WINCY);
	m_Old = (HBITMAP)SelectObject(m_memDC, m_Bit);

	CSceneMgr::GetInstance()->ChangeScene(SC_LOGO);
}

void CMainGame::Update()
{
	CKeyMgr::GetInstance()->KeyUpdate();
	CSceneMgr::GetInstance()->Update();
}

void CMainGame::LateUpdate()
{
	CSceneMgr::GetInstance()->LateUpdate();
	CSceneMgr::GetInstance()->SceneProcess();
}

void CMainGame::Render()
{
	m_iFPS++;

	if (m_dwTime + 1000 < GetTickCount64())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);

		m_iFPS = 0;

		m_dwTime = GetTickCount64();

		SetWindowText(g_hWnd, m_szFPS);
	}
	CObjMgr::GetInstance()->Render(m_memDC);
	CSceneMgr::GetInstance()->Render(m_memDC);

	BitBlt(m_hDC, 0, 0, WINCX, WINCY, m_memDC, 0, 0, SRCCOPY);
}

void CMainGame::Release()
{
	ReleaseDC(g_hWnd, m_hDC);

	CBmpMgr::Destroy();
	CImgMgr::Destroy();
	CKeyMgr::Destroy();
	CObjMgr::Destroy();
	CSceneMgr::Destroy();
}
