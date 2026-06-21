#include "pch.h"
#include "CLogo.h"
#include "CImgMgr.h"
#include "CSceneMgr.h"
#include "CSoundMgr.h"

CLogo::CLogo()
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
	if (m_eCurSceneState == SCENE_START && m_fAlpha > 0.f && m_dwFrameTime + 10 <= GetTickCount64())
	{
		m_dwFrameTime = GetTickCount64();
		m_fAlpha -= 0.01f;
	}
	if (m_eCurSceneState == SCENE_END && m_fAlpha < 1.f && m_dwFrameTime + 10 <= GetTickCount64())
	{
		m_dwFrameTime = GetTickCount64();
		m_fAlpha += 0.01f;
	}
	CheckSceneFrame();
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

void CLogo::CheckSceneFrame()
{
	if (m_eCurSceneState == SCENE_START	&& m_fAlpha < 0.f)
	{
		m_eCurSceneState = SCENE_END;
		//ChangeScene();
	}
	else if (m_eCurSceneState == SCENE_END && m_fAlpha >= 1.f)
	{
		CSceneMgr::GetInstance()->SceneChangeReserve(SC_MENU);
	}
}

void CLogo::ChangeScene()
{
	if (m_ePreSceneState == m_eCurSceneState)
		return;
	switch (m_eCurSceneState)
	{
	case SCENE_START:
		m_dwFrameTime = GetTickCount64();
		break;
	case SCENE_END:
		m_dwFrameTime = GetTickCount64();
		break;
	default:
		break;
	}
	m_ePreSceneState = m_eCurSceneState;
}

