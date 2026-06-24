#include "pch.h"
#include "CLogin.h"
#include "CSceneMgr.h"
#include "CImgMgr.h"
#include "CBmpMgr.h"
#include "CObjMgr.h"
#include "CButton.h"
#include "CAbstractFactory.h"
#include "CKeyMgr.h"
#include "CSoundMgr.h"

CLogin::CLogin() :m_pButton2p(nullptr), m_pButton1p(nullptr), m_bShow2pControls(false), m_bClickButton2P(false)
{
}

CLogin::~CLogin()
{
	Release();
}

void CLogin::Initialize()
{
	m_pButton2p = CAbstractFactory<CButton>::Create(612.5, 472, L"Login_2P");
	CObjMgr::GetInstance()->AddObject(OBJ_BUTTON, m_pButton2p);
	m_pButton1p = CAbstractFactory<CButton>::Create(191.5, 472, L"Login_1P");
	CObjMgr::GetInstance()->AddObject(OBJ_BUTTON, m_pButton1p);

	CSoundMgr::Get_Instance()->PlayBGM(L"Lobby.wav", 0.1f);
}

int CLogin::Update()
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
	CObjMgr::GetInstance()->Update();
	return 0;
}

void CLogin::LateUpdate()
{
	POINT		ptMouse{};
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);

	if (PtInRect(m_pButton2p->GetRect(), ptMouse))
	{
		m_bShow2pControls = true;
		if (CKeyMgr::GetInstance()->KeyDown(VK_LBUTTON))
		{
			CSceneMgr::GetInstance()->SetPlayMode(MODE2P);
			m_eCurSceneState = SCENE_END;
			m_bClickButton2P = true;
		}
	}
	else
	{
		m_bShow2pControls = false;
	}

	if (PtInRect(m_pButton1p->GetRect(), ptMouse))
	{
		if (CKeyMgr::GetInstance()->KeyDown(VK_LBUTTON))
		{
			CSceneMgr::GetInstance()->SetPlayMode(MODE1P);
			m_eCurSceneState = SCENE_END;
		}
	}
	if (m_bClickButton2P)
		m_bShow2pControls = true;
	CObjMgr::GetInstance()->LateUpdate();
}

void CLogin::Render(HDC hDC)
{
	HDC hLogin = CBmpMgr::GetInstance()->FindImage(L"LogIn");
	BitBlt(hDC, 0, 0, WINCX, WINCY, hLogin, 0, 0, SRCCOPY);
	if (m_bShow2pControls)
	{
		HDC h2pControls = CBmpMgr::GetInstance()->FindImage(L"Control_2P");
		BitBlt(hDC, 172, 94, 461, 297, h2pControls, 0, 0, SRCCOPY);
	}

	CObjMgr::GetInstance()->Render(hDC);

	if (m_eCurSceneState == SCENE_START || m_eCurSceneState == SCENE_END)
	{
		Graphics* _pGraphics = Graphics::FromHDC(hDC);
		Gdiplus::Image* pBlackImg = CImgMgr::GetInstance()->FindImg(L"black_bg");

		Rect rect = { 0,0,800,600 };

		ImageAttributes attr;
		MakeAlphaAttr(attr, m_fAlpha);
		_pGraphics->DrawImage(pBlackImg, rect, 0, 0, WINCX, WINCY, UnitPixel, &attr);
	}
}

void CLogin::Release()
{
	CObjMgr::GetInstance()->DeleteObj(OBJ_BUTTON);
	CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
}

void CLogin::CheckSceneFrame()
{
	if (m_eCurSceneState == SCENE_START && m_fAlpha < 0.f)
	{
		m_eCurSceneState = SCENE_PLAY;
	}
	else if (m_eCurSceneState == SCENE_END && m_fAlpha >= 1.f)
	{
		m_bShow2pControls = true;
		CSceneMgr::GetInstance()->SceneChangeReserve(SC_MENU);		
	}
}

void CLogin::ChangeScene()
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
