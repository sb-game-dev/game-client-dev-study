#include "pch.h"
#include "CMenu.h"
#include "CImgMgr.h"
#include "CBmpMgr.h"
#include "CObjMgr.h"
#include "CButton.h"
#include "CAbstractFactory.h"
#include "CSoundMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CInven.h"
#include "CNotice.h"
#include "CSelectPlayer.h"

CMenu::CMenu():m_pButtonList(nullptr), m_pSelectStage(nullptr)
{
}

CMenu::~CMenu()
{
	Release();
}

void CMenu::Initialize()
{
	CObjMgr::GetInstance()->AddObject(OBJ_BUTTON, CAbstractFactory<CButton>::Create(722, 36, L"button_creator"));
	CObjMgr::GetInstance()->AddObject(OBJ_BUTTON, CAbstractFactory<CButton>::Create(508, 347, L"button_stageStart"));
	CObjMgr::GetInstance()->AddObject(OBJ_BUTTON, CAbstractFactory<CButton>::Create(338, 225, L"button_FirstStage"));
	CObjMgr::GetInstance()->AddObject(OBJ_BUTTON, CAbstractFactory<CButton>::Create(509, 225, L"button_SecondStage"));
	CObjMgr::GetInstance()->AddObject(OBJ_BUTTON, CAbstractFactory<CButton>::Create(679.5, 225, L"button_ThirdStage"));

	CObjMgr::GetInstance()->AddObject(OBJ_BUTTON, CAbstractFactory<CButton>::Create(176, 585, L"button_shop"));
	CObjMgr::GetInstance()->AddObject(OBJ_BUTTON, CAbstractFactory<CButton>::Create(662, 584, L"button_myPage"));

	CObjMgr::GetInstance()->AddObject(OBJ_BUTTON, CAbstractFactory<CButton>::Create(765, 584, L"button_exit"));


	m_pButtonList = CObjMgr::GetInstance()->GetListPtr(OBJ_BUTTON);


	CSoundMgr::Get_Instance()->PlayBGM(L"Channel.wav", 0.1f);

		
}

int CMenu::Update()
{
	CObjMgr::GetInstance()->Update();
	return 0;
}

void CMenu::LateUpdate()
{
	if (CInven::GetInstance()->GetDraw())
	{
		CInven::GetInstance()->LateUpdate();
	}
	else if (CNotice::GetInstance()->GetDraw())
	{
		CNotice::GetInstance()->LateUpdate();
	}
	else if (CSelectPlayer::GetInstance()->GetDraw())
	{
		CSelectPlayer::GetInstance()->LateUpdate();
	}
	else
	{
		POINT		ptMouse{};
		GetCursorPos(&ptMouse);
		ScreenToClient(g_hWnd, &ptMouse);
		for (auto& pButton : *m_pButtonList)
		{
			if (PtInRect(pButton->GetRect(), ptMouse) && CKeyMgr::GetInstance()->KeyDown(VK_LBUTTON))
			{
				if (!lstrcmp(L"button_FirstStage", pButton->GetFrameKey()) || 
					!lstrcmp(L"button_SecondStage", pButton->GetFrameKey()) || 
					!lstrcmp(L"button_ThirdStage", pButton->GetFrameKey()))
				{
					m_pSelectStage = pButton;
					pButton->SetStartFrame(1);
				}
				else if (!lstrcmp(L"button_stageStart", pButton->GetFrameKey()))
				{
					if (*CSceneMgr::GetInstance()->GetPlayModePtr() == MODE1P &&
						(!lstrcmp(L"button_SecondStage", m_pSelectStage->GetFrameKey()) ||
							!lstrcmp(L"button_ThirdStage", m_pSelectStage->GetFrameKey())))
					{
						m_eCurSceneState = SCENE_PLAY;
						CSoundMgr::Get_Instance()->PlaySound(L"ban.wav", BUTTON_CURSOR, 0.9f);
					}
					else
						m_eCurSceneState = SCENE_END;
				}
			}
			if ((!lstrcmp(L"button_FirstStage", pButton->GetFrameKey()) || 
				!lstrcmp(L"button_SecondStage", pButton->GetFrameKey()) || 
				!lstrcmp(L"button_ThirdStage", pButton->GetFrameKey())) 
				&&	pButton != m_pSelectStage)
			{
				pButton->SetStartFrame(0);
			}
		}

		CObjMgr::GetInstance()->LateUpdate();
	}
	if (m_eCurSceneState == SCENE_START || m_eCurSceneState == SCENE_END)
	{
		if (m_eCurSceneState == SCENE_START && m_fAlpha > 0.f && m_dwFrameTime + 10 <= GetTickCount64())
		{
			m_dwFrameTime = GetTickCount64();
			m_fAlpha -= 0.015f;
		}
		else if (m_eCurSceneState == SCENE_END && m_fAlpha < 1.f && m_dwFrameTime + 10 <= GetTickCount64())
		{
			m_dwFrameTime = GetTickCount64();
			m_fAlpha += 0.03f;
		}
		CheckSceneFrame();
	}
}

void CMenu::Render(HDC hDC)
{
	HDC hBackGround = CBmpMgr::GetInstance()->FindImage(L"menu_background");
	BitBlt(hDC,							// 목적지 DC
		0, 0,
		WINCX, WINCY,
		hBackGround,					// 원본 DC
		0,								// 원본 이미지에서 가져오기 시작할 좌표의 LEFT, TOP
		0,
		SRCCOPY);						// 그대로 복사하여 출력
	
	CObjMgr::GetInstance()->Render(hDC);
	if (CInven::GetInstance()->GetDraw())
	{
		CInven::GetInstance()->Render(hDC);
		CObjMgr::GetInstance()->GetList(OBJ_MOUSE).front()->Render(hDC);
	}

	if (CNotice::GetInstance()->GetDraw())
	{
		CNotice::GetInstance()->Render(hDC);
		CObjMgr::GetInstance()->GetList(OBJ_MOUSE).front()->Render(hDC);
	}

	if (CSelectPlayer::GetInstance()->GetDraw())
	{
		CSelectPlayer::GetInstance()->Render(hDC);
		CObjMgr::GetInstance()->GetList(OBJ_MOUSE).front()->Render(hDC);
	}

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

void CMenu::Release()
{
	CInven::GetInstance()->SetDraw(false);
	CNotice::GetInstance()->SetDraw(false);
	CObjMgr::GetInstance()->ReleaseRenderList();
	CObjMgr::GetInstance()->DeleteObj(OBJ_BUTTON);
	CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
}

void CMenu::CheckSceneFrame()
{
	if (m_eCurSceneState == SCENE_START && m_fAlpha < 0.f)
	{
		m_eCurSceneState = SCENE_PLAY;
	}
	else if (m_eCurSceneState == SCENE_END && m_fAlpha >= 1.f)
	{
		if (m_pSelectStage && !lstrcmp(L"button_FirstStage", m_pSelectStage->GetFrameKey()))
			CSceneMgr::GetInstance()->SceneChangeReserve(SC_STAGE1);
		else if (m_pSelectStage && !lstrcmp(L"button_SecondStage", m_pSelectStage->GetFrameKey()))
			CSceneMgr::GetInstance()->SceneChangeReserve(SC_STAGE4);
		else if (m_pSelectStage && !lstrcmp(L"button_ThirdStage", m_pSelectStage->GetFrameKey()))
			CSceneMgr::GetInstance()->SceneChangeReserve(SC_STAGE5);
	}
}