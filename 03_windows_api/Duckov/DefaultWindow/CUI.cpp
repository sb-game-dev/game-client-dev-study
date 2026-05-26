#include "pch.h"
#include "CUI.h"

CUI::CUI():m_pPlayer(nullptr)
{
	ZeroMemory(&m_rcHeal, sizeof(RECT));
	ZeroMemory(&m_rcMainWeapon, sizeof(RECT));
	ZeroMemory(&m_rcSubWeapon, sizeof(RECT));
	ZeroMemory(&m_tAmmoInfo, sizeof(AMMOINFO));
}

CUI::~CUI()
{
}
void CUI::Update()
{

}
void CUI::Initialize()
{
	m_rcMainWeapon = {
		270,
		490,
		330,
		550,
	};
	
	m_rcSubWeapon = {
		370,
		490,
		430,
		550
	};
	
	m_rcHeal = {
		470,
		490,
		530,
		550
	};
}
void CUI::Render(HDC hDC)
{
	Rectangle(hDC, 250, 470, 550, 600);

	WEAPON m_eWeapon = m_pPlayer->GetWeapon();
	m_tAmmoInfo = m_pPlayer->GetAmmoInfo();

	if (m_eWeapon == WEAPON_MAIN)
	{
		Rectangle(hDC,
			m_rcMainWeapon.left		- 10,
			m_rcMainWeapon.top		- 10,
			m_rcMainWeapon.right	+10,
			m_rcMainWeapon.bottom	+ 10);
	}
	else
	{
		Rectangle(hDC,
			m_rcSubWeapon.left		- 10,
			m_rcSubWeapon.top		- 10,
			m_rcSubWeapon.right		+ 10,
			m_rcSubWeapon.bottom	+ 10);
	}

	TextOut(hDC, WINCX * 0.5f - 100, WINCY - 30, L"1", lstrlen(L"1"));
	Rectangle(hDC,
		m_rcMainWeapon.left,
		m_rcMainWeapon.top,
		m_rcMainWeapon.right,
		m_rcMainWeapon.bottom);

	TextOut(hDC, WINCX * 0.5f, WINCY - 30, L"2", lstrlen(L"2"));
	Rectangle(hDC,
		m_rcSubWeapon.left,
		m_rcSubWeapon.top,
		m_rcSubWeapon.right,
		m_rcSubWeapon.bottom);

	TextOut(hDC, WINCX * 0.5f + 100, WINCY - 30, L"3", lstrlen(L"3"));
	Rectangle(hDC,
		m_rcHeal.left,
		m_rcHeal.top,
		m_rcHeal.right,
		m_rcHeal.bottom);


	TCHAR	szBuff[32] = L"Main";
	RECT rc{
		m_rcMainWeapon.left,
		m_rcMainWeapon.top + 20,
		m_rcMainWeapon.right,
		m_rcMainWeapon.bottom + 20
	};
	DrawText(hDC, szBuff, lstrlen(szBuff), &rc, DT_CENTER);


	TCHAR	szBuff2[32] = L"Sub";
	RECT rc2{
		m_rcSubWeapon.left,
		m_rcSubWeapon.top + 20,
		m_rcSubWeapon.right,
		m_rcSubWeapon.bottom + 20
	};
	DrawText(hDC, szBuff2, lstrlen(szBuff2), &rc2, DT_CENTER);

	TCHAR	szBuff3[32] = L"Heal";
	RECT rc3{
		m_rcHeal.left,
		m_rcHeal.top + 20,
		m_rcHeal.right,
		m_rcHeal.bottom + 20
	};
	DrawText(hDC, szBuff3, lstrlen(szBuff3), &rc3, DT_CENTER);
	if (m_eWeapon == WEAPON_MAIN)
	{
		TCHAR	szBuffMagazine[32] = L"";
		RECT rcMagazine{
			m_rcMainWeapon.left,
			m_rcMainWeapon.top,
			m_rcMainWeapon.right,
			m_rcMainWeapon.bottom
		};
		swprintf_s(szBuffMagazine, L"%d / %d", m_tAmmoInfo.iCurMain, m_tAmmoInfo.iReserveMain);
		DrawText(hDC, szBuffMagazine, lstrlen(szBuffMagazine), &rcMagazine, DT_CENTER);
	}
	else
	{
		TCHAR	szBuffMagazine[32] = L"";
		RECT rcMagazine{
			m_rcSubWeapon.left,
			m_rcSubWeapon.top,
			m_rcSubWeapon.right,
			m_rcSubWeapon.bottom
		};
		swprintf_s(szBuffMagazine, L"%d / %d", m_tAmmoInfo.iCurSub, m_tAmmoInfo.iReserveSub);
		DrawText(hDC, szBuffMagazine, lstrlen(szBuffMagazine), &rcMagazine, DT_CENTER);
	}
}