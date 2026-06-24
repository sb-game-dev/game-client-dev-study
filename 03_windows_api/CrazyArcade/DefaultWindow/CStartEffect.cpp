#include "pch.h"
#include "CStartEffect.h"
#include "CBmpMgr.h"

CStartEffect* CStartEffect::m_pInstance = nullptr;

CStartEffect::CStartEffect()
{
	m_fTop1 = 245.f;
	m_fTop2 = 245.f;
	m_fTop3 = 245.f;
	m_fTop4 = 245.f;
	m_fTop5 = 245.f;
	m_fTop6 = 245.f;
	m_fTop7 = 245.f;

	m_bEffectRunning = true;

	m_fSpeed = 100.f;
}

CStartEffect::~CStartEffect()
{
}


void CStartEffect::Update()
{
	if (m_bEffectRunning == false)
		return;
	//cout << m_fCnt << endl;
	m_fCnt += 0.1f;
	if (m_fCnt >= 1)
	{
		m_fTop1 -= m_fSpeed;
	}
	if (m_fCnt >= 3)
	{
		m_fTop2 -= m_fSpeed;
	}
	if (m_fCnt >= 5)
	{
		m_fTop3 -= m_fSpeed;
	}
	if (m_fCnt >= 7)
	{
		m_fTop4 -= m_fSpeed;
	}
	if (m_fCnt >= 9)
	{
		m_fTop5 -= m_fSpeed;
	}
	if (m_fCnt >= 11)
	{
		m_fTop6 -= m_fSpeed;
	}
	if (m_fCnt >= 13)
	{
		m_fTop7 -= m_fSpeed;
	}
	if(m_fTop7 < 0)
		m_bEffectRunning = false;
}
void CStartEffect::Render(HDC hDC)
{
	if (m_bEffectRunning == false)
		return;
	HDC hObj2 = CBmpMgr::GetInstance()->FindImage(L"game_start_t");
	if (m_fTop1 > 0)
	{
		HDC hObj1 = CBmpMgr::GetInstance()->FindImage(L"game_start_s");
		GdiTransparentBlt(hDC, 139, m_fTop1, 85, 77, hObj1, 0, 0, 85, 77, RGB(255, 0, 255));
	}
	if (m_fTop2 > 0)
	{
		GdiTransparentBlt(hDC, 139 + 69, m_fTop2, 84, 77, hObj2, 0, 0, 84, 77, RGB(255, 0, 255));
	}
	if (m_fTop3 > 0)
	{
		HDC hObj3 = CBmpMgr::GetInstance()->FindImage(L"game_start_a");
		GdiTransparentBlt(hDC, 139 + 132, m_fTop3, 97, 77, hObj3, 0, 0, 97, 77, RGB(255, 0, 255));
	}
	if (m_fTop4 > 0)
	{
		HDC hObj4 = CBmpMgr::GetInstance()->FindImage(L"game_start_r");
		GdiTransparentBlt(hDC, 139 + 232, m_fTop4, 90, 77, hObj4, 0, 0, 90, 77, RGB(255, 0, 255));
	}
	if (m_fTop5 > 0)
	{
		GdiTransparentBlt(hDC, 139 + 322, m_fTop5, 84, 77, hObj2, 0, 0, 84, 77, RGB(255, 0, 255));
	}
	HDC hObj6 = CBmpMgr::GetInstance()->FindImage(L"game_start_mark");
	if (m_fTop6 > 0)
	{
		GdiTransparentBlt(hDC, 139 + 406, m_fTop6, 34, 77, hObj6, 0, 0, 34, 77, RGB(255, 0, 255));
	}
	if (m_fTop7 > 0)
	{
		GdiTransparentBlt(hDC, 139 + 443, m_fTop7, 34, 77, hObj6, 0, 0, 34, 77, RGB(255, 0, 255));
	}
}