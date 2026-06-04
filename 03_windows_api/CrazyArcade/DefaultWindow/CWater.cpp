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
	CBmpMgr::GetInstance()->InsertBmp(L"../Image/크레이지 아케이드 리소스/Resource/Bullet/BoomLeftEX.bmp", L"WaterLeft");
	CBmpMgr::GetInstance()->InsertBmp(L"../Image/크레이지 아케이드 리소스/Resource/Bullet/BoomUpEX.bmp", L"WaterUp");
	CBmpMgr::GetInstance()->InsertBmp(L"../Image/크레이지 아케이드 리소스/Resource/Bullet/BoomRightEX.bmp", L"WaterRight");
	CBmpMgr::GetInstance()->InsertBmp(L"../Image/크레이지 아케이드 리소스/Resource/Bullet/BoomDownEX.bmp", L"WaterDown");

	CBmpMgr::GetInstance()->InsertBmp(L"../Image/크레이지 아케이드 리소스/Resource/Bullet/BoomLeft.bmp", L"WaterLeftEnd");
	CBmpMgr::GetInstance()->InsertBmp(L"../Image/크레이지 아케이드 리소스/Resource/Bullet/BoomUp.bmp", L"WaterUpEnd");
	CBmpMgr::GetInstance()->InsertBmp(L"../Image/크레이지 아케이드 리소스/Resource/Bullet/BoomRight.bmp", L"WaterRightEnd");
	CBmpMgr::GetInstance()->InsertBmp(L"../Image/크레이지 아케이드 리소스/Resource/Bullet/BoomDown.bmp", L"WaterDownEnd");
}

int CWater::Update()
{
	if (m_bDead == DEAD)
		return DEAD;
	if (m_eDirection == DIR_END)
	{
		m_tRenderInfo = { 0,2,100,0,0 };
	}
	else
	{
		m_tRenderInfo = { 0,7,100,0,0 };
	}

	if (m_dwAniTime + m_tRenderInfo.dwFrameSpeed <= GetTickCount())
	{
		m_dwAniTime = GetTickCount();
		m_iFrame = (m_iFrame + 1) % m_tRenderInfo.iFrameEnd;
	}
	return NONEVENT;
}

void CWater::LateUpdate()
{
	if (m_dwTime + 500 <= GetTickCount())
		m_bDead = DEAD;
}

void CWater::Render(HDC hDC)
{
	HDC hMemDC = NULL;
	switch (m_eDirection)
	{
	case DIR_LEFT:
		hMemDC = CBmpMgr::GetInstance()->FindImage(L"WaterLeft");
		break;
	case DIR_UP:
		hMemDC = CBmpMgr::GetInstance()->FindImage(L"WaterUp");
		break;
	case DIR_RIGHT:
		hMemDC = CBmpMgr::GetInstance()->FindImage(L"WaterRight");
		break;
	case DIR_DOWN:
		hMemDC = CBmpMgr::GetInstance()->FindImage(L"WaterDown");
		break;

	case DIR_LEFTEND:
		hMemDC = CBmpMgr::GetInstance()->FindImage(L"WaterLeftEnd");
		break;
	case DIR_DOWNEND:
		hMemDC = CBmpMgr::GetInstance()->FindImage(L"WaterDownEnd");
		break;
	case DIR_RIGHTEND:
		hMemDC = CBmpMgr::GetInstance()->FindImage(L"WaterRightEnd");
		break;
	case DIR_UPEND:
		hMemDC = CBmpMgr::GetInstance()->FindImage(L"WaterUpEnd");
		break;
	case DIR_END:
		hMemDC = CBmpMgr::GetInstance()->FindImage(L"Water");
		break;
	default:
		break;
	}

	GdiTransparentBlt(hDC,
		m_tRect.left,
		m_tRect.top,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hMemDC,
		m_iFrame * m_tInfo.fCX,
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
	bool bRunning = true;
	for (int i = 1; i <= iBombRange; ++i)
	{
		if (bRunning == false) break;
		CObj* pWater = nullptr;
		if(i == iBombRange)
			pWater = CAbstractFactory<CWater>::Create(m_tInfo.fX + m_tInfo.fCX * i, m_tInfo.fY,DIR_RIGHTEND);
		else
			pWater = CAbstractFactory<CWater>::Create(m_tInfo.fX + m_tInfo.fCX * i, m_tInfo.fY, DIR_RIGHT);

		CObjMgr::GetInstance()->AddObject(OBJ_WATER, pWater);
		if (i + 1 > iBombRange) break;
		for (auto& pBlock : CObjMgr::GetInstance()->GetList(OBJ_BLOCK))
		{
			if (fabsf(pWater->GetInfo()->fX  - pBlock->GetInfo()->fX) <= 10.f &&
				fabsf(pWater->GetInfo()->fY - pBlock->GetInfo()->fY) <= 10.f)
			{
				bRunning = false;
				break;
			}
		}
	}
	//left
	bRunning = true;
	for (int i = 1; i <= iBombRange; ++i)
	{
		if (bRunning == false) break;

		CObj* pWater = nullptr;
		if (i == iBombRange)
			pWater = CAbstractFactory<CWater>::Create(m_tInfo.fX - m_tInfo.fCX * i, m_tInfo.fY, DIR_LEFTEND);
		else
			pWater = CAbstractFactory<CWater>::Create(m_tInfo.fX - m_tInfo.fCX * i, m_tInfo.fY, DIR_LEFT);

		CObjMgr::GetInstance()->AddObject(OBJ_WATER, pWater);
		if (i + 1 > iBombRange) break;
		for (auto& pBlock : CObjMgr::GetInstance()->GetList(OBJ_BLOCK))
		{
			if (fabsf(pWater->GetInfo()->fX - pBlock->GetInfo()->fX) <= 10.f &&
				fabsf(pWater->GetInfo()->fY - pBlock->GetInfo()->fY) <= 10.f)
			{
				bRunning = false;
				break;
			}
		}
	}
	//top
	bRunning = true;
	for (int i = 1; i <= iBombRange; ++i)
	{
		if (bRunning == false) break;
		CObj* pWater = nullptr;
		if (i == iBombRange)
			pWater = CAbstractFactory<CWater>::Create(m_tInfo.fX , m_tInfo.fY - m_tInfo.fCY * i, DIR_UPEND);
		else
			pWater = CAbstractFactory<CWater>::Create(m_tInfo.fX , m_tInfo.fY - m_tInfo.fCY * i, DIR_UP);

		CObjMgr::GetInstance()->AddObject(OBJ_WATER, pWater);
		if (i + 1 > iBombRange) break;
		for (auto& pBlock : CObjMgr::GetInstance()->GetList(OBJ_BLOCK))
		{
			if (fabsf(pWater->GetInfo()->fX - pBlock->GetInfo()->fX) <= 10.f &&
				fabsf(pWater->GetInfo()->fY - pBlock->GetInfo()->fY) <= 10.f)
			{
				bRunning = false;
				break;
			}
		}
	}
	//bottom
	bRunning = true;
	for (int i = 1; i <= iBombRange; ++i)
	{
		if (bRunning == false) break;
		CObj* pWater = nullptr;
		if (i == iBombRange)
			pWater = CAbstractFactory<CWater>::Create(m_tInfo.fX , m_tInfo.fY + m_tInfo.fCY * i, DIR_DOWNEND);
		else
			pWater = CAbstractFactory<CWater>::Create(m_tInfo.fX , m_tInfo.fY + m_tInfo.fCY * i, DIR_DOWN);
		CObjMgr::GetInstance()->AddObject(OBJ_WATER, pWater);
		if (i + 1 > iBombRange) break;
		for (auto& pBlock : CObjMgr::GetInstance()->GetList(OBJ_BLOCK))
		{
			if (fabsf(pWater->GetInfo()->fX - pBlock->GetInfo()->fX) <= 10.f &&
				fabsf(pWater->GetInfo()->fY - pBlock->GetInfo()->fY) <= 10.f)
			{
				bRunning = false;
				break;
			}
		}
	}
}
