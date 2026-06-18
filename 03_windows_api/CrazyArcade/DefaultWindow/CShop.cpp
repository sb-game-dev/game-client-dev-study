#include "pch.h"
#include "CShop.h"
#include "CObjMgr.h"
#include "CAbstractFactory.h"
#include "CSceneMgr.h"
#include "CSoundMgr.h"
#include "CButton.h"
#include "CBmpMgr.h"
#include "CInven.h"

CShop::CShop()
{
}

CShop::~CShop()
{
	Release();
}

void CShop::Initialize()
{
	CObjMgr::GetInstance()->AddObject(OBJ_BUTTON, CAbstractFactory<CButton>::Create(224, 420, L"button_buy0"));
	CObjMgr::GetInstance()->AddObject(OBJ_BUTTON, CAbstractFactory<CButton>::Create(455, 420, L"button_buy1"));
	CObjMgr::GetInstance()->AddObject(OBJ_BUTTON, CAbstractFactory<CButton>::Create(224, 517, L"button_buy2"));
	CObjMgr::GetInstance()->AddObject(OBJ_BUTTON, CAbstractFactory<CButton>::Create(455, 517, L"button_buy3"));

	CObjMgr::GetInstance()->AddObject(OBJ_BUTTON, CAbstractFactory<CButton>::Create(117, 585, L"button_back"));
}

int CShop::Update()
{
	//int iMoney = CInven::GetInstance()->GetGold();
	//cout << iMoney << endl;
	CObjMgr::GetInstance()->Update();
	return 0;
}

void CShop::LateUpdate()
{
	CObjMgr::GetInstance()->LateUpdate();
}

void CShop::Render(HDC hDC)
{
	HDC hBackGround = CBmpMgr::GetInstance()->FindImage(L"shop");
	BitBlt(hDC,							// 목적지 DC
		0, 0,
		WINCX, WINCY,
		hBackGround,					// 원본 DC
		0,								// 원본 이미지에서 가져오기 시작할 좌표의 LEFT, TOP
		0,
		SRCCOPY);						// 그대로 복사하여 출력

	int iMoney = CInven::GetInstance()->GetGold();
	int iNumcnt = 0;
	while (iMoney)
	{
		
		int iNum = iMoney % 10;
		HDC hNumber = CBmpMgr::GetInstance()->FindImage(L"numbers");
		GdiTransparentBlt(hDC,					// 목적지 DC
			int(307-11)-22*iNumcnt,	// 목적지 LEFT, TOP
			int(15),
			22,			// 목적지 공간의 가로, 세로 사이즈
			26,
			hNumber,						// 원본 이미지 DC
			22 * iNum,	// 원본 이미지 LEFT, TOP
			0,
			22,				// 원본 이미지 가로, 세로 사이즈
			26,		
			RGB(255, 0, 255));		// 제거할 픽셀 색상
		++iNumcnt;
		iMoney /= 10;
	}
	CObjMgr::GetInstance()->Render(hDC);
}

void CShop::Release()
{
	CObjMgr::GetInstance()->ReleaseRenderList();
	CObjMgr::GetInstance()->DeleteObj(OBJ_BUTTON);
	CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
}
