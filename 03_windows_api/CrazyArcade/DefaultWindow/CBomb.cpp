#include "pch.h"
#include "CBomb.h"
#include "CWater.h"
#include "CAbstractFactory.h"
#include "CObjMgr.h"
#include "CBmpMgr.h"
CBomb::CBomb() :m_dwTime(GetTickCount()), m_iBombRange(0)
{
}

CBomb::~CBomb()
{
	Release();
}

void CBomb::Initialize()
{
	CBmpMgr::GetInstance()->InsertBmp(L"../Image/크레이지 아케이드 리소스/Resource/Bullet/BlueBub.bmp", L"Bomb");
	m_tInfo.fCX = 46.f;
	m_tInfo.fCY = 46.f;
}

int CBomb::Update()
{
	if (m_bDead == DEAD)
		return DEAD;
	if (m_dwTime + 1500 <= GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(OBJ_WATER, CreateWater());
		m_bDead = DEAD;
	}
	return NONEVENT;
}

void CBomb::LateUpdate()
{
}

void CBomb::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::GetInstance()->FindImage(L"Bomb");
	GdiTransparentBlt(hDC,
		m_tRect.left,
		m_tRect.top,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hMemDC,
		0,
		0,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(0, 0, 0));
}

void CBomb::Release()
{
}

CObj* CBomb::CreateWater()
{
	CObj* pWater = CAbstractFactory<CWater>::Create(m_tInfo.fX, m_tInfo.fY);

	dynamic_cast<CWater*>(pWater)->Spread(m_iBombRange);
	return pWater;
}
