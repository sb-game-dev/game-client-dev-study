#include "pch.h"
#include "CNotice.h"
#include "CBmpMgr.h"
#include "CAbstractFactory.h"
#include "CButton.h"
#include "CKeyMgr.h"
#include "CSoundMgr.h"
#include "CSceneMgr.h"

CNotice* CNotice::m_pInstance = nullptr;

CNotice::CNotice():m_bDraw(false), m_pExitNoticeButton(nullptr), m_pReLoginButton(nullptr), m_pExitGameButton(nullptr)
{
	m_pExitNoticeButton = CAbstractFactory<CButton>::Create(530.5, 208, L"button_ExitNotice");
	m_pReLoginButton = CAbstractFactory<CButton>::Create(342, 396, L"button_ReLogin");
	m_pExitGameButton = CAbstractFactory<CButton>::Create(458, 396, L"button_ExitGame");

	m_iExitNoticeButtonFrame = 0;
	m_iReLoginButtonFrame = 0;
	m_iExitGameButtonFrame = 0;

	m_bButtonPreState = false;
	m_bButtonCurState = false;
}

CNotice::~CNotice()
{
	Release();
}
void CNotice::Initialize()
{
}
int CNotice::Update()
{
	return 0;
}
void CNotice::LateUpdate()
{
	POINT		ptMouse{};
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);

	m_bButtonPreState = m_bButtonCurState;
	RECT rcExitNoticeButton = { 519,198,542,218 };
	RECT rcReLoginButton = { 291,381,393,411 };
	RECT rcExitGameButton = { 407,381,509,411 };
	if (PtInRect(&rcExitNoticeButton, ptMouse))
	{
		m_bButtonCurState = true;
		m_iExitNoticeButtonFrame = 1;
		if (CKeyMgr::GetInstance()->KeyDown(VK_LBUTTON))
		{
			m_bDraw = false;
			CSoundMgr::Get_Instance()->PlaySound(L"buttonClick_2.wav", BUTTON_CLICK, 0.3f);
		}
	}
	else if (PtInRect(&rcReLoginButton, ptMouse))
	{
		m_bButtonCurState = true;
		m_iReLoginButtonFrame = 1;
		if (CKeyMgr::GetInstance()->KeyDown(VK_LBUTTON))
		{
			m_bDraw = false;
			CSoundMgr::Get_Instance()->PlaySound(L"buttonClick_2.wav", BUTTON_CLICK, 0.3f);
			CSceneMgr::GetInstance()->SceneChangeReserve(SC_LOGIN);
		}
	}
	else if (PtInRect(&rcExitGameButton, ptMouse))
	{
		m_bButtonCurState = true;
		m_iExitGameButtonFrame = 1;
		if (CKeyMgr::GetInstance()->KeyDown(VK_LBUTTON))
		{
			m_bDraw = false;
			CSoundMgr::Get_Instance()->PlaySound(L"buttonClick_2.wav", BUTTON_CLICK, 0.3f);
			PostQuitMessage(0);
		}
	}
	else
	{
		m_iExitNoticeButtonFrame = 0;
		m_iReLoginButtonFrame = 0;
		m_iExitGameButtonFrame = 0;
		m_bButtonCurState = false;
		m_pExitNoticeButton->SetStartFrame(0);
	}
	if (m_bButtonCurState && !m_bButtonPreState)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"buttonCursor_0.wav", BUTTON_CURSOR, 0.1f);
	}
}

void CNotice::Render(HDC hDC)
{
	if (m_bDraw == false)
		return;
	
	HDC hNotice = CBmpMgr::GetInstance()->FindImage(L"Notice");
	GdiTransparentBlt(hDC, 240, 174, 320, 252, hNotice, 0, 0, 320, 252, RGB(255,0,255));

	HDC hExitNoticeButton = CBmpMgr::GetInstance()->FindImage(L"button_ExitNotice");
	BitBlt(hDC, 519, 198, 23, 20, hExitNoticeButton, m_iExitNoticeButtonFrame * 23, 0, SRCCOPY);

	HDC hReLoginButton = CBmpMgr::GetInstance()->FindImage(L"button_ReLogin");
	BitBlt(hDC, 291, 381, 102, 30, hReLoginButton, m_iReLoginButtonFrame * 102 ,0, SRCCOPY);

	HDC hExitGameButton = CBmpMgr::GetInstance()->FindImage(L"button_ExitGame");
	BitBlt(hDC, 407, 381, 102, 30, hExitGameButton, m_iExitGameButtonFrame * 102, 0, SRCCOPY);
}

void CNotice::Release()
{
	Safe_Delete(m_pExitGameButton);
	Safe_Delete(m_pExitNoticeButton);
	Safe_Delete(m_pReLoginButton);
}