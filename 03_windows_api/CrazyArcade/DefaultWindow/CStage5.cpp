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
CStage5::CStage5() :m_hBackGround(NULL), m_pTileVector(nullptr)
{
	m_pBaseStart	= nullptr;

	m_pBase1		= nullptr;
	m_pBase2		= nullptr;
	m_pBase3		= nullptr;
	m_pBase4		= nullptr;

	m_pBaseFinal	= nullptr;

	m_pPlayer		= nullptr;

	m_iTrackCnt		= 3;
	m_iNextBase		= 0;
}

CStage5::~CStage5()
{
	Release();
}

void CStage5::Initialize()
{
#ifdef _DEBUG


#endif // _DEBUG
	int iPlayer_StartX = 14;
	int iPlayer_StartY = 11;
	CObjMgr::GetInstance()->AddObject(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create((iPlayer_StartX * 40) + 40, (iPlayer_StartY * 40) + 60, L"player_start"));

	m_pBaseStart = CAbstractFactory<CBase>::Create((12 * 40) + 40, (11 * 40) + 60 + 20, L"tile_start");
	dynamic_cast<CBase*>(m_pBaseStart)->SetBaseMoveFrame(true);

	m_pBase1	 = CAbstractFactory<CBase>::Create((2 * 40) + 40, (3 * 40) + 60, L"tile_base1");
	m_pBase2	 = CAbstractFactory<CBase>::Create((10 * 40) + 40, (1 * 40) + 60, L"tile_base2");
	m_pBase3	 = CAbstractFactory<CBase>::Create((2 * 40) + 40, (11 * 40) + 60, L"tile_base3");
	m_pBase4	 = CAbstractFactory<CBase>::Create((14 * 40) + 40, (5 * 40) + 60, L"tile_base4");
	m_pBaseFinal = CAbstractFactory<CBase>::Create((12 * 40) + 40, (11 * 40) + 60 + 20, L"tile_final");
	m_pBaseFinal->SetDraw(false);

	CObjMgr::GetInstance()->AddObject(OBJ_BASE, m_pBaseStart);

	CObjMgr::GetInstance()->AddObject(OBJ_BASE, m_pBase1);
	CObjMgr::GetInstance()->AddObject(OBJ_BASE, m_pBase2);
	CObjMgr::GetInstance()->AddObject(OBJ_BASE, m_pBase3);
	CObjMgr::GetInstance()->AddObject(OBJ_BASE, m_pBase4);

	CObjMgr::GetInstance()->AddObject(OBJ_BASE, m_pBaseFinal);

	CObjMgr::GetInstance()->AddObject(OBJ_GASSTATION, CAbstractFactory<CGasStation>::Create(260, 159.5, L"GasStation"));



	CObjMgr::GetInstance()->AddObject(OBJ_BUTTON, CAbstractFactory<CButton>::Create(717, 576, L"button_stageExit"));

	CObjMgr::GetInstance()->LoadStage5();

	m_pPlayer = CObjMgr::GetInstance()->GetList(OBJ_PLAYER).front();

	m_hBackGround = CBmpMgr::GetInstance()->FindImage(L"stage3");
	m_pTileVector = CObjMgr::GetInstance()->GetTilePtr();

	for (auto& pTile : *m_pTileVector)
	{
		int iStart = pTile->GetFrame().iStart;
		if ((iStart >= 20 && iStart <= 30) || (iStart >=32 && iStart <=34))
		{
			pTile->Render(m_hBackGround);
			pTile->SetDraw(false);
		}
	}

	CSoundMgr::Get_Instance()->PlaySound(L"StageStart_7.wav", STAGE_START, 0.2f);
}

int CStage5::Update()
{
	if (m_iTrackCnt > 0)
	{
		CObjMgr::GetInstance()->Update();
		CheckBase();
	}
	else
	{
		CSceneMgr::GetInstance()->SceneChangeReserve(SC_MENU);
	}
	return 0;
}

void CStage5::LateUpdate()
{
	CObjMgr::GetInstance()->LateUpdate();
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
}

void CStage5::Release()
{
	CObjMgr::GetInstance()->ReleaseRenderList();
	CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
	CObjMgr::GetInstance()->DeleteObj(OBJ_PLAYER);
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
	if (dynamic_cast<CPlayer*>(m_pPlayer)->GetRide() == false)
		return;
	RECT rc;
	if (m_iTrackCnt == 3 && m_iNextBase == 0
		&& IntersectRect(&rc, m_pBaseStart->GetRect(), m_pPlayer->GetRect()))
	{
		dynamic_cast<CBase*>(m_pBaseStart)->SetBaseMoveFrame(false);
		dynamic_cast<CBase*>(m_pBase1)->SetBaseMoveFrame(true);
		//++m_iNextBase;
		m_iNextBase = m_iNextBase % 4 + 1;
	}
	CObj* BaseArr[4] = { m_pBase1,m_pBase2,m_pBase3,m_pBase4 };
	for (int i = 0; i < 4; i++)
	{
		if (m_iNextBase == i+1
			&& IntersectRect(&rc, BaseArr[i]->GetRect(), m_pPlayer->GetRect()))
		{
			if (m_iNextBase == 4)
				--m_iTrackCnt;
			dynamic_cast<CBase*>(BaseArr[m_iNextBase -1])->SetBaseMoveFrame(false);
			dynamic_cast<CBase*>(BaseArr[m_iNextBase % 4])->SetBaseMoveFrame(true);
			m_iNextBase = m_iNextBase % 4 + 1;
		}
	}
	//if (m_iNextBase == 1
	//	&& IntersectRect(&rc, m_pBase1->GetRect(), m_pPlayer->GetRect()))
	//{
	//	dynamic_cast<CBase*>(m_pBase1)->SetBaseMoveFrame(false);
	//	dynamic_cast<CBase*>(m_pBase2)->SetBaseMoveFrame(true);
	//	//++m_iNextBase;
	//	m_iNextBase = m_iNextBase % 4 + 1;
	//}
	//if (m_iNextBase == 2
	//	&& IntersectRect(&rc, m_pBase2->GetRect(), m_pPlayer->GetRect()))
	//{
	//	dynamic_cast<CBase*>(m_pBase2)->SetBaseMoveFrame(false);
	//	dynamic_cast<CBase*>(m_pBase3)->SetBaseMoveFrame(true);
	//	//++m_iNextBase;
	//	m_iNextBase = m_iNextBase % 4 + 1;
	//}

	//if (m_iNextBase == 3
	//	&& IntersectRect(&rc, m_pBase3->GetRect(), m_pPlayer->GetRect()))
	//{
	//	dynamic_cast<CBase*>(m_pBase3)->SetBaseMoveFrame(false);
	//	dynamic_cast<CBase*>(m_pBase4)->SetBaseMoveFrame(true);
	//	//++m_iNextBase;
	//	m_iNextBase = m_iNextBase % 4 + 1;
	//}

	//if (m_iNextBase == 4
	//	&& IntersectRect(&rc, m_pBase4->GetRect(), m_pPlayer->GetRect()))
	//{
	//	dynamic_cast<CBase*>(m_pBase4)->SetBaseMoveFrame(false);
	//	dynamic_cast<CBase*>(m_pBase1)->SetBaseMoveFrame(true);
	//	//++m_iNextBase;
	//	m_iNextBase = m_iNextBase % 4 + 1;
	//}

}
