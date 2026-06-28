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
#include "CNotice.h"
#include "CStartEffect.h"
#include "CSelectPlayer.h"
#include "CInven2.h"
#include "CTimer.h"
#include "CLineMgr.h"
#include "CScrollMgr.h"
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
	CSceneMgr::GetInstance()->SceneChangeReserve(SC_STAGE6);
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
	CInven::Destroy();
	CInven2::Destroy();
	CNotice::Destroy();
	CStartEffect::Destroy();
	CSelectPlayer::Destroy();
	CTimer::Destroy();
	CLineMgr::DestroyInstance();
	CScrollMgr::DestroyInstance();
}

void CMainGame::InsertImg()
{
	//BackGround
	CImgMgr::GetInstance()->InsertImg(L"../Resource/BackGround/Logo.png", L"Logo");
	CImgMgr::GetInstance()->InsertImg(L"../Resource/BackGround/black_bg.png", L"black_bg");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/BackGround/black_bg.bmp", L"black_bg1");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/BackGround/black_bg.bmp", L"black_bg2");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/BackGround/black_bg.bmp", L"black_bg3");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/BackGround/black_bg.bmp", L"black_bg4");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/BackGround/menu_background.bmp", L"menu_background");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/BackGround/edit_background.bmp", L"edit_background");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/BackGround/stage_background.bmp", L"stage_background");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/BackGround/stage_background2.bmp", L"stage_background2");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/BackGround/stage2.bmp", L"stage2");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/BackGround/shop.bmp", L"shop");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/BackGround/stage3.bmp", L"stage3");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/BackGround/LogIn.bmp", L"LogIn");


	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Maple/BackGround/MBackGround.bmp", L"MBackGround");

	//Button
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Button/bmp/button_edit.bmp", L"button_edit");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Button/bmp/button_save.bmp", L"button_save");

	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Button/bmp/button_exitEdit.bmp", L"button_exitEdit");

	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Button/bmp/button_creator.bmp", L"button_creator");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Button/bmp/button_fastStart.bmp", L"button_fastStart");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Button/bmp/button_stageStart.bmp", L"button_stageStart");

	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Button/bmp/button_FirstStage.bmp", L"button_FirstStage");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Button/bmp/button_SecondStage.bmp", L"button_SecondStage");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Button/bmp/button_ThirdStage.bmp", L"button_ThirdStage");

	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Button/bmp/button_stageExit.bmp", L"button_stageExit");

	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Button/bmp/button_back.bmp", L"button_back");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Button/bmp/button_shop.bmp", L"button_shop");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Button/bmp/button_buy.bmp", L"button_buy0");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Button/bmp/button_buy.bmp", L"button_buy1");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Button/bmp/button_buy.bmp", L"button_buy2");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Button/bmp/button_buy.bmp", L"button_buy3");

	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Button/bmp/button_InvenExit.bmp", L"button_InvenExit");

	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Button/bmp/button_myPage.bmp", L"button_myPage");

	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Button/bmp/Login_2P.bmp", L"Login_2P");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Button/bmp/Login_1P.bmp", L"Login_1P");


	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Button/bmp/button_exit.bmp", L"button_exit");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Button/bmp/button_ReLogin.bmp", L"button_ReLogin");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Button/bmp/button_ExitGame.bmp", L"button_ExitGame");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Button/bmp/button_ExitNotice.bmp", L"button_ExitNotice");


	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Button/bmp/button_SelectPlayer.bmp", L"button_SelectPlayer1");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Button/bmp/button_SelectPlayer.bmp", L"button_SelectPlayer2");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Button/bmp/button_ExitSelectPlayer.bmp", L"button_ExitSelectPlayer");

	//Player
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Maple/Player/Player_LEFT.bmp", L"Player_LEFT");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Maple/Player/Player_RIGHT.bmp", L"Player_RIGHT");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Maple/Player/Player_ROPE.bmp", L"Player_ROPE");

	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Player/player_start.bmp", L"player_start");

	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Player/kart_up.bmp", L"kart_up");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Player/kart_right.bmp", L"kart_right");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Player/kart_left.bmp", L"kart_left");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Player/kart_down.bmp", L"kart_down");

	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Player/kart_dismount.bmp", L"kart_dismount");

	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Player/player_down.bmp", L"player_down");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Player/player_up.bmp", L"player_up");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Player/player_left.bmp", L"player_left");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Player/player_right.bmp", L"player_right");


	CImgMgr::GetInstance()->InsertImg(L"../Resource/Player/player_down.png", L"player_down");
	CImgMgr::GetInstance()->InsertImg(L"../Resource/Player/player_up.png", L"player_up");
	CImgMgr::GetInstance()->InsertImg(L"../Resource/Player/player_left.png", L"player_left");
	CImgMgr::GetInstance()->InsertImg(L"../Resource/Player/player_right.png", L"player_right");

	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Player/player_hit.bmp", L"player_hit");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Player/player_death.bmp", L"player_death");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Player/player_live.bmp", L"player_live");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Player/player_win.bmp", L"player_win");


	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Player/player_start2.bmp", L"player_start2");

	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Player/player_down2.bmp", L"player_down2");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Player/player_up2.bmp", L"player_up2");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Player/player_left2.bmp", L"player_left2");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Player/player_right2.bmp", L"player_right2");

	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Player/kart_up2.bmp", L"kart_up2");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Player/kart_right2.bmp", L"kart_right2");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Player/kart_left2.bmp", L"kart_left2");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Player/kart_down2.bmp", L"kart_down2");

	CImgMgr::GetInstance()->InsertImg(L"../Resource/Player/player_down2.png", L"player_down2");
	CImgMgr::GetInstance()->InsertImg(L"../Resource/Player/player_up2.png", L"player_up2");
	CImgMgr::GetInstance()->InsertImg(L"../Resource/Player/player_left2.png", L"player_left2");
	CImgMgr::GetInstance()->InsertImg(L"../Resource/Player/player_right2.png", L"player_right2");

	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Player/player_hit2.bmp", L"player_hit2");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Player/player_death2.bmp", L"player_death2");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Player/player_live2.bmp", L"player_live2");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Player/player_win2.bmp", L"player_win2");

	//Tile
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Tile/tile.bmp", L"tile");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Tile/tile_hit.bmp", L"tile_hit");

	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Tile/tile_base1.bmp", L"tile_base1");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Tile/tile_base2.bmp", L"tile_base2");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Tile/tile_base3.bmp", L"tile_base3");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Tile/tile_base4.bmp", L"tile_base4");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Tile/tile_final.bmp", L"tile_final");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Tile/tile_start.bmp", L"tile_start");


	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Tile/tile_base1_1.bmp", L"tile_base1_1");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Tile/tile_base1_2.bmp", L"tile_base1_2");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Tile/tile_base2_1.bmp", L"tile_base2_1");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Tile/tile_base2_2.bmp", L"tile_base2_2");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Tile/tile_base3_1.bmp", L"tile_base3_1");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Tile/tile_base3_2.bmp", L"tile_base3_2");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Tile/tile_base4_1.bmp", L"tile_base4_1");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Tile/tile_base4_2.bmp", L"tile_base4_2");


	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Tile/tile_start1.bmp", L"tile_start1");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Tile/tile_start2.bmp", L"tile_start2");

	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/GasStation/GasStation.bmp", L"GasStation");

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
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Item/new/joystick.bmp", L"joystick");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Item/new/blur.bmp", L"blur");

	//Monster
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Monster/Bean_Monster_Start.bmp", L"Bean_Monster_Start");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Monster/Bean_Monster_Death.bmp", L"Bean_Monster_Death");

	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Monster/Bean_Monster_Down.bmp", L"Bean_Monster_Down");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Monster/Bean_Monster_Left.bmp", L"Bean_Monster_Left");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Monster/Bean_Monster_Right.bmp", L"Bean_Monster_Right");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Monster/Bean_Monster_Up.bmp", L"Bean_Monster_Up");


	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Monster/Bean_Monster_Start2.bmp", L"Bean_Monster_Start2");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Monster/Bean_Monster_Death2.bmp", L"Bean_Monster_Death2");

	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Monster/Bean_Monster_Down2.bmp", L"Bean_Monster_Down2");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Monster/Bean_Monster_Left2.bmp", L"Bean_Monster_Left2");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Monster/Bean_Monster_Right2.bmp", L"Bean_Monster_Right2");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Monster/Bean_Monster_Up2.bmp", L"Bean_Monster_Up2");

	//Item_UI
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/UI/UI_Bomb.bmp", L"UI_Bomb");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/UI/UI_Liquid2.bmp", L"UI_Liquid2");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/UI/UI_Skate.bmp", L"UI_Skate");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/UI/Bulla_Num.bmp", L"Bulla_Num");

	//Numver_UI
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/UI/Timer/numbers.bmp", L"numbers");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/UI/Timer/TimerNumbers.bmp", L"TimerNumbers");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/UI/Timer/Time.bmp", L"Time");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/UI/Timer/Dot.bmp", L"Dot");

	//Inventory_UI
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/UI/MyPage.bmp", L"MyPage");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/UI/MyPage1P.bmp", L"MyPage1P");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/UI/MyPage2P-1.bmp", L"MyPage2P-1");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/UI/MyPage2P-2.bmp", L"MyPage2P-2");


	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/UI/Slot1.bmp", L"Slot1");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/UI/Slot2.bmp", L"Slot2");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/UI/Slot3.bmp", L"Slot3");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/UI/Slot4.bmp", L"Slot4");

	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/UI/InvenItem.bmp", L"InvenItem");

	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/UI/InGameSlot.bmp", L"InGameSlot");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/UI/InGameNumber.bmp", L"InGameNumber");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/UI/InGameNumber2.bmp", L"InGameNumber2");

	//Notice_UI
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/UI/Notice.bmp", L"Notice");

	//SelectPlayer
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/UI/UserSelect.bmp", L"UserSelect");

	//Control_2P
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/UI/Control_2P.bmp", L"Control_2P");

	//trackCnt_UI
	CImgMgr::GetInstance()->InsertImg(L"../Resource/UI/trackCnt.bmp", L"trackCnt");
	CImgMgr::GetInstance()->InsertImg(L"../Resource/UI/trackCnt2.bmp", L"trackCnt2");

	//gasBar_UI
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/UI/gas_frame.bmp", L"gas_frame");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/UI/gas_frame2.bmp", L"gas_frame2");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/UI/gas_bar.bmp", L"gas_bar");
	
	//Arrow_UI
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/UI/PlayerArrow2.bmp", L"PlayerArrow2");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/UI/UI_Respawn.bmp", L"UI_Respawn");
	

	//Ctrl_slot
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/UI/stage_ctrlItem.bmp", L"stage_ctrlItem");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/UI/stage_ctrlItemP1.bmp", L"stage_ctrlItemP1");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/UI/stage_ctrlItemP2.bmp", L"stage_ctrlItemP2");

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

	//StartEffect

	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/GameStart/game_start_s.bmp", L"game_start_s");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/GameStart/game_start_t.bmp", L"game_start_t");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/GameStart/game_start_a.bmp", L"game_start_a");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/GameStart/game_start_r.bmp", L"game_start_r");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/GameStart/game_start_mark.bmp", L"game_start_mark");
}
