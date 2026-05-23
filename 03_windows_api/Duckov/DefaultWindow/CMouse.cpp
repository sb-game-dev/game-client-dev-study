#include "pch.h"
#include "CMouse.h"
#include "CObjMgr.h"
#include "CPlayer.h"
CMouse::CMouse():m_iSize(0)
{
	ZeroMemory(&m_tPoint, sizeof(POINT));
}

CMouse::~CMouse()
{
	Release();
}

void CMouse::Initialize()
{
	m_iSize = 10;
	m_fSpeed = 1.f;
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
	if (CObjMgr::GetInstance()->GetList(OBJ_PLAYER).size() == 0)
		return;
	
	if(dynamic_cast<CPlayer*> (CObjMgr::GetInstance()->GetList(OBJ_PLAYER).front())->GetWeapon() == WEAPON_SUB)
	{
		if (dynamic_cast<CPlayer*> (CObjMgr::GetInstance()->GetList(OBJ_PLAYER).front())->GetReload() == true)
		{
			m_fAngle -= m_fSpeed * 4.f;
			m_tPoint.x = m_tInfo.fX + m_iSize * 2 * cosf(m_fAngle * PI / 180.f);
			m_tPoint.y = m_tInfo.fY - m_iSize * 2 * sinf(m_fAngle * PI / 180.f);
			Ellipse(hDC,
				int(m_tPoint.x - 10.f),
				int(m_tPoint.y - 10.f),
				int(m_tPoint.x + 10.f),
				int(m_tPoint.y + 10.f));
		}
		else
		{
			RenderSub(hDC);
		}
	}
	else
	{
		if (dynamic_cast<CPlayer*> (CObjMgr::GetInstance()->GetList(OBJ_PLAYER).front())->GetReload() == true)
		{
			m_fAngle -= m_fSpeed * 2.f;
			m_tPoint.x = m_tInfo.fX + m_iSize * 2 * cosf(m_fAngle * PI / 180.f);
			m_tPoint.y = m_tInfo.fY - m_iSize * 2 * sinf(m_fAngle * PI / 180.f);
			Ellipse(hDC,
				int(m_tPoint.x - 10.f),
				int(m_tPoint.y - 10.f),
				int(m_tPoint.x + 10.f),
				int(m_tPoint.y + 10.f));
		}
		else
		{
			RenderMain(hDC);
		}
	}
	TCHAR	szBuff[32] = L"";
	swprintf_s(szBuff, L"X : %.0f", m_tInfo.fX);
	TextOut(hDC, 50, 500, szBuff, lstrlen(szBuff));
	
	TCHAR	szBuff2[32] = L"";
	swprintf_s(szBuff2, L"Y : %.0f", m_tInfo.fY);
	TextOut(hDC, 50, 520, szBuff2, lstrlen(szBuff2));
}

void CMouse::Release()
{
}

void CMouse::RenderMain(HDC hDC)
{
	Rectangle(hDC, m_tInfo.fX - 2, m_tInfo.fY - (m_iSize + 5), m_tInfo.fX + 2, m_tInfo.fY - 5);
	Rectangle(hDC, m_tInfo.fX - 2, m_tInfo.fY + 5, m_tInfo.fX + 2, m_tInfo.fY + (m_iSize + 5));
	Rectangle(hDC, m_tInfo.fX - (m_iSize + 5), m_tInfo.fY - 2, m_tInfo.fX - 5, m_tInfo.fY + 2);
	Rectangle(hDC, m_tInfo.fX + 5, m_tInfo.fY - 2, m_tInfo.fX + (m_iSize + 5), m_tInfo.fY + 2);
}

void CMouse::RenderSub(HDC hDC)
{
	MoveToEx(hDC, (int)m_tInfo.fX, (int)m_tInfo.fY - 5, nullptr);
	LineTo(hDC, (int)m_tInfo.fX, (int)m_tInfo.fY - (5 + m_iSize));

	MoveToEx(hDC, (int)m_tInfo.fX, (int)m_tInfo.fY + 5, nullptr);
	LineTo(hDC, (int)m_tInfo.fX, (int)m_tInfo.fY + (5 + m_iSize));

	MoveToEx(hDC, (int)m_tInfo.fX - 5, (int)m_tInfo.fY, nullptr);
	LineTo(hDC, (int)m_tInfo.fX - (5 + m_iSize), (int)m_tInfo.fY);

	MoveToEx(hDC, (int)m_tInfo.fX + 5, (int)m_tInfo.fY, nullptr);
	LineTo(hDC, (int)m_tInfo.fX + (5 + m_iSize), (int)m_tInfo.fY);
}

void CMouse::RenderReload(HDC hDC)
{
}
