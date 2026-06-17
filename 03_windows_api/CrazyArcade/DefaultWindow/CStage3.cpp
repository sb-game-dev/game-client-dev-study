#include "pch.h"
#include "CStage3.h"
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
CStage3::CStage3()
{
}

CStage3::~CStage3()
{
	Release();
}

void CStage3::Initialize()
{
	//InsertImg();
#ifdef _DEBUG
	CObjMgr::GetInstance()->AddObject(OBJ_ITEM, CAbstractFactory<CItem>::Create((0 * 40) + 40, (1 * 40) + 60, L"bubble"));
	CObjMgr::GetInstance()->AddObject(OBJ_ITEM, CAbstractFactory<CItem>::Create((1 * 40) + 40, (1 * 40) + 60, L"dart"));
	CObjMgr::GetInstance()->AddObject(OBJ_ITEM, CAbstractFactory<CItem>::Create((2 * 40) + 40, (1 * 40) + 60, L"needle"));
	CObjMgr::GetInstance()->AddObject(OBJ_ITEM, CAbstractFactory<CItem>::Create((3 * 40) + 40, (1 * 40) + 60, L"roller"));
	CObjMgr::GetInstance()->AddObject(OBJ_ITEM, CAbstractFactory<CItem>::Create((10 * 40) + 40, (1 * 40) + 60, L"shield"));
	CObjMgr::GetInstance()->AddObject(OBJ_ITEM, CAbstractFactory<CItem>::Create((11 * 40) + 40, (1 * 40) + 60, L"shoe"));
	CObjMgr::GetInstance()->AddObject(OBJ_ITEM, CAbstractFactory<CItem>::Create((12 * 40) + 40, (1 * 40) + 60, L"trampoline"));
#endif // _DEBUG

	CObjMgr::GetInstance()->AddObject(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create((13 * 40) + 40, (11 * 40) + 60, L"player_start"));
	CObjMgr::GetInstance()->AddObject(OBJ_BOSS, CAbstractFactory<CBoss>::Create((3 * 40) + 40, (10 * 40) + 60, L"Boss_down"));

	CObjMgr::GetInstance()->AddObject(OBJ_BUTTON, CAbstractFactory<CButton>::Create(717, 576, L"button_stageExit"));
	CObjMgr::GetInstance()->AddObject(OBJ_MONSTER, CAbstractFactory<CMonster>::Create((12 * 40) + 40, (7 * 40) + 60, L"Bean_Monster_Start"));

	CObjMgr::GetInstance()->LoadStage3();
	CSoundMgr::Get_Instance()->PlaySound(L"StageStart_7.wav", STAGE_START, 0.2f);
}

int CStage3::Update()
{
	if (CObjMgr::GetInstance()->GetRemainBoss() <= 0)
	{
		CSceneMgr::GetInstance()->SceneChangeReserve(SC_MENU);
		return 0;
	}
	else if (CObjMgr::GetInstance()->GetRemainPlayer() == false)
	{
		m_bEndScene = true;
	}
	CObjMgr::GetInstance()->Update();
	return 0;
}

void CStage3::LateUpdate()
{
	CObjMgr::GetInstance()->LateUpdate();
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
}

void CStage3::Release()
{
	CObjMgr::GetInstance()->ReleaseRenderList();
	CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
	CObjMgr::GetInstance()->DeleteObj(OBJ_PLAYER);
	CObjMgr::GetInstance()->DeleteObj(OBJ_BOMB);
	CObjMgr::GetInstance()->DeleteObj(OBJ_WAVE);
	CObjMgr::GetInstance()->DeleteObj(OBJ_BUTTON);
	CObjMgr::GetInstance()->DeleteObj(OBJ_BOSS);
	CObjMgr::GetInstance()->DeleteObj(OBJ_ITEM);
	CObjMgr::GetInstance()->DeleteTile();
}


