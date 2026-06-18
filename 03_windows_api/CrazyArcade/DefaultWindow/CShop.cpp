#include "pch.h"
#include "CShop.h"
#include "CObjMgr.h"
#include "CAbstractFactory.h"
#include "CSceneMgr.h"
#include "CSoundMgr.h"
#include "CButton.h"
#include "CBmpMgr.h"

CShop::CShop()
{
}

CShop::~CShop()
{
	Release();
}

void CShop::Initialize()
{
	//CObjMgr::GetInstance()->AddObject(OBJ_BUTTON, CAbstractFactory<CButton>::Create(717, 576, L"button_buy"));
	//CObjMgr::GetInstance()->AddObject(OBJ_BUTTON, CAbstractFactory<CButton>::Create(717, 576, L"button_back"));
}

int CShop::Update()
{
	return 0;
}

void CShop::LateUpdate()
{
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
}

void CShop::Release()
{
}
