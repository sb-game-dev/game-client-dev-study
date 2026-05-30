#include "pch.h"
#include "CBomb.h"
#include "CWater.h"
#include "CAbstractFactory.h"
#include "CObjMgr.h"
#include "CBmpMgr.h"
#include "CCollisionMgr.h"
CBomb::CBomb() :m_dwTime(GetTickCount()), m_iBombRange(0), m_bPlayerCollision(true)
{
}

CBomb::~CBomb()
{
	Release();
}

void CBomb::Initialize()
{
	CBmpMgr::GetInstance()->InsertBmp(L"../Image/크레이지 아케이드 리소스/Resource/Bullet/BlueBub.bmp", L"Bomb");
	m_tInfo.fCX = 40.f;
	m_tInfo.fCY = 40.f;
	m_tRenderInfo = { 0, 3, 250,0,0 };
}

int CBomb::Update()
{
	if (m_bDead == DEAD)
		return DEAD;
	if (m_bPlayerCollision == true)
	{
		float fTemp1 = 0.f;
		float fTemp2 = 0.f;
		if (!CCollisionMgr::CheckRect(this, CObjMgr::GetInstance()->GetList(OBJ_PLAYER).front(), fTemp1, fTemp2))
		{
			m_bPlayerCollision = false;
		}
	}
	if (m_dwTime + 1500 <= GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(OBJ_WATER, CreateWater());
		m_bDead = DEAD;
	}
	if(m_dwAniTime + m_tRenderInfo.dwFrameSpeed <= GetTickCount())
	{
		m_dwAniTime = GetTickCount();
		m_iFrame = (m_iFrame + 1) % m_tRenderInfo.iFrameEnd;
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
		46,//(int)m_tInfo.fCX
		46,//(int)m_tInfo.fCY
		hMemDC,
		m_iFrame * 46,//m_tInfo.fCX
		0,
		46,//(int)m_tInfo.fCX
		46,//(int)m_tInfo.fCY
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
