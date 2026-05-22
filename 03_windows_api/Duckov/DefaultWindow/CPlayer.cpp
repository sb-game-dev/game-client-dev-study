#include "pch.h"
#include "CPlayer.h"
#include "CObjMgr.h"
#include "CAbstractFactory.h"
#include "CBullet.h"

CPlayer::CPlayer() : m_eWEAPON(WEAPON_MAIN)
{
	ZeroMemory(&m_rcMainWeapon, sizeof(RECT));
	ZeroMemory(&m_rcSubWeapon, sizeof(RECT));

	ZeroMemory(&m_InfoMainWeapon, sizeof(INFO));
	ZeroMemory(&m_InfoSubWeapon, sizeof(INFO));

	ZeroMemory(&m_rcHeal, sizeof(RECT));
	ZeroMemory(&m_InfoHeal, sizeof(INFO));

	ZeroMemory(&m_rcSelect, sizeof(RECT));
	ZeroMemory(&m_InfoSelect, sizeof(INFO));
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

	RenderInven(hDC);
}

void CPlayer::Release()
{
}


void CPlayer::KeyInput()
{
	Move();
	ChangeWeapon();
	Shoot();
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
		if (GetAsyncKeyState(VK_SPACE))
			CObjMgr::GetInstance()->AddObject(OBJ_PLAYER_BULLET, CreateBullet());
	}
	else
	{
		if (GetAsyncKeyState(VK_SPACE) & 0x0001)
			CObjMgr::GetInstance()->AddObject(OBJ_PLAYER_BULLET, CreateBullet());
	}
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