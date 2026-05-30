#include "pch.h"
#include "CWater.h"
#include "CObjMgr.h"
#include "CAbstractFactory.h"
#include "CBmpMgr.h"
CWater::CWater():m_dwTime(GetTickCount())
{
}

CWater::~CWater()
{
}

void CWater::Initialize()
{
	m_tInfo.fCX = 40.f;
	m_tInfo.fCY = 40.f;
	CBmpMgr::GetInstance()->InsertBmp(L"../Image/크레이지 아케이드 리소스/Resource/Bullet/Boomcenter.bmp", L"Water");
}

int CWater::Update()
{
	if (m_bDead == DEAD)
		return DEAD;
	return NONEVENT;
}

void CWater::LateUpdate()
{
	if (m_dwTime + 500 <= GetTickCount())
		m_bDead = DEAD;
}

void CWater::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::GetInstance()->FindImage(L"Water");
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

void CWater::Release()
{
}

void CWater::Spread(int iBombRange)
{
	//right
	for (int i = 1; i <= iBombRange; ++i)
	{
		CObj* pWater = CAbstractFactory<CWater>::Create(m_tInfo.fX + m_tInfo.fCX * i, m_tInfo.fY);
		CObjMgr::GetInstance()->AddObject(OBJ_WATER, pWater);
		if (i + 1 > iBombRange) break;
		for (auto& pBlock : CObjMgr::GetInstance()->GetList(OBJ_BLOCK))
		{
			if (m_tInfo.fX + m_tInfo.fCX * (i + 1) == pBlock->GetInfo().fX &&
				m_tInfo.fY == pBlock->GetInfo().fY)
			{
				break;
			}
		}
	}
	//left
	for (int i = 1; i <= iBombRange; ++i)
	{
		CObj* pWater = CAbstractFactory<CWater>::Create(m_tInfo.fX - m_tInfo.fCX * i, m_tInfo.fY);
		CObjMgr::GetInstance()->AddObject(OBJ_WATER, pWater);
		if (i + 1 > iBombRange) break;
		for (auto& pBlock : CObjMgr::GetInstance()->GetList(OBJ_BLOCK))
		{
			if (m_tInfo.fX - m_tInfo.fCX * (i + 1) == pBlock->GetInfo().fX &&
				m_tInfo.fY == pBlock->GetInfo().fY)
			{
				break;
			}
		}
	}
	//top
	for (int i = 1; i <= iBombRange; ++i)
	{
		CObj* pWater = CAbstractFactory<CWater>::Create(m_tInfo.fX, m_tInfo.fY - m_tInfo.fCY * i);
		CObjMgr::GetInstance()->AddObject(OBJ_WATER, pWater);
		if (i + 1 > iBombRange) break;
		for (auto& pBlock : CObjMgr::GetInstance()->GetList(OBJ_BLOCK))
		{
			if (m_tInfo.fX == pBlock->GetInfo().fX &&
				m_tInfo.fY - m_tInfo.fCY * (i + 1) == pBlock->GetInfo().fY)
			{
				break;
			}
		}
	}
	//bottom
	for (int i = 1; i <= iBombRange; ++i)
	{
		CObj* pWater = CAbstractFactory<CWater>::Create(m_tInfo.fX, m_tInfo.fY + m_tInfo.fCY * i);
		CObjMgr::GetInstance()->AddObject(OBJ_WATER, pWater);
		if (i + 1 > iBombRange) break;
		for (auto& pBlock : CObjMgr::GetInstance()->GetList(OBJ_BLOCK))
		{
			if (m_tInfo.fX == pBlock->GetInfo().fX &&
				m_tInfo.fY + m_tInfo.fCY * (i + 1) == pBlock->GetInfo().fY)
			{
				break;
			}
		}
	}
}
