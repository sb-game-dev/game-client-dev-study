#include "pch.h"
#include "CLogo.h"
#include "CImgMgr.h"
#include "CSceneMgr.h"
#include "CSoundMgr.h"

CLogo::CLogo():m_dwTime(GetTickCount64())
{
}

CLogo::~CLogo()
{
	Release();
}

void CLogo::Initialize()
{
}

int CLogo::Update()
{
	if (m_fAlpha > 0 && m_dwTime + 10 <= GetTickCount64())
	{
		m_dwTime = GetTickCount64();
		m_fAlpha -= 0.01f;
	}
	else
	{
		CSceneMgr::GetInstance()->SceneChangeReserve(SC_MENU);
	}

	// cout << m_fAlpha << endl;
	//if (m_bStartScene && m_dwTime + 10 <= GetTickCount64())
	//{
	//	m_dwTime = GetTickCount64();
	//	m_fAlpha -= 0.01f;
	//}
	//if (m_bEndScene && m_dwTime + 10 <= GetTickCount64())
	//{
	//	m_dwTime = GetTickCount64();
	//	m_fAlpha += 0.01f;
	//}
	//else
	//{
	//	CSceneMgr::GetInstance()->SceneChangeReserve(SC_MENU);
	//}
	//
	//
	//if (m_fAlpha < 0)
	//{
	//	m_bStartScene = false;
	//	m_bEndScene = true;
	//}
	//if (m_fAlpha > 1)
	//{
	//	m_bEndScene = false;
	//}
	
    return 0;
}

void CLogo::LateUpdate()
{
}

void CLogo::Render(HDC hDC)
{
	Graphics* _pGraphics = Graphics::FromHDC(hDC);
	Gdiplus::Image* pBlackImg = CImgMgr::GetInstance()->FindImg(L"black_bg");
	Gdiplus::Image* pImg = CImgMgr::GetInstance()->FindImg(L"Logo");

	Rect rect = { 0,0,800,600 };

	ImageAttributes attr;
	MakeAlphaAttr(attr, m_fAlpha);
	_pGraphics->DrawImage(pImg, rect, 0, 0, WINCX, WINCY, UnitPixel);
	_pGraphics->DrawImage(pBlackImg, rect, 0, 0, WINCX, WINCY, UnitPixel, & attr);
}

void CLogo::Release()
{
}

