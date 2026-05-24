#include "pch.h"
#include "CMouse.h"
#include "CObjMgr.h"
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

	m_pPlayer = dynamic_cast<CPlayer*> (CObjMgr::GetInstance()->GetList(OBJ_PLAYER).front());
}

int CMouse::Update()
{
	POINT ptMouse;

	GetCursorPos(&ptMouse);

	ScreenToClient(g_hWnd, &ptMouse);

	m_tInfo.fX = (float)ptMouse.x;
	m_tInfo.fY = (float)ptMouse.y;
	if(m_pPlayer)
		ShowCursor(FALSE);

	return NONEVENT;
}

void CMouse::LateUpdate()
{
}

void CMouse::Render(HDC hDC)
{
	if (!m_pPlayer)
		return;
	
	if(m_pPlayer->GetWeapon() == WEAPON_MAIN)
	{
		if (m_pPlayer->GetReload() == true)
		{
			m_fAngle = 90.f;
			m_iCount++;
			for (int i = 0; i < m_iCount ;++i)
			{
				m_fAngle -= 1.6f;
				RenderReload(hDC);
			}
		}
		else
		{
			m_iCount = 0;
			RenderMain(hDC);
		}
	}
	else
	{
		if (m_pPlayer->GetReload() == true)
		{
			m_fAngle = 90.f;
			m_iCount++;
			for (int i = 0; i < m_iCount; ++i)
			{
				m_fAngle -= 3.2f;
				RenderReload(hDC);
			}
		}
		else
		{
			m_iCount = 0;
			RenderSub(hDC);
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
	m_tPoint.x = m_tInfo.fX + m_iSize * cosf(m_fAngle * PI / 180.f);
	m_tPoint.y = m_tInfo.fY - m_iSize * sinf(m_fAngle * PI / 180.f);
	Ellipse(hDC,
		int(m_tPoint.x - 5.f),
		int(m_tPoint.y - 5.f),
		int(m_tPoint.x + 5.f),
		int(m_tPoint.y + 5.f));
}
