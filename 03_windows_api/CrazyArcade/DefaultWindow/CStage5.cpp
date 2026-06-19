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
CStage5::CStage5() :m_hBackGround(NULL)
{
}

CStage5::~CStage5()
{
	Release();
}

void CStage5::Initialize()
{
#ifdef _DEBUG


#endif // _DEBUG
	int iPlayer_StartX = 9;
	int iPlayer_StartY = 9;
	CObjMgr::GetInstance()->AddObject(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create((iPlayer_StartX * 40) + 40, (iPlayer_StartY * 40) + 60, L"player_start"));

	CObjMgr::GetInstance()->AddObject(OBJ_MONSTER, CAbstractFactory<CMonster>::Create((0 * 40) + 40, (0 * 40) + 60, L"Bean_Monster_Start"));
	CObjMgr::GetInstance()->AddObject(OBJ_MONSTER, CAbstractFactory<CMonster>::Create((5 * 40) + 40, (4 * 40) + 60, L"Bean_Monster_Start"));
	CObjMgr::GetInstance()->AddObject(OBJ_MONSTER, CAbstractFactory<CMonster>::Create((3 * 40) + 40, (12 * 40) + 60, L"Bean_Monster_Start"));
	CObjMgr::GetInstance()->AddObject(OBJ_MONSTER, CAbstractFactory<CMonster>::Create((8 * 40) + 40, (6 * 40) + 60, L"Bean_Monster_Start"));
	CObjMgr::GetInstance()->AddObject(OBJ_MONSTER, CAbstractFactory<CMonster>::Create((11 * 40) + 40, (12 * 40) + 60, L"Bean_Monster_Start"));

	CObjMgr::GetInstance()->AddObject(OBJ_BUTTON, CAbstractFactory<CButton>::Create(717, 576, L"button_stageExit"));

	CObjMgr::GetInstance()->LoadStage5();


	CSoundMgr::Get_Instance()->PlaySound(L"StageStart_7.wav", STAGE_START, 0.2f);
}

int CStage5::Update()
{
	CObjMgr::GetInstance()->Update();
	return 0;
}

void CStage5::LateUpdate()
{
	CObjMgr::GetInstance()->LateUpdate();
	
}

void CStage5::Render(HDC hDC)
{
	HDC hBackGround = CBmpMgr::GetInstance()->FindImage(L"stage_background");
	BitBlt(hDC,							// 목적지 DC
		0, 0,
		WINCX, WINCY,
		hBackGround,					// 원본 DC
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
	CObjMgr::GetInstance()->DeleteTile();
}