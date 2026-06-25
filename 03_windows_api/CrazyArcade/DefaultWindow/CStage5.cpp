#include "pch.h"
#include "CStage5.h"
#include "CObjMgr.h"
#include "CAbstractFactory.h"
#include "CPlayer.h"
#include "CImgMgr.h"
#include "CBoss.h"
#include "CBmpMgr.h"
#include "CItem.h"
#include "CSceneMgr.h"
#include "CSoundMgr.h"
#include "CMonster.h"
#include "CButton.h"
#include "CMark.h"
#include "CInven.h"
#include "CBase.h"
#include "CGasStation.h"
#include "CPlayer2.h"
#include "CBaseEffect.h"
#include "CStartEffect.h"
CStage5::CStage5() :m_hBackGround(NULL), m_pTileVector(nullptr), m_pPlayerRemainGas(nullptr), m_pPlayerRemainGas2(nullptr), m_pPlayMode(nullptr)
{
	m_pBaseStart	= nullptr;

	m_pBase1		= nullptr;
	m_pBase2		= nullptr;
	m_pBase3		= nullptr;
	m_pBase4		= nullptr;

	m_pBaseFinal	= nullptr;

	m_pPlayer		= nullptr;
	m_pPlayer2		= nullptr;
	m_pGasStation	= nullptr;

	m_pBaseStartEffect1	= nullptr;
	m_pBaseStartEffect2	= nullptr;

	m_pBase1Effect1		= nullptr;
	m_pBase1Effect2		= nullptr;
	m_pBase2Effect1		= nullptr;
	m_pBase2Effect2		= nullptr;
	m_pBase3Effect1		= nullptr;
	m_pBase3Effect2		= nullptr;
	m_pBase4Effect1		= nullptr;
	m_pBase4Effect2		= nullptr;

	m_iTrackCnt		= 3;
	m_iNextBase		= 0;

	m_iTrackCnt2	= 3;
	m_iNextBase2	= 0;
}

CStage5::~CStage5()
{
	Release();
}

void CStage5::Initialize()
{
	int iPlayer_StartX = 14;
	int iPlayer_StartY = 11;
	m_pPlayer = CAbstractFactory<CPlayer>::Create((iPlayer_StartX * 40) + 40, (iPlayer_StartY * 40) + 60, L"player_start");
	CObjMgr::GetInstance()->AddObject(OBJ_PLAYER, m_pPlayer);

	int iPlayer2_StartX = 4;
	int iPlayer2_StartY = 8;
	m_pPlayMode = CSceneMgr::GetInstance()->GetPlayModePtr();
#ifdef _DEBUG
	* m_pPlayMode = MODE2P;
#endif // _DEBUG
	if (*m_pPlayMode == MODE2P)
	{
		m_pPlayer2 = CAbstractFactory<CPlayer2>::Create((iPlayer2_StartX * 40) + 40, (iPlayer2_StartY * 40) + 60, L"player_start");
		CObjMgr::GetInstance()->AddObject(OBJ_PLAYER2, m_pPlayer2);
	}

	m_pBaseStart = CAbstractFactory<CBase>::Create((12 * 40) + 40, (11 * 40) + 60 + 20, L"tile_start");	


	m_pBase1	 = CAbstractFactory<CBase>::Create((2 * 40) + 40, (3 * 40) + 60, L"tile_base1");
	m_pBase2	 = CAbstractFactory<CBase>::Create((10 * 40) + 40, (1 * 40) + 60, L"tile_base2");
	m_pBase3	 = CAbstractFactory<CBase>::Create((2 * 40) + 40, (11 * 40) + 60, L"tile_base3");
	m_pBase4	 = CAbstractFactory<CBase>::Create((14 * 40) + 40, (5 * 40) + 60, L"tile_base4");
	m_pBaseFinal = CAbstractFactory<CBase>::Create((12 * 40) + 40, (11 * 40) + 60 + 20, L"tile_final");

	m_pBaseFinal->SetDraw(false);

	m_pGasStation = CAbstractFactory<CGasStation>::Create((5 * 40) + 40, (3 * 40) + 60, L"GasStation");

	CObjMgr::GetInstance()->AddObject(OBJ_BASE, m_pBaseStart);
	
	CObjMgr::GetInstance()->AddObject(OBJ_BASE, m_pBase1);
	CObjMgr::GetInstance()->AddObject(OBJ_BASE, m_pBase2);
	CObjMgr::GetInstance()->AddObject(OBJ_BASE, m_pBase3);
	CObjMgr::GetInstance()->AddObject(OBJ_BASE, m_pBase4);

	CObjMgr::GetInstance()->AddObject(OBJ_BASE, m_pBaseFinal);

	CObjMgr::GetInstance()->AddObject(OBJ_GASSTATION, m_pGasStation);

	CObjMgr::GetInstance()->AddObject(OBJ_BUTTON, CAbstractFactory<CButton>::Create(717, 576, L"button_stageExit"));

	CObjMgr::GetInstance()->LoadStage5();

	m_pPlayer = CObjMgr::GetInstance()->GetList(OBJ_PLAYER).front();

	m_hBackGround = CBmpMgr::GetInstance()->FindImage(L"stage3");
	m_pTileVector = CObjMgr::GetInstance()->GetTilePtr();
	m_pPlayerRemainGas = dynamic_cast<CPlayer*>(m_pPlayer)->GetRemainGasPtr();
	m_pPlayerRemainGas2 = dynamic_cast<CPlayer2*>(m_pPlayer2)->GetRemainGasPtr();
	for (auto& pTile : *m_pTileVector)
	{
		int iStart = pTile->GetFrame().iStart;
		if ((iStart >= 20 && iStart <= 30) || iStart == 4)// || (iStart >=32 && iStart <=34))
		{
			pTile->Render(m_hBackGround);
			pTile->SetDraw(false);
		}
	}

	m_pBaseStartEffect1 = CAbstractFactory<CBaseEffect>::Create((12 * 40) + 40, (11 * 40) + 60 + 20, L"tile_start1");
	dynamic_cast<CBaseEffect*>(m_pBaseStartEffect1)->SetMoveFrame(true);
	CObjMgr::GetInstance()->AddObject(OBJ_BASE, m_pBaseStartEffect1);

	m_pBaseStartEffect2 = CAbstractFactory<CBaseEffect>::Create((12 * 40) + 40, (11 * 40) + 60 + 20, L"tile_start2");
	dynamic_cast<CBaseEffect*>(m_pBaseStartEffect2)->SetMoveFrame(true);
	CObjMgr::GetInstance()->AddObject(OBJ_BASE, m_pBaseStartEffect2);

	m_pBase1Effect1 = CAbstractFactory<CBaseEffect>::Create((2 * 40) + 40, (3 * 40) + 60, L"tile_base1_1");
	m_pBase1Effect1->SetDraw(false);
	CObjMgr::GetInstance()->AddObject(OBJ_BASE, m_pBase1Effect1);

	m_pBase1Effect2 = CAbstractFactory<CBaseEffect>::Create((2 * 40) + 40, (3 * 40) + 60, L"tile_base1_2");
	m_pBase1Effect2->SetDraw(false);
	CObjMgr::GetInstance()->AddObject(OBJ_BASE, m_pBase1Effect2);

	m_pBase2Effect1 = CAbstractFactory<CBaseEffect>::Create((10 * 40) + 40, (1 * 40) + 60, L"tile_base2_1");
	m_pBase2Effect1->SetDraw(false);
	CObjMgr::GetInstance()->AddObject(OBJ_BASE, m_pBase2Effect1);

	m_pBase2Effect2 = CAbstractFactory<CBaseEffect>::Create((10 * 40) + 40, (1 * 40) + 60, L"tile_base2_2");
	m_pBase2Effect2->SetDraw(false);
	CObjMgr::GetInstance()->AddObject(OBJ_BASE, m_pBase2Effect2);

	m_pBase3Effect1 = CAbstractFactory<CBaseEffect>::Create((2 * 40) + 40, (11 * 40) + 60, L"tile_base3_1");
	m_pBase3Effect1->SetDraw(false);
	CObjMgr::GetInstance()->AddObject(OBJ_BASE, m_pBase3Effect1);

	m_pBase3Effect2 = CAbstractFactory<CBaseEffect>::Create((2 * 40) + 40, (11 * 40) + 60, L"tile_base3_2");
	m_pBase3Effect2->SetDraw(false);
	CObjMgr::GetInstance()->AddObject(OBJ_BASE, m_pBase3Effect2);

	m_pBase4Effect1 = CAbstractFactory<CBaseEffect>::Create((14 * 40) + 40, (5 * 40) + 60, L"tile_base4_1");
	m_pBase4Effect1->SetDraw(false);
	CObjMgr::GetInstance()->AddObject(OBJ_BASE, m_pBase4Effect1);

	m_pBase4Effect2 = CAbstractFactory<CBaseEffect>::Create((14 * 40) + 40, (5 * 40) + 60, L"tile_base4_2");
	m_pBase4Effect2->SetDraw(false);
	CObjMgr::GetInstance()->AddObject(OBJ_BASE, m_pBase4Effect2);


	CStartEffect::GetInstance()->Initialize();
	CSoundMgr::Get_Instance()->PlaySound(L"StageStart_7.wav", STAGE_START, 0.2f);
}

int CStage5::Update()
{
	CObjMgr::GetInstance()->Update();

	CheckCollisionGasStation();
	CheckCollisionGasStation2();
	CStartEffect::GetInstance()->Update();

	return 0;
}

void CStage5::LateUpdate()
{
	if (m_pPlayer == nullptr)
		return;

	CObjMgr::GetInstance()->LateUpdate();

	CheckBase(); 
	CheckBase2();
	CheckNoCollisionGasStation();

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

void CStage5::Render(HDC hDC)
{
	BitBlt(hDC,							// 목적지 DC
		0, 0,
		WINCX, WINCY,
		m_hBackGround,					// 원본 DC
		0,								// 원본 이미지에서 가져오기 시작할 좌표의 LEFT, TOP
		0,
		SRCCOPY);						// 그대로 복사하여 출력

	CObjMgr::GetInstance()->Render(hDC);

	if (m_pPlayer && dynamic_cast<CPlayer*>(m_pPlayer)->GetRide())
	{
		Graphics* _pGraphics = Graphics::FromHDC(hDC);
		Gdiplus::Image* hTrackCnt = CImgMgr::GetInstance()->FindImg(L"trackCnt");

		Rect rect = { 519, 495, 97, 41 };

		ImageAttributes attr;
		MakeAlphaAttr(attr, 0.7f);
		_pGraphics->DrawImage(hTrackCnt, rect,
			97 * ((3 - m_iTrackCnt < 3) ? (3 - m_iTrackCnt) : 2), 0,
			97, 41,
			UnitPixel, &attr);

		HDC hGasFrame = CBmpMgr::GetInstance()->FindImage(L"gas_frame");
		BitBlt(hDC, 447, 536, 170, 22, hGasFrame, 0, 0, SRCCOPY);

		HDC hGasBar = CBmpMgr::GetInstance()->FindImage(L"gas_bar");
		BitBlt(hDC, 524, 540, 87 * (*m_pPlayerRemainGas) / 300, 14, hGasBar, 0, 0, SRCCOPY);
	}

	//2p_UI
	if (m_pPlayer2 && dynamic_cast<CPlayer2*>(m_pPlayer2)->GetRide())
	{
		Graphics* _pGraphics = Graphics::FromHDC(hDC);
		Gdiplus::Image* hTrackCnt = CImgMgr::GetInstance()->FindImg(L"trackCnt2");
	
		Rect rect = { 24, 495,97, 41 };
	
		ImageAttributes attr;
		MakeAlphaAttr(attr, 0.7f);
		_pGraphics->DrawImage(hTrackCnt, rect,
			97 * ((3 - m_iTrackCnt2 < 3) ? (3 - m_iTrackCnt2) : 2), 0,
			97, 41,
			UnitPixel, &attr);
	
		HDC hGasFrame = CBmpMgr::GetInstance()->FindImage(L"gas_frame2");
		BitBlt(hDC, 24, 536, 170, 22, hGasFrame, 0, 0, SRCCOPY);
	
		HDC hGasBar = CBmpMgr::GetInstance()->FindImage(L"gas_bar");
		BitBlt(hDC, 101, 540, 87 * (*m_pPlayerRemainGas2) / 300, 14, hGasBar, 0, 0, SRCCOPY);
	}



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
	if (m_eCurSceneState == SCENE_START || m_eCurSceneState == SCENE_END)
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

void CStage5::Release()
{
	CObjMgr::GetInstance()->ReleaseRenderList();
	CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
	CObjMgr::GetInstance()->DeleteObj(OBJ_PLAYER);
	CObjMgr::GetInstance()->DeleteObj(OBJ_PLAYER2);
	CObjMgr::GetInstance()->DeleteObj(OBJ_BOMB);
	CObjMgr::GetInstance()->DeleteObj(OBJ_WAVE);
	CObjMgr::GetInstance()->DeleteObj(OBJ_BUTTON);
	CObjMgr::GetInstance()->DeleteObj(OBJ_MONSTER);
	CObjMgr::GetInstance()->DeleteObj(OBJ_ITEM);

	CObjMgr::GetInstance()->DeleteObj(OBJ_BASE);
	CObjMgr::GetInstance()->DeleteObj(OBJ_GASSTATION);

	CObjMgr::GetInstance()->DeleteTile();
}

void CStage5::CheckBase()
{
	if (!CObjMgr::GetInstance()->GetList(OBJ_PLAYER).empty())
	{
		CPlayer* pTempPlayer = dynamic_cast<CPlayer*>(m_pPlayer);
		if(pTempPlayer && pTempPlayer->GetRide() == false)
			return;
	}
	cout << "m_iNextBase: " << m_iNextBase << endl;
	RECT rc;
	//Start
	if (m_iTrackCnt == 3 && m_iNextBase == 0
		&& IntersectRect(&rc, m_pBaseStart->GetRect(), m_pPlayer->GetRect()))
	{
		CSoundMgr::Get_Instance()->PlaySound(L"ef_4.wav", SOUND_EFFECT, 0.2f);
		dynamic_cast<CBaseEffect*>(m_pBaseStartEffect1)->SetMoveFrame(false);
		dynamic_cast<CBaseEffect*>(m_pBase1Effect1)->SetMoveFrame(true);
		m_iNextBase = m_iNextBase % 4 + 1;
	}

	if (m_iTrackCnt > 0)
	{
		CObj* BaseArr[4] = { m_pBase1Effect1,m_pBase2Effect1,m_pBase3Effect1,m_pBase4Effect1 };
		for (int i = 0; i < 4; i++)
		{
			if (m_iNextBase == i + 1
				&& IntersectRect(&rc, BaseArr[i]->GetRect(), m_pPlayer->GetRect()))
			{
				CSoundMgr::Get_Instance()->PlaySound(L"ef_4.wav", SOUND_EFFECT, 0.2f);
				if (m_iNextBase == 4)
					--m_iTrackCnt;
				dynamic_cast<CBaseEffect*>(BaseArr[m_iNextBase - 1])->SetMoveFrame(false);
				if (m_iTrackCnt > 0)
				{
					dynamic_cast<CBaseEffect*>(BaseArr[m_iNextBase % 4])->SetMoveFrame(true);
					m_iNextBase = m_iNextBase % 4 + 1;
				}
				else
				{
					m_pBaseFinal->SetDraw(true);
					dynamic_cast<CBase*>(m_pBaseFinal)->SetBaseMoveFrame(true);
					dynamic_cast<CBaseEffect*>(m_pBaseStartEffect2)->SetMoveFrame(false);
				}
			}
		}
	}
	
	//Final
	if (m_pBaseFinal->GetDraw() == true &&
		IntersectRect(&rc, m_pBaseFinal->GetRect(), m_pPlayer->GetRect()))
	{
		cout << "FinalRectCollision" << endl;

		CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
		m_eCurSceneState = SCENE_WIN;
		dynamic_cast<CPlayer*>(m_pPlayer)->SetWin();
		ChangeScene();
	}	
}

void CStage5::CheckBase2()
{
	if (!CObjMgr::GetInstance()->GetList(OBJ_PLAYER2).empty())
	{
		CPlayer2* pTempPlayer = dynamic_cast<CPlayer2*>(m_pPlayer2);
		if (pTempPlayer && pTempPlayer->GetRide() == false)
			return;
	}
	cout << "m_iNextBase2: " << m_iNextBase2 << endl;
	RECT rc;
	if (m_iTrackCnt2 == 3 && m_iNextBase2 == 0
		&& IntersectRect(&rc, m_pBaseStart->GetRect(), m_pPlayer2->GetRect()))
	{
		CSoundMgr::Get_Instance()->PlaySound(L"ef_4.wav", SOUND_EFFECT, 0.2f);
		dynamic_cast<CBaseEffect*>(m_pBaseStartEffect2)->SetMoveFrame(false);
		dynamic_cast<CBaseEffect*>(m_pBase1Effect2)->SetMoveFrame(true);
		m_iNextBase2 = m_iNextBase2 % 4 + 1;
	}
	if (m_iTrackCnt2 > 0)
	{
		CObj* BaseArr[4] = { m_pBase1Effect2,m_pBase2Effect2,m_pBase3Effect2,m_pBase4Effect2 };
		for (int i = 0; i < 4; i++)
		{
			if (m_iNextBase2 == i + 1
				&& IntersectRect(&rc, BaseArr[i]->GetRect(), m_pPlayer2->GetRect()))
			{
				CSoundMgr::Get_Instance()->PlaySound(L"ef_4.wav", SOUND_EFFECT, 0.2f);
				if (m_iNextBase2 == 4)
					--m_iTrackCnt2;
				dynamic_cast<CBaseEffect*>(BaseArr[m_iNextBase2 - 1])->SetMoveFrame(false);
				if (m_iTrackCnt2 > 0)
				{
					dynamic_cast<CBaseEffect*>(BaseArr[m_iNextBase2 % 4])->SetMoveFrame(true);
					m_iNextBase2 = m_iNextBase2 % 4 + 1;
				}
				else
				{
					m_pBaseFinal->SetDraw(true);
					dynamic_cast<CBase*>(m_pBaseFinal)->SetBaseMoveFrame(true);
					dynamic_cast<CBaseEffect*>(m_pBaseStartEffect1)->SetMoveFrame(false);
				}
			}
		}
	}

	//Final
	if (m_pBaseFinal->GetDraw() == true &&
		IntersectRect(&rc, m_pBaseFinal->GetRect(), m_pPlayer2->GetRect()))
	{
		cout << "FinalRectCollision" << endl;

		CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
		m_eCurSceneState = SCENE_WIN;
		dynamic_cast<CPlayer2*>(m_pPlayer2)->SetWin();
		ChangeScene();
	}

}

void CStage5::CheckCollisionGasStation()
{
	if (CObjMgr::GetInstance()->GetList(OBJ_PLAYER).empty()
		|| dynamic_cast<CPlayer*>(m_pPlayer)->GetRide() == false)
		return;
	RECT rc;
	RECT rcGasStation = { 260,160,300,200 };
	if (IntersectRect(&rc, &rcGasStation, m_pPlayer->GetRect()))
	{
		m_pPlayer->SetDraw(false);
		dynamic_cast<CGasStation*>(m_pGasStation)->SetRefuel(true);
		if ((*m_pPlayerRemainGas) < 300)
		{
			dynamic_cast<CPlayer*>(m_pPlayer)->AddGas(1.f);
		}
	}
	else
	{
		m_pPlayer->SetDraw(true);
	}
}

void CStage5::CheckCollisionGasStation2()
{
	if (CObjMgr::GetInstance()->GetList(OBJ_PLAYER2).empty()
		|| dynamic_cast<CPlayer2*>(m_pPlayer2)->GetRide() == false)
		return;
	RECT rc;
	RECT rcGasStation = { 260,160,300,200 };
	if (IntersectRect(&rc, &rcGasStation, m_pPlayer2->GetRect()))
	{
		m_pPlayer2->SetDraw(false);
		dynamic_cast<CGasStation*>(m_pGasStation)->SetRefuel(true);
		if ((*m_pPlayerRemainGas2) < 300)
		{
			dynamic_cast<CPlayer2*>(m_pPlayer2)->AddGas(1.f);
		}
	}
	else
	{
		m_pPlayer2->SetDraw(true);
	}
	
	
}

void CStage5::CheckNoCollisionGasStation()
{
	if (CObjMgr::GetInstance()->GetList(OBJ_PLAYER).empty() ||
		CObjMgr::GetInstance()->GetList(OBJ_PLAYER2).empty())
		return;

	RECT rc;
	RECT rcGasStation = { 260,160,300,200 };
	if (!IntersectRect(&rc, &rcGasStation, m_pPlayer->GetRect()) &&
		!IntersectRect(&rc, &rcGasStation, m_pPlayer2->GetRect()))
	{
		dynamic_cast<CGasStation*>(m_pGasStation)->SetRefuel(false);
	}

}

void CStage5::CheckSceneFrame()
{
	if (m_eCurSceneState == SCENE_START && m_fAlpha < 0.f)
	{
		m_eCurSceneState = SCENE_PLAY;
		CSoundMgr::Get_Instance()->PlayBGM(L"bg_4.wav", 0.1f);
	}
	else if (m_eCurSceneState == SCENE_END && m_fAlpha >= 1.f)
	{
	}
}

void CStage5::ChangeScene()
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
		break;
	default:
		break;
	}
	m_ePreSceneState = m_eCurSceneState;
}