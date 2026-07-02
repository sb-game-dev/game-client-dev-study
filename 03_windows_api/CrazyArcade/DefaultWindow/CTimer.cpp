#include "pch.h"
#include "CTimer.h"
#include "CBmpMgr.h"
#include "CObjMgr.h"
CTimer* CTimer::m_pInstance = nullptr;


CTimer::CTimer()
{
	m_dwTimer = GetTickCount64();
	m_iSec = 180;
}

CTimer::~CTimer()
{
}
void CTimer::Initialize()
{
	m_dwTimer = GetTickCount64();
	m_iSec = 180;
}
void CTimer::Update()
{
	if (m_iSec < 0)
		return;
	if ((CObjMgr::GetInstance()->GetRemainPlayer() == false && CObjMgr::GetInstance()->GetRemainPlayer2() == false))
		return;
	if (m_dwTimer + 1000 <= GetTickCount64())
	{
		m_dwTimer = GetTickCount64();
		--m_iSec;
	}
}
void CTimer::Render(HDC hDC)
{
	if (m_iSec < 0)
		return;
	HDC hTimer = CBmpMgr::GetInstance()->FindImage(L"Time");
	GdiTransparentBlt(hDC, 666, 77, 39, 10, hTimer, 0, 0, 39, 10, RGB(255, 0, 255));

	HDC hDot = CBmpMgr::GetInstance()->FindImage(L"Dot");
	GdiTransparentBlt(hDC, 738, 78, 4, 10, hDot, 0, 0, 4, 10, RGB(255, 0, 255));

	HDC hNumber = CBmpMgr::GetInstance()->FindImage(L"TimerNumbers");
	int iMinut = m_iSec / 60;
	int iSec = m_iSec % 60;

	int iNumcnt = 0;
	if (iMinut == 0)
	{
		GdiTransparentBlt(hDC, 725 - 12 * 0, 78, 12, 11, hNumber, 12 * 0, 0, 12, 11, RGB(255, 0, 255));
		GdiTransparentBlt(hDC, 725 - 12 * 1, 78, 12, 11, hNumber, 12 * 0, 0, 12, 11, RGB(255, 0, 255));
	}
	else
	{
		while (iMinut)
		{
			if (iMinut < 10)
			{
				GdiTransparentBlt(hDC, 725 - 12 * 1, 78, 12, 11, hNumber, 12 * 0, 0, 12, 11, RGB(255, 0, 255));
			}
			int iNum = iMinut % 10;
			GdiTransparentBlt(hDC, 725 - 12 * iNumcnt, 78, 12, 11, hNumber, 12 * iNum, 0, 12, 11, RGB(255, 0, 255));
			++iNumcnt;
			iMinut /= 10;
		}
	}

	if (iSec == 0)
	{
		GdiTransparentBlt(hDC, 757 - 12 * 0, 78, 12, 11, hNumber, 12 * 0, 0, 12, 11, RGB(255, 0, 255));
		GdiTransparentBlt(hDC, 757 - 12 * 1, 78, 12, 11, hNumber, 12 * 0, 0, 12, 11, RGB(255, 0, 255));
	}
	else
	{
		iNumcnt = 0;
		while (iSec)
		{
			if (iSec < 10)
			{
				GdiTransparentBlt(hDC, 757 - 12 * 1, 78, 12, 11, hNumber, 12 * 0, 0, 12, 11, RGB(255, 0, 255));
			}
			int iNum = iSec % 10;
			GdiTransparentBlt(hDC, 757 - 12 * iNumcnt, 78, 12, 11, hNumber, 12 * iNum, 0, 12, 11, RGB(255, 0, 255));
			++iNumcnt;
			iSec /= 10;
		}
	}
}