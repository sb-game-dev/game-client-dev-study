#include "pch.h"
#include "CMouse.h"

CMouse::CMouse()
{
}

CMouse::~CMouse()
{
}

void CMouse::Initialize()
{
}

int CMouse::Update()
{
	POINT		ptMouse{};

	GetCursorPos(&ptMouse);	// ½ºÅ©¸° ÁÂÇ¥ÀÇ ¸¶¿ì½º °ªÀ» ¾ò¾î¿È

	ScreenToClient(g_hWnd, &ptMouse); // ½ºÅ©¸° ÁÂÇ¥¸¦ Ã¢ ÁÂÇ¥·Î º¯È¯


	m_tInfo.fX = (float)ptMouse.x;
	m_tInfo.fY = (float)ptMouse.y;

	//ShowCursor(FALSE);

	return NONEVENT;
}

void CMouse::LateUpdate()
{
}

void CMouse::Render(HDC hDC)
{
	TCHAR	szBuff[32] = L"";
	swprintf_s(szBuff, L"MouseX : %.0f \n MouseY : %.0f", m_tInfo.fX,m_tInfo.fY);
	TextOut(hDC, 50, 50, szBuff, lstrlen(szBuff));
}

void CMouse::Release()
{
}
