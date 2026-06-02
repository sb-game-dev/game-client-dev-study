#include "pch.h"
#include "CStage.h"
#include "CObjMgr.h"
#include "CAbstractFactory.h"
#include "CPlayer.h"
#include "CBlock.h"
#include "CBmpMgr.h"
#include "time.h"
void CStage::Initialize()
{
	m_iWallCnt = 0;
	CObjMgr::GetInstance()->AddObject(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create());
	//srand(unsigned((time)));
	for (int i = 0; i < 15; ++i)
	{
		for (int j = 0; j < 12; ++j)
		{
			if (rand() % 10 < 2)
			{
				m_iWallCnt++;
				int iRandNum = rand() % 3;
				switch (iRandNum)
				{
				case 0:
					CObjMgr::GetInstance()->AddObject(OBJ_BLOCK, CAbstractFactory<CBlock>::Create(float(i * 40 + 20), float(j * 40 + 60), L"Push"));
					break;
				case 1:
					CObjMgr::GetInstance()->AddObject(OBJ_BLOCK, CAbstractFactory<CBlock>::Create(float(i * 40 + 20), float(j * 40 + 60), L"Break"));
					break;
				case 2:
					CObjMgr::GetInstance()->AddObject(OBJ_BLOCK, CAbstractFactory<CBlock>::Create(float(i * 40 + 20), float(j * 40 + 60), L"Wall"));
					break;
				default:
					break;
				}
				
			}
		}
	}
	CBmpMgr::GetInstance()->InsertBmp(L"../Image/크레이지 아케이드 리소스/Resource/Stage1.bmp", L"Ground");
}

int CStage::Update()
{
	CObjMgr::GetInstance()->Update();
    return 0;
}

void CStage::LateUpdate()
{
	CObjMgr::GetInstance()->LateUpdate();
}

void CStage::Render(HDC hDC)
{
	HDC	hGround = CBmpMgr::GetInstance()->FindImage(L"Ground");
	BitBlt(hDC, 0, 0, WINCX, WINCY, hGround, 0, 0, SRCCOPY);
	//TCHAR	szBuff[32] = L"";
	//swprintf_s(szBuff, L"Bullet : %d", m_iWallCnt);
	//TextOut(hDC, 50, 50, szBuff, lstrlen(szBuff));
	CObjMgr::GetInstance()->Render(hDC);
}

void CStage::Release()
{
}
