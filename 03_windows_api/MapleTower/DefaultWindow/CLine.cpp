#include "pch.h"
#include "CLine.h"

CLine::CLine()
{
}

CLine::CLine(const LINEPOINT& tLeft,const LINEPOINT& tRight)
{
	m_tLine.tLeft	= tLeft;
	m_tLine.tRight	= tRight;
}

CLine::~CLine()
{
}

void CLine::Render(HDC hDC)
{
	MoveToEx(hDC, m_tLine.tLeft.fX, m_tLine.tLeft.fY, nullptr);
	LineTo(hDC, m_tLine.tRight.fX, m_tLine.tRight.fY);
}