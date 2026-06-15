#include "pch.h"
#include "CButton.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CImgMgr.h"
#include "CObjMgr.h"
#include "CBmpMgr.h"
#include "CSoundMgr.h"

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
		m_tFrame.iCX = 34;
		m_tFrame.iCY = 34;
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
	else if (!lstrcmp(L"button_fastStart", m_pFrameKey))
	{
		m_tInfo.fCX = 124;
		m_tInfo.fCY = 48;

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
		m_bCurState = true;
		MoveFrame();
		if (CKeyMgr::GetInstance()->KeyDown(VK_LBUTTON))
		{
			CSoundMgr::Get_Instance()->PlaySound(L"buttonClick_2.wav", BUTTON_CLICK, 0.3f);

			if (!lstrcmp(L"button_creator", m_pFrameKey))
			{
				CSceneMgr::GetInstance()->SceneChangeReserve(SC_EDIT);
			}
			else if (!lstrcmp(L"button_exitEdit", m_pFrameKey))
			{
				CSceneMgr::GetInstance()->SceneChangeReserve(SC_MENU);
			}
			else if (!lstrcmp(L"button_fastStart", m_pFrameKey))
			{
				CSceneMgr::GetInstance()->SceneChangeReserve(SC_STAGE1);
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
		if (lstrcmp(L"button_edit", m_pFrameKey))
			m_tFrame.iStart = 0;
	}
	if (m_bCurState == true && (m_bCurState != m_bPreState))
	{
		cout << "m_bCurState :" << m_bCurState << "\tm_bPreState: " << m_bPreState << endl;
		CSoundMgr::Get_Instance()->PlaySound(L"buttonCursor_0.wav", BUTTON_CURSOR, 0.1f);
	}
	return 0;
}

void CButton::LateUpdate()
{
}

void CButton::Render(HDC hDC)
{
	//Graphics* _pGraphics = Graphics::FromHDC(hDC);
	//
	//Gdiplus::Image* pImg = CImgMgr::GetInstance()->FindImg(m_pFrameKey);
	//
	//Rect rect = { m_tRect.left,m_tRect.top, (int)m_tInfo.fCX,(int)m_tInfo.fCY };
	//
	//ImageAttributes attr;
	//attr.SetColorKey(
	//	Color(255, 0, 255),
	//	Color(255, 0, 255));
	//
	//_pGraphics->DrawImage(pImg, rect,
	//	m_tFrame.iCX * m_tFrame.iStart, m_tFrame.iCY * m_tFrame.iMotion,
	//	m_tFrame.iCX, m_tFrame.iCY,
	//	UnitPixel,
	//	&attr);
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
