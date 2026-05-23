#include "pch.h"
#include "CMouse.h"

CMouse::CMouse()
{
}

CMouse::~CMouse()
{
	Release();
}

void CMouse::Initialize()
{
	
}

int CMouse::Update()
{
	POINT ptMouse;

	GetCursorPos(&ptMouse);

	ScreenToClient(g_hWnd, &ptMouse);

	m_tInfo.fX = (float)ptMouse.x;
	m_tInfo.fY = (float)ptMouse.y;

	ShowCursor(FALSE);

	return NONEVENT;
}

void CMouse::LateUpdate()
{
}

void CMouse::Render(HDC hDC)
{
	int iSize = 10;
	MoveToEx(hDC, (int)m_tInfo.fX, (int)m_tInfo.fY - 5, nullptr);
	LineTo(hDC, (int)m_tInfo.fX, (int)m_tInfo.fY - (5 + iSize));

	MoveToEx(hDC, (int)m_tInfo.fX, (int)m_tInfo.fY + 5, nullptr);
	LineTo(hDC, (int)m_tInfo.fX, (int)m_tInfo.fY + (5 + iSize));

	MoveToEx(hDC, (int)m_tInfo.fX - 5, (int)m_tInfo.fY , nullptr);
	LineTo(hDC, (int)m_tInfo.fX - (5 + iSize), (int)m_tInfo.fY );

	MoveToEx(hDC, (int)m_tInfo.fX + 5, (int)m_tInfo.fY , nullptr);
	LineTo(hDC, (int)m_tInfo.fX + (5 + iSize), (int)m_tInfo.fY );

	//TCHAR	szBuff[32] = L"";
	//swprintf_s(szBuff, L"X : %.0f", m_tInfo.fX);
	//TextOut(hDC, 50, 500, szBuff, lstrlen(szBuff));
	//
	//TCHAR	szBuff2[32] = L"";
	//swprintf_s(szBuff2, L"Y : %.0f", m_tInfo.fY);
	//TextOut(hDC, 50, 520, szBuff2, lstrlen(szBuff2));
}

void CMouse::Release()
{
}
