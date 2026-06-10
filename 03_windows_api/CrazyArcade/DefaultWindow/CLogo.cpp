#include "pch.h"
#include "CLogo.h"
#include "CImgMgr.h"
#include "CSceneMgr.h"

CLogo::CLogo():m_fAlpha(1.f), m_dwTime(GetTickCount64())
{
}

CLogo::~CLogo()
{
	Release();
}

void CLogo::Initialize()
{
	CImgMgr::GetInstance()->InsertImg(L"../Resource/BackGround/Logo.png", L"Logo");
	CImgMgr::GetInstance()->InsertImg(L"../Resource/BackGround/black_bg.png", L"black_bg");
}

int CLogo::Update()
{
	if (m_fAlpha > 0.f && m_dwTime + 10 <= GetTickCount64())
	{
		m_dwTime = GetTickCount64();
		m_fAlpha -= 0.01f;
	}
	else
	{
		CSceneMgr::GetInstance()->SceneChangeReserve(SC_STAGE3);
	}
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
