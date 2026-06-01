#include "pch.h"
#include "CButton.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CBmpMgr.h"
CButton::CButton(): m_iDrawID(0)
{
}

CButton::~CButton()
{
}

void CButton::Initialize()
{
	m_tInfo.fCX = 72.f;
	m_tInfo.fCY = 90.f;
}

int CButton::Update()
{
	return 0;
}

void CButton::LateUpdate()
{
	POINT		ptMouse;
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);

	if (PtInRect(&m_tRect, ptMouse))
	{
		if (CKeyMgr::GetInstance()->KeyUp(VK_LBUTTON))
		{
			if (!lstrcmp(L"Start_Button", m_pFrameKey))
				CSceneMgr::GetInstance()->SceneChange(SC_STAGE);
			else if (!lstrcmp(L"Exit_Button", m_pFrameKey))
				DestroyWindow(g_hWnd);
		}
		m_iDrawID = 1;
	}
	else
	{
		m_iDrawID = 0;
	}
}

void CButton::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::GetInstance()->FindImage(m_pFrameKey);
	GdiTransparentBlt(hDC,					// 복사 받을 DC
		m_tRect.left,// 복사 받을 공간의 LEFT, TOP
		m_tRect.top,
		(int)m_tInfo.fCX,		// 복사 받을 공간의 가로, 세로 사이즈
		(int)m_tInfo.fCY,
		hMemDC,					// 복사할 이미지 DC
		m_tInfo.fCX * m_iDrawID,						// 복사할 이미지 LEFT, TOP
		0,
		(int)m_tInfo.fCX,		// 복사할 이미지 가로, 세로
		(int)m_tInfo.fCY,
		RGB(255, 255, 255));	// 제거할 픽셀 색상
}

void CButton::Release()
{
}
