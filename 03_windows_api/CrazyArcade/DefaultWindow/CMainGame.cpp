#include "pch.h"
#include "CMainGame.h"
#include "CSceneMgr.h"
#include "CObjMgr.h"
#include "CKeyMgr.h"
#include "CImgMgr.h"
CMainGame::CMainGame() :m_hDC(NULL), m_memDC(NULL), m_Bit(NULL), m_Old(NULL),m_pGraphics(NULL)
{
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);

	m_memDC = CreateCompatibleDC(m_hDC);
	m_Bit = CreateCompatibleBitmap(m_hDC, WINCX, WINCY);
	m_Old = (HBITMAP)SelectObject(m_memDC, m_Bit);
	m_pGraphics = Graphics::FromHDC(m_memDC);


	CSceneMgr::GetInstance()->ChangeScene(SC_EDIT);
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
	CSceneMgr::GetInstance()->Render(m_pGraphics);

	BitBlt(m_hDC, 0, 0, WINCX, WINCY, m_memDC, 0, 0, SRCCOPY);
}

void CMainGame::Release()
{
	ReleaseDC(g_hWnd, m_hDC);


	CImgMgr::Destroy();
	CKeyMgr::Destroy();
	CObjMgr::Destroy();
	CSceneMgr::Destroy();
}
