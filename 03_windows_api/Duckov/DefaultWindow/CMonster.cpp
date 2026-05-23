#include "pch.h"
#include "CMonster.h"
#include "CObjMgr.h"
#include "CAbstractFactory.h"
#include "CBullet.h"
CMonster::CMonster() :m_fAngleSpeed(0.f), m_dwTime(GetTickCount())
{
}

CMonster::~CMonster()
{
	Release();
}

void CMonster::Initialize()
{
	m_tInfo = {WINCX*0.5f, 80.f, 40.f,40.f };
	m_tAbility = { 100,5 };
	m_fAngle = 90.f;
	m_fSpeed = 2.f;
	m_fAngleSpeed = 2.f;
	m_pTarget = CObjMgr::GetInstance()->GetList(OBJ_PLAYER).front();


}

int CMonster::Update()
{
	if (m_bDead == DEAD)
		return DEAD;

	float fDeltaX = m_pTarget->GetInfo().fX - m_tInfo.fX;
	float fDeltaY = m_pTarget->GetInfo().fY - m_tInfo.fY;
	float fDistance = sqrtf(fDeltaX * fDeltaX + fDeltaY * fDeltaY);

	if (fDistance <= 200.f || m_tAbility.fHp < 100.f)
	{
		if (m_dwTime + 1000 <= GetTickCount())
		{
			Shoot();
			m_dwTime = GetTickCount();
		}
	}
	
	if (fDistance <= 200.f)
	{
		
			float fAngle = acosf(fDeltaX / fDistance) * 180.f / PI;

			if (m_pTarget->GetInfo().fY > m_tInfo.fY)
				fAngle *= -1.f;

			m_tInfo.fX += m_fSpeed * cosf(fAngle * (PI / 180.f));
			m_tInfo.fY -= m_fSpeed * sinf(fAngle * (PI / 180.f));

	}
	else
	{
		if (abs(m_tInfo.fY - 2.f)>= 80.f)
		{
			m_fAngle = 90.f;
			fDeltaX = WINCX * 0.5f - m_tInfo.fX;
			fDeltaY = 80.f - m_tInfo.fY;
			fDistance = sqrtf(fDeltaX * fDeltaX + fDeltaY * fDeltaY);
			float fAngle = acosf(fDeltaX / fDistance) * 180.f / PI;
			if (80.f > m_tInfo.fY)
				fAngle *= -1.f;

			m_tInfo.fX += m_fSpeed * 2 * cosf(fAngle * (PI / 180.f));
			m_tInfo.fY -= m_fSpeed * 2 * sinf(fAngle * (PI / 180.f));
		}
		else
		{
			m_fAngle += m_fAngleSpeed;
			m_tInfo.fX = WINCX * 0.5f + 200.f * cosf(m_fAngle * PI / 180.f);
		}
	}


	return NONEVENT;
}

void CMonster::LateUpdate()
{
	if (m_tAbility.fHp <= 0)
		m_bDead = DEAD;
}

void CMonster::Render(HDC hDC)
{
	Rectangle(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);

	MoveToEx(hDC, m_tRect.left, m_tRect.top, nullptr);
	LineTo(hDC, m_tRect.right, m_tRect.bottom);

	MoveToEx(hDC, m_tRect.right, m_tRect.top, nullptr);
	LineTo(hDC, m_tRect.left, m_tRect.bottom);
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
		m_tInfo.fX - 25.f + (m_tAbility.fHp) * 0.5f,
		m_tInfo.fY - 30.f
	);
	TCHAR	szBuff[32] = L"Monster"; 
	RECT rc{ 
		m_tInfo.fX - 25.f,
		m_tInfo.fY - 60.f,
		m_tInfo.fX + 25.f,
		m_tInfo.fY - 40.f
	};
	DrawText(hDC, szBuff, lstrlen(szBuff),&rc , DT_NOCLIP);
}

void CMonster::Release()
{

}

void CMonster::Shoot()
{
	CObjMgr::GetInstance()->AddObject(OBJ_MONSER_BULLET, CreateBullet());
}

CObj* CMonster::CreateBullet()
{
	if (CObjMgr::GetInstance()->GetList(OBJ_PLAYER).size() == 0)
		return nullptr;
	CObj* pPLAYER	= CObjMgr::GetInstance()->GetList(OBJ_PLAYER).front();
	
	float fDeltaX	= pPLAYER->GetInfo().fX - m_tInfo.fX;
	float fDeltaY	= pPLAYER->GetInfo().fY - m_tInfo.fY;
	
	float iSize		= sqrtf((fDeltaX) * (fDeltaX)+(fDeltaY) * (fDeltaY));
	float fAngle	= acosf(fDeltaX / iSize);
	
	if (pPLAYER->GetInfo().fY > m_tInfo.fY)
		fAngle *= -1;

	CObj* pBullet = CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, 1, m_tAbility.fAttack, fAngle);
	pBullet->SetSpeed(15.f);
	return pBullet;
}