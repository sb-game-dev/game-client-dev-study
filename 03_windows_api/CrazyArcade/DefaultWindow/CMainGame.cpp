#include "pch.h"
#include "CMainGame.h"
#include "CSceneMgr.h"
#include "CObjMgr.h"
#include "CKeyMgr.h"
#include "CImgMgr.h"
#include "CMouse.h"
#include "CAbstractFactory.h"
#include "CBmpMgr.h"
#include "CSoundMgr.h"
#include "CInven.h"
CMainGame::CMainGame() :m_hDC(NULL), m_memDC(NULL), m_Bit(NULL), m_Old(NULL),m_pGraphics(NULL), m_iFPS(0),m_dwTime(GetTickCount64())
{
	ZeroMemory(&m_szFPS, sizeof(m_szFPS));
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	
#ifdef _DEBUG

	if (::AllocConsole() == TRUE)
	{
		FILE* nfp[3];
		freopen_s(nfp + 0, "CONOUT$", "rb", stdin);
		freopen_s(nfp + 1, "CONOUT$", "wb", stdout);
		freopen_s(nfp + 2, "CONOUT$", "wb", stderr);
		std::ios::sync_with_stdio();
	}

#endif // _DEBUG
	InsertImg();

	m_hDC = GetDC(g_hWnd);
	m_memDC = CreateCompatibleDC(m_hDC);
	m_Bit = CreateCompatibleBitmap(m_hDC, WINCX, WINCY);
	m_Old = (HBITMAP)SelectObject(m_memDC, m_Bit);

	CObjMgr::GetInstance()->AddObject(OBJ_MOUSE, CAbstractFactory<CMouse>::Create(0.f, 0.f));

	CSoundMgr::Get_Instance()->Initialize();

#ifdef _DEBUG
	CSceneMgr::GetInstance()->SceneChangeReserve(SC_STAGE3);
#elif NDEBUG
	CSceneMgr::GetInstance()->SceneChangeReserve(SC_LOGO);
#endif // _DEBUG
}

void CMainGame::Update()
{
	CKeyMgr::GetInstance()->KeyUpdate();
	CSceneMgr::GetInstance()->Update();
}

void CMainGame::LateUpdate()
{
	CSceneMgr::GetInstance()->LateUpdate();
	CSceneMgr::GetInstance()->SceneProcess();
}


void CMainGame::Render()
{
	m_iFPS++;

	if (m_dwTime + 1000 < GetTickCount64())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);

		m_iFPS = 0;

		m_dwTime = GetTickCount64();

		SetWindowText(g_hWnd, m_szFPS);
	}
	CSceneMgr::GetInstance()->Render(m_memDC);

	BitBlt(m_hDC, 0, 0, WINCX, WINCY, m_memDC, 0, 0, SRCCOPY);
}

void CMainGame::Release()
{
#ifdef _DEBUG

	FreeConsole();

#endif // _DEBUG

	ReleaseDC(g_hWnd, m_hDC);

	CBmpMgr::Destroy();
	CImgMgr::Destroy();
	CKeyMgr::Destroy();
	CSceneMgr::Destroy();
	CSoundMgr::Destroy_Instance();
	CObjMgr::Destroy();
}

void CMainGame::InsertImg()
{
	//BackGround
	CImgMgr::GetInstance()->InsertImg(L"../Resource/BackGround/Logo.png", L"Logo");
	CImgMgr::GetInstance()->InsertImg(L"../Resource/BackGround/black_bg.png", L"black_bg");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/BackGround/menu_background.bmp", L"menu_background");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/BackGround/edit_background.bmp", L"edit_background");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/BackGround/stage_background.bmp", L"stage_background");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/BackGround/stage2.bmp", L"stage2");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/BackGround/shop.bmp", L"shop");


	//Button
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Button/bmp/button_edit.bmp", L"button_edit");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Button/bmp/button_save.bmp", L"button_save");

	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Button/bmp/button_exitEdit.bmp", L"button_exitEdit");

	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Button/bmp/button_creator.bmp", L"button_creator");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Button/bmp/button_fastStart.bmp", L"button_fastStart");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Button/bmp/button_stageStart.bmp", L"button_stageStart");

	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Button/bmp/button_FirstStage.bmp", L"button_FirstStage");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Button/bmp/button_SecondStage.bmp", L"button_SecondStage");

	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Button/bmp/button_stageExit.bmp", L"button_stageExit");

	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Button/bmp/button_back.bmp", L"button_back");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Button/bmp/button_shop.bmp", L"button_shop");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Button/bmp/button_buy.bmp", L"button_buy0");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Button/bmp/button_buy.bmp", L"button_buy1");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Button/bmp/button_buy.bmp", L"button_buy2");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Button/bmp/button_buy.bmp", L"button_buy3");

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
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Tile/tile2.bmp", L"tile");
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

	//Item
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Item/new/bubble.bmp", L"bubble");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Item/new/dart.bmp", L"dart");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Item/new/fluid.bmp", L"fluid");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Item/new/needle.bmp", L"needle");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Item/new/roller.bmp", L"roller");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Item/new/shield.bmp", L"shield");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Item/new/shoe.bmp", L"shoe");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Item/new/trampoline.bmp", L"trampoline");

	//Monster
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Monster/Bean_Monster_Start.bmp", L"Bean_Monster_Start");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Monster/Bean_Monster_Death.bmp", L"Bean_Monster_Death");

	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Monster/Bean_Monster_Down.bmp", L"Bean_Monster_Down");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Monster/Bean_Monster_Left.bmp", L"Bean_Monster_Left");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Monster/Bean_Monster_Right.bmp", L"Bean_Monster_Right");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Monster/Bean_Monster_Up.bmp", L"Bean_Monster_Up");

	//Item_UI
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/UI/UI_Bomb.bmp", L"UI_Bomb");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/UI/UI_Liquid2.bmp", L"UI_Liquid2");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/UI/UI_Skate.bmp", L"UI_Skate");

	//Numver_UI
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/UI/Timer/numbers.bmp", L"numbers");

	

	//Ctrl_slot
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/UI/stage_ctrlItem.bmp", L"stage_ctrlItem");

	//DartObj
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Item/new/dart_obj.bmp", L"dart_obj");

	//SheildEffect
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Item/new/shieldEffects2.bmp", L"shieldEffects");
	//button_Exit

	//Boss
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Boss/Boss_down2.bmp", L"Boss_down");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Boss/Boss_up2.bmp", L"Boss_up");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Boss/Boss_left2.bmp", L"Boss_left");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Boss/Boss_right2.bmp", L"Boss_right");

	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Boss/Boss_Bubble.bmp", L"Boss_Bubble");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Boss/Boss_Dead.bmp", L"Boss_Dead");

	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/UI/HP_Bar.bmp", L"HP_Bar");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/UI/HP_Bar_Blue.bmp", L"HP_Bar_Blue");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/UI/HP_Bar_Red.bmp", L"HP_Bar_Red");

	//Mark
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Mark/Mark.bmp", L"Mark");
}
