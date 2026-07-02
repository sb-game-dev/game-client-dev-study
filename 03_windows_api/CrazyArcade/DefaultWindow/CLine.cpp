#include "pch.h"
#include "CLine.h"
#include "CScrollMgr.h"
#include "CBmpMgr.h"
#include "CImgMgr.h"
CLine::CLine()
{
}

CLine::CLine(const LINEPOINT& tLeft, const LINEPOINT& tRight)
{
	m_tLine.tLeft = tLeft;
	m_tLine.tRight = tRight;
}

CLine::~CLine()
{
}

void CLine::Render(HDC hDC)
{
	//if (m_bDraw == false)
	//	return;
	int iScrollX = CScrollMgr::GetInstance()->GetScrollX();

	//MoveToEx(hDC, m_tLine.tLeft.fX, m_tLine.tLeft.fY + MWINCY - 600, nullptr);
	//LineTo(hDC, m_tLine.tRight.fX, m_tLine.tRight.fY + MWINCY - 600);
	if (m_tLine.tRight.fX == m_tLine.tLeft.fX)
	{
		Graphics* _pGraphics = Graphics::FromHDC(hDC);
		Gdiplus::Image* pBoard = CImgMgr::GetInstance()->FindImg(L"Rope");

		Rect rect = {
			int(m_tLine.tLeft.fX - 10.f),
			int(m_tLine.tLeft.fY) + MWINCY - 600,
			30,360 };

		_pGraphics->DrawImage(pBoard, rect, 0, 0, 30, 360, UnitPixel);
	}
	else if (m_tLine.tRight.fX - m_tLine.tLeft.fX <= 50)
	{
		Graphics* _pGraphics = Graphics::FromHDC(hDC);
		Gdiplus::Image* pBoard = CImgMgr::GetInstance()->FindImg(L"Board1");

		Rect rect = {
			int(m_tLine.tLeft.fX),
			int(m_tLine.tLeft.fY - 24.f) + MWINCY - 600,
			48,70 };

		_pGraphics->DrawImage(pBoard, rect, 0, 0, 48, 70, UnitPixel);
	}
	else if (m_tLine.tRight.fX - m_tLine.tLeft.fX <= 160)
	{
		Graphics* _pGraphics = Graphics::FromHDC(hDC);
		Gdiplus::Image* pBoard = CImgMgr::GetInstance()->FindImg(L"Board4");

		Rect rect = { 
			int(m_tLine.tLeft.fX),
			int(m_tLine.tLeft.fY - 24.f) + MWINCY - 600,
			159,70 };

		_pGraphics->DrawImage(pBoard, rect, 0, 0, 159, 70, UnitPixel);
	}
	//MoveToEx(hDC, (int)m_tLine.tLeft.fX + iScrollX, (int)m_tLine.tLeft.fY, nullptr);
	//LineTo(hDC, (int)m_tLine.tRight.fX + iScrollX, (int)m_tLine.tRight.fY);
}