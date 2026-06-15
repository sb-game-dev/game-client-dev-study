#include "pch.h"
#include "CStage1.h"
#include "CBmpMgr.h"
#include "CObjMgr.h"
#include "CPlayer.h"
#include "CAbstractFactory.h"
#include "CMonster.h"
#include "CSceneMgr.h"
#include "CSoundMgr.h"
#include "CButton.h"

CStage1::CStage1()
{
}

CStage1::~CStage1()
{
	Release();
}

void CStage1::Initialize()
{
	InsertImg();

	CObjMgr::GetInstance()->AddObject(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create((13 * 40) + 40, (11 * 40) + 60, L"player_start"));

	//Follow

	CObjMgr::GetInstance()->AddObject(OBJ_MONSTER, CAbstractFactory<CMonster>::Create((7 * 40) + 40, (2  * 40) + 60, L"Bean_Monster_Start"));
	CObjMgr::GetInstance()->AddObject(OBJ_MONSTER, CAbstractFactory<CMonster>::Create((7 * 40) + 40, (12 * 40) + 60, L"Bean_Monster_Start"));
	
	//Basic
	CObjMgr::GetInstance()->AddObject(OBJ_MONSTER, CAbstractFactory<CMonster>::Create((9 * 40) + 40,  (7 * 40) + 60, L"Bean_Monster_Start"));
	CObjMgr::GetInstance()->AddObject(OBJ_MONSTER, CAbstractFactory<CMonster>::Create((10 * 40) + 40, (7 * 40) + 60, L"Bean_Monster_Start"));
	CObjMgr::GetInstance()->AddObject(OBJ_MONSTER, CAbstractFactory<CMonster>::Create((11 * 40) + 40, (7 * 40) + 60, L"Bean_Monster_Start"));
	CObjMgr::GetInstance()->AddObject(OBJ_MONSTER, CAbstractFactory<CMonster>::Create((12 * 40) + 40, (7 * 40) + 60, L"Bean_Monster_Start"));


	CObjMgr::GetInstance()->AddObject(OBJ_BUTTON, CAbstractFactory<CButton>::Create(717, 576, L"button_stageExit"));


	CObjMgr::GetInstance()->LoadStage1();
	CSoundMgr::Get_Instance()->PlaySound(L"StageStart_7.wav", STAGE_START, 0.2f);
}

int CStage1::Update()
{
	if (CObjMgr::GetInstance()->GetRemainMonster() <= 0)
	{
		CSceneMgr::GetInstance()->SceneChangeReserve(SC_STAGE2);
		return 0;
	}
	else if (CObjMgr::GetInstance()->GetRemainPlayer() == false)
	{
		m_bEndScene = true;
	}
	CObjMgr::GetInstance()->Update();

	return 0;
}

void CStage1::LateUpdate()
{

	CObjMgr::GetInstance()->LateUpdate();
}

void CStage1::Render(HDC hDC)
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
	//if (m_bEndScene)
	//{
	//	HDC hExitButton = CBmpMgr::GetInstance()->FindImage(L"button_stageExit");
	//
	//	BitBlt(hDC,							// 목적지 DC
	//		0, 0,
	//		WINCX, WINCY,
	//		hBackGround,					// 원본 DC
	//		0,								// 원본 이미지에서 가져오기 시작할 좌표의 LEFT, TOP
	//		0,
	//		SRCCOPY);						// 그대로 복사하여 출력
	//
	//	CObjMgr::GetInstance()->Render(hDC);
	//}
}

void CStage1::Release()
{
	CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
	CObjMgr::GetInstance()->DeleteObj(OBJ_PLAYER);
	CObjMgr::GetInstance()->DeleteObj(OBJ_BOMB);
	CObjMgr::GetInstance()->DeleteObj(OBJ_BUTTON);
	CObjMgr::GetInstance()->DeleteObj(OBJ_WAVE);
	CObjMgr::GetInstance()->DeleteObj(OBJ_MONSTER);
	CObjMgr::GetInstance()->DeleteObj(OBJ_ITEM);
	CObjMgr::GetInstance()->DeleteTile();
}

void CStage1::InsertImg()
{
	//BackGround(Map)
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/BackGround/stage_background.bmp", L"stage_background");

	//Player
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Player/player_start.bmp", L"player_start");

	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Player/player_down.bmp", L"player_down");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Player/player_up.bmp", L"player_up");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Player/player_left.bmp", L"player_left");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Player/player_right.bmp", L"player_right");

	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Player/player_hit.bmp", L"player_hit");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Player/player_death.bmp", L"player_death");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Player/player_live.bmp", L"player_live");

	//Tile
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Tile/tile.bmp", L"tile");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Tile/tile_hit.bmp", L"tile_hit");

	//Bubble
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Bomb/BlueBubble.bmp", L"BlueBubble");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Bomb/RainbowBubble.bmp", L"RainbowBubble");

	//Wave
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Wave/WaveCenter.bmp", L"WaveCenter");

	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Wave/down.bmp", L"down");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Wave/left.bmp", L"left");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Wave/right.bmp", L"right");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Wave/up.bmp", L"up");

	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Wave/down_end.bmp", L"down_end");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Wave/left_end.bmp", L"left_end");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Wave/right_end.bmp", L"right_end");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Wave/up_end.bmp", L"up_end");

	//Monster
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Monster/Bean_Monster_Start.bmp", L"Bean_Monster_Start");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Monster/Bean_Monster_Death.bmp", L"Bean_Monster_Death");

	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Monster/Bean_Monster_Down.bmp", L"Bean_Monster_Down");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Monster/Bean_Monster_Left.bmp", L"Bean_Monster_Left");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Monster/Bean_Monster_Right.bmp", L"Bean_Monster_Right");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Monster/Bean_Monster_Up.bmp", L"Bean_Monster_Up");

	//Item
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Item/new/bubble.bmp", L"bubble");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Item/new/dart.bmp", L"dart");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Item/new/fluid.bmp", L"fluid");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Item/new/needle.bmp", L"needle");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Item/new/roller.bmp", L"roller");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Item/new/shield.bmp", L"shield");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Item/new/shoe.bmp", L"shoe");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Item/new/trampoline.bmp", L"trampoline");

	//Item_UI
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/UI/UI_Bomb.bmp", L"UI_Bomb");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/UI/UI_Liquid2.bmp", L"UI_Liquid2");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/UI/UI_Skate.bmp", L"UI_Skate");

	//Ctrl_slot
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/UI/stage_ctrlItem.bmp", L"stage_ctrlItem");

	//DartObj
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Item/new/dart_obj.bmp", L"dart_obj");

	//SheildEffect
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Item/new/shieldEffects2.bmp", L"shieldEffects");

	//button_Exit
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Button/bmp/button_stageExit.bmp", L"button_stageExit");
}
