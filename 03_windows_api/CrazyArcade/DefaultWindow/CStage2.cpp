#include "pch.h"
#include "CStage2.h"
#include "CBmpMgr.h"
#include "CObjMgr.h"
#include "CPlayer.h"
#include "CAbstractFactory.h"
#include "CMonster.h"
#include "CSceneMgr.h"
#include "CSoundMgr.h"
#include "CButton.h"

CStage2::CStage2()
{
}

CStage2::~CStage2()
{
	Release();
}

void CStage2::Initialize()
{
	//InsertImg();

	CObjMgr::GetInstance()->DeleteObj(OBJ_MONSTER);

	CObjMgr::GetInstance()->AddObject(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create((6 * 40) + 40, (5 * 40) + 60, L"player_start"));

	//Follow
	CObjMgr::GetInstance()->AddObject(OBJ_MONSTER, CAbstractFactory<CMonster>::Create((7 * 40) + 40, (0 * 40) + 60, L"Bean_Monster_Start"));
	CObjMgr::GetInstance()->AddObject(OBJ_MONSTER, CAbstractFactory<CMonster>::Create((7 * 40) + 40, (12 * 40) + 60, L"Bean_Monster_Start"));
	CObjMgr::GetInstance()->AddObject(OBJ_MONSTER, CAbstractFactory<CMonster>::Create((2 * 40) + 40, (6 * 40) + 60, L"Bean_Monster_Start"));
	CObjMgr::GetInstance()->AddObject(OBJ_MONSTER, CAbstractFactory<CMonster>::Create((12 * 40) + 40, (6 * 40) + 60, L"Bean_Monster_Start"));
	
	//Basic
	CObjMgr::GetInstance()->AddObject(OBJ_MONSTER, CAbstractFactory<CMonster>::Create((0 * 40) + 40, (0 * 40) + 60, L"Bean_Monster_Start"));
	CObjMgr::GetInstance()->AddObject(OBJ_MONSTER, CAbstractFactory<CMonster>::Create((0 * 40) + 40, (12 * 40) + 60, L"Bean_Monster_Start"));
	CObjMgr::GetInstance()->AddObject(OBJ_MONSTER, CAbstractFactory<CMonster>::Create((14 * 40) + 40, (0 * 40) + 60, L"Bean_Monster_Start"));
	CObjMgr::GetInstance()->AddObject(OBJ_MONSTER, CAbstractFactory<CMonster>::Create((14 * 40) + 40, (12 * 40) + 60, L"Bean_Monster_Start"));
	
	CObjMgr::GetInstance()->AddObject(OBJ_MONSTER, CAbstractFactory<CMonster>::Create((2 * 40) + 40, (2 * 40) + 60, L"Bean_Monster_Start"));
	CObjMgr::GetInstance()->AddObject(OBJ_MONSTER, CAbstractFactory<CMonster>::Create((2 * 40) + 40, (10 * 40) + 60, L"Bean_Monster_Start"));
	CObjMgr::GetInstance()->AddObject(OBJ_MONSTER, CAbstractFactory<CMonster>::Create((12 * 40) + 40, (2 * 40) + 60, L"Bean_Monster_Start"));
	CObjMgr::GetInstance()->AddObject(OBJ_MONSTER, CAbstractFactory<CMonster>::Create((12 * 40) + 40, (10 * 40) + 60, L"Bean_Monster_Start"));
	
	//CObjMgr::GetInstance()->AddObject(OBJ_MONSTER, CAbstractFactory<CMonster>::Create((4 * 40) + 40, (4 * 40) + 60, L"Bean_Monster_Start"));
	CObjMgr::GetInstance()->AddObject(OBJ_MONSTER, CAbstractFactory<CMonster>::Create((10 * 40) + 40, (4 * 40) + 60, L"Bean_Monster_Start"));
	CObjMgr::GetInstance()->AddObject(OBJ_MONSTER, CAbstractFactory<CMonster>::Create((4 * 40) + 40, (8 * 40) + 60, L"Bean_Monster_Start"));
	CObjMgr::GetInstance()->AddObject(OBJ_MONSTER, CAbstractFactory<CMonster>::Create((10 * 40) + 40, (8 * 40) + 60, L"Bean_Monster_Start"));



	CObjMgr::GetInstance()->AddObject(OBJ_BUTTON, CAbstractFactory<CButton>::Create(717, 576, L"button_stageExit"));
	CObjMgr::GetInstance()->LoadStage2();
	CSoundMgr::Get_Instance()->PlaySound(L"StageStart_7.wav", STAGE_START, 0.2f);
}

int CStage2::Update()
{
	if (CObjMgr::GetInstance()->GetRemainMonster() <= 0)
	{
		CSceneMgr::GetInstance()->SceneChangeReserve(SC_STAGE3);
		return 0;
	}
	else if (CObjMgr::GetInstance()->GetRemainPlayer() == false)
	{
		m_bEndScene = true;
	}
	CObjMgr::GetInstance()->Update();

	return 0;
}

void CStage2::LateUpdate()
{

	CObjMgr::GetInstance()->LateUpdate();
}

void CStage2::Render(HDC hDC)
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
}

void CStage2::Release()
{
	CObjMgr::GetInstance()->ReleaseRenderList();
	CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
	CObjMgr::GetInstance()->DeleteObj(OBJ_BOMB);
	CObjMgr::GetInstance()->DeleteObj(OBJ_WAVE);
	CObjMgr::GetInstance()->DeleteObj(OBJ_BUTTON);
	CObjMgr::GetInstance()->DeleteObj(OBJ_PLAYER);
	CObjMgr::GetInstance()->DeleteObj(OBJ_MONSTER);
	CObjMgr::GetInstance()->DeleteObj(OBJ_ITEM);
	CObjMgr::GetInstance()->DeleteTile();
}

