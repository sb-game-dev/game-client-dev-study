#include "pch.h"
#include "CPlayer.h"
#include "CObjMgr.h"
#include "CAbstractFactory.h"
#include "CBullet.h"

CPlayer::CPlayer() : m_eWEAPON(WEAPON_MAIN), m_eCoverL(DETACHED), m_eCoverR(DETACHED), m_bReload(false), m_dwTime(GetTickCount())
{
	
	ZeroMemory(&m_tAmmoInfo, sizeof(AMMOINFO));
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

	m_tAmmoInfo.iMaxCurMain = 30;
	m_tAmmoInfo.iMaxCurSub = 2;

	m_tAmmoInfo.iCurMain = m_tAmmoInfo.iMaxCurMain;
	m_tAmmoInfo.iCurSub = m_tAmmoInfo.iMaxCurSub;

	m_tAmmoInfo.iReserveMain	= 240;
	m_tAmmoInfo.iReserveSub		= 16;



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

	
	//현재 체력 바
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
		if (GetAsyncKeyState(VK_SPACE) && m_tAmmoInfo.iCurMain >0)
		{
			CObjMgr::GetInstance()->AddObject(OBJ_PLAYER_BULLET, CreateBullet());
			m_tAmmoInfo.iCurMain--;
		}
	}
	else
	{
		if ((GetAsyncKeyState(VK_SPACE) & 0x0001) && m_tAmmoInfo.iCurSub > 0)
		{
			CObjMgr::GetInstance()->AddObject(OBJ_PLAYER_BULLET, CreateBullet(PI / 180.f * -10 	));
			CObjMgr::GetInstance()->AddObject(OBJ_PLAYER_BULLET, CreateBullet(PI / 180.f * -5	));
			CObjMgr::GetInstance()->AddObject(OBJ_PLAYER_BULLET, CreateBullet(PI / 180.f * 0	));
			CObjMgr::GetInstance()->AddObject(OBJ_PLAYER_BULLET, CreateBullet(PI / 180.f * 5	));
			CObjMgr::GetInstance()->AddObject(OBJ_PLAYER_BULLET, CreateBullet(PI / 180.f * 10	));
			m_tAmmoInfo.iCurSub--;
		}
	}
}

void CPlayer::Reload()
{
	if (m_bReload == false)
		return;
	
	if (m_eWEAPON == WEAPON_MAIN && (m_tAmmoInfo.iCurMain >= 30 || m_tAmmoInfo.iReserveMain == 0))
	{
		m_bReload = false;
		return;
	}
	else if (m_eWEAPON == WEAPON_SUB && (m_tAmmoInfo.iCurSub >= 2 || m_tAmmoInfo.iReserveSub == 0))
	{
		m_bReload = false;
		return;
	}

	if (m_eWEAPON == WEAPON_MAIN && m_dwTime + 1800 <= GetTickCount())
	{
		m_bReload = false;
		m_dwTime = GetTickCount();
		int iNum = min(m_tAmmoInfo.iReserveMain, (m_tAmmoInfo.iMaxCurMain - m_tAmmoInfo.iCurMain));
		m_tAmmoInfo.iReserveMain -= min(m_tAmmoInfo.iReserveMain, (m_tAmmoInfo.iMaxCurMain - m_tAmmoInfo.iCurMain));
		m_tAmmoInfo.iCurMain += iNum;
	}
	else if (m_eWEAPON == WEAPON_SUB && m_dwTime + 900 <= GetTickCount())
	{
		m_bReload = false;
		m_dwTime = GetTickCount();
		int iNum = min(m_tAmmoInfo.iReserveSub, (m_tAmmoInfo.iMaxCurSub - m_tAmmoInfo.iCurSub));
		m_tAmmoInfo.iReserveSub -= min(m_tAmmoInfo.iReserveSub, (m_tAmmoInfo.iMaxCurSub - m_tAmmoInfo.iCurSub));
		m_tAmmoInfo.iCurSub += iNum;
	}
}

void CPlayer::Heal()
{
	if (GetAsyncKeyState('3'))
		m_tAbility.fHp = 100.f;
}


void CPlayer::UpdateRect(RECT& m_WeaponRect, INFO& m_WeaponInfo)
{
	m_WeaponRect.left	= LONG(m_WeaponInfo.fX - (m_WeaponInfo.fCX / 2.f));
	m_WeaponRect.top	= LONG(m_WeaponInfo.fY - (m_WeaponInfo.fCY / 2.f));
	m_WeaponRect.right	= LONG(m_WeaponInfo.fX + (m_WeaponInfo.fCX / 2.f));
	m_WeaponRect.bottom	= LONG(m_WeaponInfo.fY + (m_WeaponInfo.fCY / 2.f));
}

CObj* CPlayer::CreateBullet(float fAngle)
{
	CObj* pMouse	= CObjMgr::GetInstance()->GetList(OBJ_MOUSE).front();
	float fDeltaX	= pMouse->GetInfo().fX - m_tInfo.fX;
	float fDeltaY	= pMouse->GetInfo().fY - m_tInfo.fY;

	float iSize		= sqrtf((fDeltaX) * (fDeltaX)+(fDeltaY) * (fDeltaY));
	fAngle	+= acosf(fDeltaX / iSize);

	if (pMouse->GetInfo().fY > m_tInfo.fY)
		fAngle *= -1;

	CObj* pBullet = CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, 1, m_tAbility.fAttack + m_eWEAPON, fAngle);
	return pBullet;
}