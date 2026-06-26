#include "pch.h"
#include "CStage3.h"
#include "CObjMgr.h"
#include "CAbstractFactory.h"
#include "CImgMgr.h"
#include "CBoss.h"
#include "CBmpMgr.h"
#include "CItem.h"
#include "CSceneMgr.h"
#include "CSoundMgr.h"
#include "CMonster.h"
#include "CButton.h"
#include "CInven.h"
#include "CPlayer2.h"
#include "CStartEffect.h"
#include "CInven2.h"
CStage3::CStage3() :m_pPlayer(nullptr), m_pPlayer2(nullptr), m_pPlayMode(nullptr)
{
}

CStage3::~CStage3()
{
	Release();
}

void CStage3::Initialize()
{
#ifdef _DEBUG
	CObjMgr::GetInstance()->AddObject(OBJ_ITEM, CAbstractFactory<CItem>::Create((0 * 40) + 40, (1 * 40) + 60, L"bubble"));
	CObjMgr::GetInstance()->AddObject(OBJ_ITEM, CAbstractFactory<CItem>::Create((1 * 40) + 40, (1 * 40) + 60, L"dart"));
	CObjMgr::GetInstance()->AddObject(OBJ_ITEM, CAbstractFactory<CItem>::Create((2 * 40) + 40, (1 * 40) + 60, L"needle"));
	CObjMgr::GetInstance()->AddObject(OBJ_ITEM, CAbstractFactory<CItem>::Create((3 * 40) + 40, (1 * 40) + 60, L"roller"));
	CObjMgr::GetInstance()->AddObject(OBJ_ITEM, CAbstractFactory<CItem>::Create((10 * 40) + 40, (1 * 40) + 60, L"shield"));
	CObjMgr::GetInstance()->AddObject(OBJ_ITEM, CAbstractFactory<CItem>::Create((11 * 40) + 40, (1 * 40) + 60, L"shoe"));
#endif // _DEBUG

	m_pPlayer = CAbstractFactory<CPlayer>::Create((13 * 40) + 40, (11 * 40) + 60, L"player_start");
	CObjMgr::GetInstance()->AddObject(OBJ_PLAYER, m_pPlayer);

	m_pPlayMode = CSceneMgr::GetInstance()->GetPlayModePtr();

#ifdef _DEBUG
	* m_pPlayMode = MODE2P;
#endif // _DEBUG

	if (*m_pPlayMode == MODE2P)
	{
		int iPlayer2_StartX = 13;
		int iPlayer2_StartY = 1;
		m_pPlayer2 = CAbstractFactory<CPlayer2>::Create((iPlayer2_StartX * 40) + 40, (iPlayer2_StartY * 40) + 60, L"player_start2");
		CObjMgr::GetInstance()->AddObject(OBJ_PLAYER2, m_pPlayer2);
	}

	CObjMgr::GetInstance()->AddObject(OBJ_BOSS, CAbstractFactory<CBoss>::Create((3 * 40) + 40, (10 * 40) + 60, L"Boss_down"));

	CObjMgr::GetInstance()->AddObject(OBJ_BUTTON, CAbstractFactory<CButton>::Create(717, 576, L"button_stageExit"));
	CObjMgr::GetInstance()->AddObject(OBJ_MONSTER, CAbstractFactory<CMonster>::Create((12 * 40) + 40, (7 * 40) + 60, L"Bean_Monster_Start"));

	CObjMgr::GetInstance()->LoadStage3();
	CStartEffect::GetInstance()->Initialize();
	CSoundMgr::Get_Instance()->PlaySound(L"StageStart_7.wav", STAGE_START, 0.1f);
}

int CStage3::Update()
{
	CObjMgr::GetInstance()->Update();
	CStartEffect::GetInstance()->Update();
	if (CObjMgr::GetInstance()->GetRemainBoss() == false)
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
		m_eCurSceneState = SCENE_WIN;
		if (dynamic_cast<CPlayer*>(m_pPlayer))
			dynamic_cast<CPlayer*>(m_pPlayer)->SetWin();
		if (dynamic_cast<CPlayer2*>(m_pPlayer2))
			dynamic_cast<CPlayer2*>(m_pPlayer2)->SetWin();
		ChangeScene();
	}
	else if (CObjMgr::GetInstance()->GetRemainPlayer() == false && CObjMgr::GetInstance()->GetRemainPlayer2() == false)
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
		m_eCurSceneState = SCENE_LOSE;
		ChangeScene();
	}

	return 0;
}

void CStage3::LateUpdate()
{
	CObjMgr::GetInstance()->LateUpdate();
	if (m_eCurSceneState == SCENE_START || m_eCurSceneState == SCENE_WIN)
	{
		if (m_eCurSceneState == SCENE_START && m_fAlpha > 0.f && m_dwFrameTime + 10 <= GetTickCount64())
		{
			m_dwFrameTime = GetTickCount64();
			m_fAlpha -= 0.015f;
		}
		else if (m_eCurSceneState == SCENE_WIN && m_fAlpha < 1.f && m_dwFrameTime + 10 <= GetTickCount64())
		{
			m_dwFrameTime = GetTickCount64();
			m_fAlpha += 0.008f;
		}
		CheckSceneFrame();
	}
}

void CStage3::Render(HDC hDC)
{
	HDC hBackGround = CBmpMgr::GetInstance()->FindImage(L"stage_background");

	BitBlt(hDC,							// 목적지 DC
		0,0,
		WINCX,WINCY,
		hBackGround,					// 원본 DC
		0,								// 원본 이미지에서 가져오기 시작할 좌표의 LEFT, TOP
		0,
		SRCCOPY);						// 그대로 복사하여 출력

	CObjMgr::GetInstance()->Render(hDC); 
	if (*CSceneMgr::GetInstance()->GetPlayModePtr() == MODE1P)
	{
		int iItemCnt = 0;
		for (auto& pitem : *(CInven2::GetInstance()->GetItemSlotPtr()))
		{
			switch (pitem->GetFrame().iStart)
			{
			case 0:
				++iItemCnt;
				continue;
			case 1:
				if (CInven2::GetInstance()->GetInven().iNeedleCnt <= 0)
				{
					++iItemCnt;
					continue;
				}
				break;
			case 2:
				if (CInven2::GetInstance()->GetInven().iDartCnt <= 0)
				{
					++iItemCnt;
					continue;
				}
				break;
			case 3:
				if (CInven2::GetInstance()->GetInven().iShieldCnt <= 0)
				{
					++iItemCnt;
					continue;
				}
				break;
			default:
				break;
			}
			HDC hSlotNum = CBmpMgr::GetInstance()->FindImage(L"InGameNumber");

			BitBlt(hDC,							// 목적지 DC
				243 + 40 * iItemCnt,
				568,
				13, 11,
				hSlotNum,						// 원본 DC
				13 * iItemCnt,					// 원본 이미지에서 가져오기 시작할 좌표의 LEFT, TOP
				0,
				SRCCOPY);						// 그대로 복사하여 출력

			HDC hSlotItem = CBmpMgr::GetInstance()->FindImage(L"InGameSlot");
			GdiTransparentBlt(hDC,						// 목적지 DC
				243 + 40 * iItemCnt,						// 목적지 LEFT, TOP
				568,
				37,										// 목적지 공간의 가로, 세로 사이즈
				29,
				hSlotItem,								// 원본 이미지 DC
				37 * (pitem->GetFrame().iStart - 1),	// 원본 이미지 LEFT, TOP
				0,
				37,										// 원본 이미지 가로, 세로 사이즈
				29,
				RGB(255, 0, 255));						// 제거할 픽셀 색상
			++iItemCnt;
		}
	}
	else
	{
		int iItemCnt = 0;
		for (auto& pitem : *(CInven::GetInstance()->GetItemSlotPtr()))
		{
			switch (pitem->GetFrame().iStart)
			{
			case 0:
				++iItemCnt;
				continue;
			case 1:
				if (CInven::GetInstance()->GetInven().iNeedleCnt <= 0)
				{
					++iItemCnt;
					continue;
				}
				break;
			case 2:
				if (CInven::GetInstance()->GetInven().iDartCnt <= 0)
				{
					++iItemCnt;
					continue;
				}
				break;
			case 3:
				if (CInven::GetInstance()->GetInven().iShieldCnt <= 0)
				{
					++iItemCnt;
					continue;
				}
				break;
			default:
				break;
			}

			HDC hSlotItem = CBmpMgr::GetInstance()->FindImage(L"InGameSlot");
			GdiTransparentBlt(hDC,						// 목적지 DC
				68 + 40 * iItemCnt,						// 목적지 LEFT, TOP
				568,
				37,										// 목적지 공간의 가로, 세로 사이즈
				29,
				hSlotItem,								// 원본 이미지 DC
				37 * (pitem->GetFrame().iStart - 1),	// 원본 이미지 LEFT, TOP
				0,
				37,										// 원본 이미지 가로, 세로 사이즈
				29,
				RGB(255, 0, 255));						// 제거할 픽셀 색상


			HDC hSlotNum = CBmpMgr::GetInstance()->FindImage(L"InGameNumber");

			BitBlt(hDC,							// 목적지 DC
				68 + 40 * iItemCnt,
				568,
				13, 10,
				hSlotNum,						// 원본 DC
				13 * iItemCnt,					// 원본 이미지에서 가져오기 시작할 좌표의 LEFT, TOP
				0,
				SRCCOPY);						// 그대로 복사하여 출력

			++iItemCnt;
		}
		iItemCnt = 0;
		for (auto& pitem : *(CInven2::GetInstance()->GetItemSlotPtr()))
		{
			switch (pitem->GetFrame().iStart)
			{
			case 0:
				++iItemCnt;
				continue;
			case 1:
				if (CInven2::GetInstance()->GetInven().iNeedleCnt <= 0)
				{
					++iItemCnt;
					continue;
				}
				break;
			case 2:
				if (CInven2::GetInstance()->GetInven().iDartCnt <= 0)
				{
					++iItemCnt;
					continue;
				}
				break;
			case 3:
				if (CInven2::GetInstance()->GetInven().iShieldCnt <= 0)
				{
					++iItemCnt;
					continue;
				}
				break;
			default:
				break;
			}

			HDC hSlotItem = CBmpMgr::GetInstance()->FindImage(L"InGameSlot");
			GdiTransparentBlt(hDC,						// 목적지 DC
				335 + 40 * iItemCnt,						// 목적지 LEFT, TOP
				568,
				37,										// 목적지 공간의 가로, 세로 사이즈
				29,
				hSlotItem,								// 원본 이미지 DC
				37 * (pitem->GetFrame().iStart - 1),	// 원본 이미지 LEFT, TOP
				0,
				37,										// 원본 이미지 가로, 세로 사이즈
				29,
				RGB(255, 0, 255));						// 제거할 픽셀 색상

			HDC hSlotNum = CBmpMgr::GetInstance()->FindImage(L"InGameNumber2");

			BitBlt(hDC,							// 목적지 DC
				335 + 40 * iItemCnt,
				568,
				37, 11,
				hSlotNum,						// 원본 DC
				37 * iItemCnt,					// 원본 이미지에서 가져오기 시작할 좌표의 LEFT, TOP
				0,
				SRCCOPY);						// 그대로 복사하여 출력
			++iItemCnt;
		}
	}
	if (m_eCurSceneState == SCENE_START)
	{
		Graphics* _pGraphics = Graphics::FromHDC(hDC);
		Gdiplus::Image* pBlackImg = CImgMgr::GetInstance()->FindImg(L"black_bg");

		Rect rect = { 0,0,800,600 };

		ImageAttributes attr;
		MakeAlphaAttr(attr, m_fAlpha);
		_pGraphics->DrawImage(pBlackImg, rect, 0, 0, WINCX, WINCY, UnitPixel, &attr);
	}
	CObjMgr::GetInstance()->GetList(OBJ_MOUSE).front()->Render(hDC);
	CStartEffect::GetInstance()->Render(hDC);
}

void CStage3::Release()
{
	CObjMgr::GetInstance()->ReleaseRenderList();
	CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
	CObjMgr::GetInstance()->DeleteObj(OBJ_PLAYER);
	CObjMgr::GetInstance()->DeleteObj(OBJ_PLAYER2);
	CObjMgr::GetInstance()->DeleteObj(OBJ_BOMB);
	CObjMgr::GetInstance()->DeleteObj(OBJ_WAVE);
	CObjMgr::GetInstance()->DeleteObj(OBJ_BUTTON);
	CObjMgr::GetInstance()->DeleteObj(OBJ_MONSTER);
	CObjMgr::GetInstance()->DeleteObj(OBJ_BOSS);
	CObjMgr::GetInstance()->DeleteObj(OBJ_ITEM);
	CObjMgr::GetInstance()->DeleteTile();
}


void CStage3::CheckSceneFrame()
{
	if (m_eCurSceneState == SCENE_START && m_fAlpha < 0.f)
	{
		m_eCurSceneState = SCENE_PLAY;
		CSoundMgr::Get_Instance()->PlayBGM(L"BossBGM.wav", 0.1f);
	}
	else if (m_eCurSceneState == SCENE_END && m_fAlpha >= 1.f)
	{
	}
}

void CStage3::ChangeScene()
{
	if (m_ePreSceneState == m_eCurSceneState)
		return;
	switch (m_eCurSceneState)
	{
	case SCENE_START:
		m_dwFrameTime = GetTickCount64();
		break;
	case SCENE_WIN:
		CSoundMgr::Get_Instance()->PlaySound(L"Win.wav", SOUND_EFFECT, 0.1f);
		break;
	case SCENE_LOSE:
		CSoundMgr::Get_Instance()->PlaySound(L"Loss_8.wav", STAGE_LOSE, 0.1f);
		break;
	default:
		break;
	}
	m_ePreSceneState = m_eCurSceneState;
}