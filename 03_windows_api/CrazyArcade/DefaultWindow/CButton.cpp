#include "pch.h"
#include "CButton.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CImgMgr.h"
#include "CObjMgr.h"

CButton::CButton() :m_iDrawID(0)
{
}

CButton::~CButton()
{
}

void CButton::Initialize()
{
	CImgMgr::GetInstance()->InsertImg(L"../Resource/Button/png/button_edit.png", L"button_edit");
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

void CButton::Render(Graphics* _pGraphics)
{
	Gdiplus::Image* pImg = CImgMgr::GetInstance()->FindImg(m_pFrameKey);

	Rect rect = { m_tRect.left,m_tRect.top, (int)m_tInfo.fCX,(int)m_tInfo.fCY };

	ImageAttributes attr;
	attr.SetColorKey(
		Color(255, 0, 255),
		Color(255, 0, 255));

	_pGraphics->DrawImage(pImg, rect,
		m_tFrame.iCX * m_tFrame.iStart, m_tFrame.iCY * m_tFrame.iMotion,
		m_tFrame.iCX, m_tFrame.iCY,
		UnitPixel,
		&attr);
}

void CButton::Release()
{
}
