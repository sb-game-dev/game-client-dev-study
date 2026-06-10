#include "pch.h"
#include "CButton.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CImgMgr.h"
#include "CObjMgr.h"
#include "CBmpMgr.h"

CButton::CButton() :m_iDrawID(0)
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
	else if (!lstrcmp(L"", m_pFrameKey))
	{

	}
}

int CButton::Update()
{
	POINT		ptMouse{};
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);


	if (PtInRect(&m_tRect, ptMouse))
	{
		if (CKeyMgr::GetInstance()->KeyDown(VK_LBUTTON))
		{
			
		}

		m_iDrawID = 1;
	}
	else
		m_iDrawID = 0;


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
	BitBlt(hDC,							    // 목적지 DC
		m_tRect.left,		// 목적지 LEFT,RIGHT
		m_tRect.top,
		(int)m_tFrame.iCX,				// 원본 DC에서 가져올 영역의 크기
		(int)m_tFrame.iCY,
		hButton,							// 원본 DC
		m_tFrame.iCX * m_tFrame.iStart,		// 원본 이미지에서 가져오기 시작할 좌표의 LEFT, TOP
		0,
		SRCCOPY);						// 그대로 복사하여 출력
}

void CButton::Release()
{
}
