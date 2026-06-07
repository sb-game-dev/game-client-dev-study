#include "pch.h"
#include "CStage.h"
#include "CObjMgr.h"
#include "CAbstractFactory.h"
#include "CPlayer.h"
#include "CBlock.h"
#include "CBmpMgr.h"
#include "time.h"
#include "CTileMgr.h"
#include "CCollisionMgr.h"
void CStage::Initialize()
{
	CBmpMgr::GetInstance()->InsertBmp(L"../Image/크레이지 아케이드 리소스/Resource/Block/Tile_base.bmp", L"Tile_base");
	CTileMgr::GetInstance()->LoadStage();

	CObjMgr::GetInstance()->AddObject(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create());

	CBmpMgr::GetInstance()->InsertBmp(L"../Image/크레이지 아케이드 리소스/Resource/stage_background.bmp", L"BackGround");
	CBmpMgr::GetInstance()->InsertBmp(L"../Image/크레이지 아케이드 리소스/Resource/ICEMap.bmp", L"Ground");
}

int CStage::Update()
{
	CTileMgr::GetInstance()->Update();
	CObjMgr::GetInstance()->Update();
    return 0;
}

void CStage::LateUpdate()
{

	CTileMgr::GetInstance()->LateUpdate();


	//CCollisionMgr::CollisionBody(m_ObjList[OBJ_BLOCK], m_ObjList[OBJ_PLAYER]);
	CCollisionMgr::CollisionBody(CObjMgr::GetInstance()->GetList(OBJ_BOMB), CObjMgr::GetInstance()->GetList(OBJ_PLAYER));
	CCollisionMgr::CollisionBody(CObjMgr::GetInstance()->GetList(OBJ_BOMB), CObjMgr::GetInstance()->GetList(OBJ_BLOCK));
	CCollisionMgr::CollisionBody(CTileMgr::GetInstance()->GetTile(), CObjMgr::GetInstance()->GetList(OBJ_PLAYER));


	CCollisionMgr::CollisionAttack(CObjMgr::GetInstance()->GetList(OBJ_ITEM), CObjMgr::GetInstance()->GetList(OBJ_PLAYER));
	CCollisionMgr::CollisionAttack(CObjMgr::GetInstance()->GetList(OBJ_BOMB), CObjMgr::GetInstance()->GetList(OBJ_WATER));
	CCollisionMgr::CollisionAttack(CObjMgr::GetInstance()->GetList(OBJ_PLAYER), CObjMgr::GetInstance()->GetList(OBJ_WATER));
	CCollisionMgr::CollisionAttack(CTileMgr::GetInstance()->GetTile(), CObjMgr::GetInstance()->GetList(OBJ_WATER));
	//CCollisionMgr::CollisionAttack(m_ObjList[OBJ_ITEM], m_ObjList[OBJ_WATER]);

	CObjMgr::GetInstance()->LateUpdate();
}

void CStage::Render(HDC hDC)
{
	HDC	hBackGround = CBmpMgr::GetInstance()->FindImage(L"BackGround");
	HDC	hGround = CBmpMgr::GetInstance()->FindImage(L"Ground");
	//GdiTransparentBlt(hDC,					// 목적지 DC
	//	0,	// 목적지 LEFT, TOP
	//	0,
	//	WINCX,			// 목적지 공간의 가로, 세로 사이즈
	//	WINCY,
	//	hBackGround,						// 원본 이미지 DC
	//	0,							// 원본 이미지 LEFT, TOP
	//	0,
	//	WINCX,			// 원본 이미지 가로, 세로 사이즈
	//	WINCY,
	//	RGB(255, 0, 255));		// 제거할 픽셀 색상
	BitBlt(hDC, 0, 0, WINCX, WINCY, hBackGround, 0, 0, SRCCOPY);
	//BitBlt(hDC, 19, 39, 600, 520, hGround, 0, 0, SRCCOPY);
	//TCHAR	szBuff[32] = L"";
	//swprintf_s(szBuff, L"Bullet : %d", m_iWallCnt);
	//TextOut(hDC, 50, 50, szBuff, lstrlen(szBuff));

	CTileMgr::GetInstance()->Render(hDC);
	CObjMgr::GetInstance()->Render(hDC);
}

void CStage::Release()
{
}
