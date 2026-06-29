#include "pch.h"
#include "CLine.h"
#include "CScrollMgr.h"
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
	int iScrollX = CScrollMgr::GetInstance()->GetScrollX();

	MoveToEx(hDC, m_tLine.tLeft.fX, m_tLine.tLeft.fY, nullptr);
	LineTo(hDC, m_tLine.tRight.fX, m_tLine.tRight.fY);

	//MoveToEx(hDC, (int)m_tLine.tLeft.fX + iScrollX, (int)m_tLine.tLeft.fY, nullptr);
	//LineTo(hDC, (int)m_tLine.tRight.fX + iScrollX, (int)m_tLine.tRight.fY);
}