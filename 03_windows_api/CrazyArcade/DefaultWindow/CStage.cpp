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
	
	//CBmpMgr::GetInstance()->InsertBmp(L"../Image/크레이지 아케이드 리소스/Resource/Block/block_v2.bmp", L"Push");
	//CBmpMgr::GetInstance()->InsertBmp(L"../Image/크레이지 아케이드 리소스/Resource/Block/block_v1.bmp", L"Break");
	//CBmpMgr::GetInstance()->InsertBmp(L"../Image/크레이지 아케이드 리소스/Resource/Block/Wall_f1.bmp", L"Wall");
	//CObjMgr::GetInstance()->AddObject(OBJ_BLOCK, CAbstractFactory<CBlock>::Create(float(600), float(550), L"Push"));

	//srand(unsigned((time)));
	//for (int i = 0; i < 15; ++i)
	//{
	//	for (int j = 0; j < 13; ++j)
	//	{
	//		if (1)//rand() % 10 < 2)
	//		{
	//			m_iWallCnt++;
	//			int iRandNum = rand() % 3;
	//			switch (iRandNum)
	//			{
	//			case 0:
	//				CObjMgr::GetInstance()->AddObject(OBJ_BLOCK, CAbstractFactory<CBlock>::Create(float(i * 40 + 35), float(j * 40 + 60), L"Push"));
	//				break;
	//			case 1:
	//				CObjMgr::GetInstance()->AddObject(OBJ_BLOCK, CAbstractFactory<CBlock>::Create(float(i * 40 + 35), float(j * 40 + 60), L"Break"));
	//				break;
	//			case 2:
	//				CObjMgr::GetInstance()->AddObject(OBJ_BLOCK, CAbstractFactory<CBlock>::Create(float(i * 40 + 35), float(j * 40 + 60), L"Wall"));
	//				break;
	//			default:
	//				break;
	//			}
	//			
	//		}
	//	}
	//}
	CBmpMgr::GetInstance()->InsertBmp(L"../Image/크레이지 아케이드 리소스/Resource/Stage1.bmp", L"Ground");
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


	CCollisionMgr::CollisionBody(CTileMgr::GetInstance()->GetTile(), CObjMgr::GetInstance()->GetList(OBJ_PLAYER));


	CObjMgr::GetInstance()->LateUpdate();
}

void CStage::Render(HDC hDC)
{
	HDC	hGround = CBmpMgr::GetInstance()->FindImage(L"Ground");
	BitBlt(hDC, 0, 0, WINCX, WINCY, hGround, 0, 0, SRCCOPY);
	//TCHAR	szBuff[32] = L"";
	//swprintf_s(szBuff, L"Bullet : %d", m_iWallCnt);
	//TextOut(hDC, 50, 50, szBuff, lstrlen(szBuff));

	CTileMgr::GetInstance()->Render(hDC);
	CObjMgr::GetInstance()->Render(hDC);
}

void CStage::Release()
{
}
