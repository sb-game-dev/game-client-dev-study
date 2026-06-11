#include "pch.h"
#include "CStage3.h"
#include "CObjMgr.h"
#include "CAbstractFactory.h"
#include "CPlayer.h"
#include "CImgMgr.h"
#include "CBoss.h"
#include "CBmpMgr.h"
CStage3::CStage3()
{
}

CStage3::~CStage3()
{
	Release();
}

void CStage3::Initialize()
{
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/BackGround/stage_background.bmp", L"stage_background");
	CObjMgr::GetInstance()->AddObject(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create((13 * 40) + 40, (11 * 40) + 60, L"player_start"));
	//CObjMgr::GetInstance()->AddObject(OBJ_BOSS, CAbstractFactory<CBoss>::Create((3 * 40) + 40, (9 * 40) + 60, L"Boss_down"));
	CObjMgr::GetInstance()->AddObject(OBJ_BOSS, CAbstractFactory<CBoss>::Create((3 * 40) + 40, (10 * 40) + 60, L"Boss_down"));
	CObjMgr::GetInstance()->LoadStage3();
	
	//for (int i = 0; i < 13; ++i)
	//{
	//	for (int j = 0; j < 15; ++j)
	//	{
	//		CObjMgr::GetInstance()->AddTile(CAbstractFactory<CTile>::Create((j * 40) + 40, (i * 40) + 60, L"tile", TILE1));
	//	}
	//}
}

int CStage3::Update()
{
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

	BitBlt(hDC,							    // 목적지 DC
		0,0,
		WINCX,WINCY,
		hBackGround,							// 원본 DC
		0,								// 원본 이미지에서 가져오기 시작할 좌표의 LEFT, TOP
		0,
		SRCCOPY);						// 그대로 복사하여 출력

	CObjMgr::GetInstance()->Render(hDC);
}

void CStage3::Release()
{
}
