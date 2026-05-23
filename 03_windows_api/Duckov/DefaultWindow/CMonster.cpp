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
	m_fSpeed = 200.f;
	m_fAngleSpeed = 2.f;
}

int CMonster::Update()
{
	if (m_bDead == DEAD)
		return DEAD;

	m_fAngle += m_fAngleSpeed;
	m_tInfo.fX = WINCX * 0.5f + 200.f * cosf(m_fAngle * PI / 180.f);

	//if (m_dwTime + 1000 <= GetTickCount())
	//{
	//	Shoot();
	//	m_dwTime = GetTickCount();
	//}

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

	TCHAR	szBuff[32] = L"";
	swprintf_s(szBuff, L"Monster HP : %.0f", m_tAbility.fHp);
	TextOut(hDC, 50, 50, szBuff, lstrlen(szBuff));
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