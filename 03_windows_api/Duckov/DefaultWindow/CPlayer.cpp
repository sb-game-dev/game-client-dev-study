#include "pch.h"
#include "CPlayer.h"
#include "CObjMgr.h"
#include "CAbstractFactory.h"
#include "CBullet.h"

CPlayer::CPlayer() : m_eWEAPON(WEAPON_MAIN), m_eCoverL(DETACHED), m_eCoverR(DETACHED), m_iCurMain(30),m_iReserveMain(240), m_iCurSub(13), m_iReserveSub(65), m_bReload(false), m_dwTime(GetTickCount())
{
	ZeroMemory(&m_rcMainWeapon, sizeof(RECT));
	ZeroMemory(&m_rcSubWeapon, sizeof(RECT));

	ZeroMemory(&m_InfoMainWeapon, sizeof(INFO));
	ZeroMemory(&m_InfoSubWeapon, sizeof(INFO));

	ZeroMemory(&m_rcHeal, sizeof(RECT));
	ZeroMemory(&m_InfoHeal, sizeof(INFO));

	ZeroMemory(&m_rcSelect, sizeof(RECT));
	ZeroMemory(&m_InfoSelect, sizeof(INFO));

	ZeroMemory(&m_rcHpBar, sizeof(RECT));
	
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_tInfo = { float(WINCX >> 1), float(WINCY >> 1), 40.f, 40.f };
	m_tAbility = { 100,1 };
	m_fSpeed = 5.f;

	m_InfoMainWeapon = { 300.f,520.f,60.f,60.f };
	UpdateRect(m_rcMainWeapon,m_InfoMainWeapon);

	m_InfoSubWeapon = { 400.f,520.f ,60.f,60.f };
	UpdateRect(m_rcSubWeapon, m_InfoSubWeapon);

	m_InfoHeal = { 500.f,520.f ,60.f,60.f };
	UpdateRect(m_rcHeal, m_InfoHeal);
	
	m_InfoSelect = { 300.f,520.f ,80.f,80.f };
	UpdateRect(m_rcHeal, m_InfoHeal);

}

int CPlayer::Update()
{
	if (m_bDead == DEAD)
		return DEAD;
	KeyInput();
	return NONEVENT;
}

void CPlayer::LateUpdate()
{
	if (m_tInfo.fX >= 158.f && m_tInfo.fX <= 382.f && m_tInfo.fY >= 278.f && m_tInfo.fY <= 362.f)
		m_eCoverL = ATTACHED;
	else
		m_eCoverL = DETACHED;

	if (m_tInfo.fX >= 418.f && m_tInfo.fX <= 622.f && m_tInfo.fY >= 278.f && m_tInfo.fY <= 362.f)
		m_eCoverR = ATTACHED;
	else
		m_eCoverR = DETACHED;
	

	if (m_tAbility.fHp <= 0)
		m_bDead = DEAD;
}

void CPlayer::Render(HDC hDC)
{
	CObj* pMouse = CObjMgr::GetInstance()->GetList(OBJ_MOUSE).front();

	MoveToEx(hDC, (int)m_tInfo.fX, (int)m_tInfo.fY, nullptr);
	LineTo(hDC, (int)pMouse->GetInfo().fX, (int)pMouse->GetInfo().fY);

	Rectangle(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);

	//최대 체력
	//Rectangle(hDC,
	//	m_tInfo.fX - 25.f,
	//	m_tInfo.fY - 40.f,
	//	m_tInfo.fX + 25.f,
	//	m_tInfo.fY - 30.f
	//);
	//현재 체력
	Rectangle(hDC,
		m_tInfo.fX - 25.f,
		m_tInfo.fY - 40.f,
		m_tInfo.fX - 25.f + (m_tAbility.fHp)*0.5f,
		m_tInfo.fY - 30.f
	);
	TCHAR	szBuff[32] = L"Player";
	RECT rc{
		m_tInfo.fX - 25.f,
		m_tInfo.fY - 60.f,
		m_tInfo.fX + 25.f,
		m_tInfo.fY - 40.f
	};
	DrawText(hDC, szBuff, lstrlen(szBuff), &rc, DT_CENTER);


	RenderInven(hDC);

}

void CPlayer::Release()
{
}


void CPlayer::KeyInput()
{
	Move();
	if (m_bReload == false)
	{
		Shoot();
		ChangeWeapon();
	}
	if (GetAsyncKeyState('R') && m_bReload == false)
	{
		m_bReload = true;
		m_dwTime = GetTickCount();
	}
	Reload();
	Heal();
}

void CPlayer::Move()
{
	if (GetAsyncKeyState('D'))
	{
		if (GetAsyncKeyState('W'))
		{
			m_tInfo.fY -= m_fSpeed / sqrtf(2.f);
			m_tInfo.fX += m_fSpeed / sqrtf(2.f);
		}
		else if (GetAsyncKeyState('S'))
		{
			m_tInfo.fY += m_fSpeed / sqrtf(2.f);
			m_tInfo.fX += m_fSpeed / sqrtf(2.f);
		}
		else
			m_tInfo.fX += m_fSpeed;
	}

	else if (GetAsyncKeyState('A'))
	{
		if (GetAsyncKeyState('W'))
		{
			m_tInfo.fY -= m_fSpeed / sqrtf(2.f);
			m_tInfo.fX -= m_fSpeed / sqrtf(2.f);
		}
		else if (GetAsyncKeyState('S'))
		{
			m_tInfo.fY += m_fSpeed / sqrtf(2.f);
			m_tInfo.fX -= m_fSpeed / sqrtf(2.f);
		}
		else
			m_tInfo.fX -= m_fSpeed;
	}

	else if (GetAsyncKeyState('W'))
	{
		m_tInfo.fY -= m_fSpeed;
	}

	else if (GetAsyncKeyState('S'))
	{
		m_tInfo.fY += m_fSpeed;
	}
}

void CPlayer::ChangeWeapon()
{
	if (GetAsyncKeyState(VK_TAB) & 0x0001)
	{
		if (m_eWEAPON == WEAPON_MAIN) m_eWEAPON = WEAPON_SUB;
		else m_eWEAPON = WEAPON_MAIN;
	}
	if (GetAsyncKeyState('1') & 0x0001)
		m_eWEAPON = WEAPON_MAIN;
	if (GetAsyncKeyState('2') & 0x0001)
		m_eWEAPON = WEAPON_SUB;
}

void CPlayer::Shoot()
{
	if (m_eWEAPON == WEAPON_MAIN)
	{
		if (GetAsyncKeyState(VK_SPACE) && m_iCurMain>0)
		{
			CObjMgr::GetInstance()->AddObject(OBJ_PLAYER_BULLET, CreateBullet());
			m_iCurMain--;
		}
	}
	else
	{
		if ((GetAsyncKeyState(VK_SPACE) & 0x0001) && m_iCurSub > 0)
		{
			CObjMgr::GetInstance()->AddObject(OBJ_PLAYER_BULLET, CreateBullet());
			m_iCurSub--;
		}
	}
}

void CPlayer::Reload()
{
	if (m_bReload == false)
		return;
	
	if (m_eWEAPON == WEAPON_MAIN && m_iCurMain >= 30)
	{
		m_bReload = false;
		return;
	}
	else if (m_eWEAPON == WEAPON_SUB && m_iCurSub >= 13)
	{
		m_bReload = false;
		return;
	}

	if (m_eWEAPON == WEAPON_MAIN && m_dwTime + 3600 <= GetTickCount())
	{
		m_bReload = false;
		m_dwTime = GetTickCount();
		int iNum = min(m_iReserveMain, (30 - m_iCurMain));
		m_iReserveMain -= min(m_iReserveMain, (30 - m_iCurMain));
		m_iCurMain += iNum;
	}
	else if (m_eWEAPON == WEAPON_SUB && m_dwTime + 1800 <= GetTickCount())
	{
		m_bReload = false;
		m_dwTime = GetTickCount();
		int iNum = min(m_iReserveSub, (13 - m_iCurSub));
		m_iReserveSub -= min(m_iReserveSub, (13 - m_iCurSub));
		m_iCurSub += iNum;
	}
}

void CPlayer::Heal()
{
	if (GetAsyncKeyState('3'))
		m_tAbility.fHp = 100.f;
}

void CPlayer::RenderInven(HDC hDC)
{
	if (m_eWEAPON == WEAPON_MAIN)
	{
		m_InfoSelect.fX = m_InfoMainWeapon.fX;
		m_InfoSelect.fY = m_InfoMainWeapon.fY;
	}
	else
	{
		m_InfoSelect.fX = m_InfoSubWeapon.fX;
		m_InfoSelect.fY = m_InfoSubWeapon.fY;
	}

	Rectangle(hDC,250,470,550,600);

	UpdateRect(m_rcSelect, m_InfoSelect);
	Rectangle(hDC,
		m_rcSelect.left,
		m_rcSelect.top,
		m_rcSelect.right,
		m_rcSelect.bottom);
	

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
		m_rcSubWeapon.top+20,
		m_rcSubWeapon.right,
		m_rcSubWeapon.bottom+20
	};
	DrawText(hDC, szBuff2, lstrlen(szBuff2), &rc2, DT_CENTER);

	TCHAR	szBuff3[32] = L"Heal";
	RECT rc3{
		m_rcHeal.left,
		m_rcHeal.top+20,
		m_rcHeal.right,
		m_rcHeal.bottom + 20
	};
	DrawText(hDC, szBuff3, lstrlen(szBuff3), &rc3, DT_CENTER);
	if (m_eWEAPON == WEAPON_MAIN)
	{
		TCHAR	szBuffMagazine[32] = L"";
		RECT rcMagazine{
			m_rcMainWeapon.left,
			m_rcMainWeapon.top,
			m_rcMainWeapon.right,
			m_rcMainWeapon.bottom
		};
		swprintf_s(szBuffMagazine, L"%d / %d", m_iCurMain, m_iReserveMain);
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
		swprintf_s(szBuffMagazine, L"%d / %d", m_iCurSub, m_iReserveSub);
		DrawText(hDC, szBuffMagazine, lstrlen(szBuffMagazine), &rcMagazine, DT_CENTER);
	}
}

void CPlayer::UpdateRect(RECT& m_WeaponRect, INFO& m_WeaponInfo)
{
	m_WeaponRect.left	= LONG(m_WeaponInfo.fX - (m_WeaponInfo.fCX / 2.f));
	m_WeaponRect.top	= LONG(m_WeaponInfo.fY - (m_WeaponInfo.fCY / 2.f));
	m_WeaponRect.right	= LONG(m_WeaponInfo.fX + (m_WeaponInfo.fCX / 2.f));
	m_WeaponRect.bottom	= LONG(m_WeaponInfo.fY + (m_WeaponInfo.fCY / 2.f));
}

CObj* CPlayer::CreateBullet()
{
	CObj* pMouse	= CObjMgr::GetInstance()->GetList(OBJ_MOUSE).front();
	float fDeltaX	= pMouse->GetInfo().fX - m_tInfo.fX;
	float fDeltaY	= pMouse->GetInfo().fY - m_tInfo.fY;

	float iSize		= sqrtf((fDeltaX) * (fDeltaX)+(fDeltaY) * (fDeltaY));
	float fAngle	= acosf(fDeltaX / iSize);

	if (pMouse->GetInfo().fY > m_tInfo.fY)
		fAngle *= -1;

	CObj* pBullet = CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, 1, m_tAbility.fAttack + m_eWEAPON, fAngle);
	return pBullet;
}