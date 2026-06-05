#include "pch.h"
#include "CLogo.h"
#include "CBmpMgr.h"
#include "CObj.h"
#include "CAbstractFactory.h"
#include "CButton.h"
#include "CObjMgr.h"
CLogo::CLogo()
{
}

CLogo::~CLogo()
{
	Release();
}

void CLogo::Initialize()
{
	CBmpMgr::GetInstance()->InsertBmp(L"../Image/크레이지 아케이드 리소스/Resource/BackGround.bmp", L"Login");

	CBmpMgr::GetInstance()->InsertBmp(L"../Image/크레이지 아케이드 리소스/Resource/Button/start3.bmp", L"Start_Button");
	CBmpMgr::GetInstance()->InsertBmp(L"../Image/크레이지 아케이드 리소스/Resource/Button/exit3.bmp", L"Exit_Button");
	CBmpMgr::GetInstance()->InsertBmp(L"../Image/크레이지 아케이드 리소스/Resource/Button/edit3.bmp", L"Edit_Button");

	CObj* pButton = CAbstractFactory<CButton>::Create(191.f, 473.f);
	pButton->SetFrameKey(L"Start_Button");
	CObjMgr::GetInstance()->AddObject(OBJ_UI, pButton);

	pButton = CAbstractFactory<CButton>::Create(610.f, 473.f);
	pButton->SetFrameKey(L"Exit_Button");
	CObjMgr::GetInstance()->AddObject(OBJ_UI, pButton);

	pButton = CAbstractFactory<CButton>::Create(400.f, 577.f);
	pButton->SetFrameKey(L"Edit_Button");
	pButton->SetSize(168.f, 34.f);

	CObjMgr::GetInstance()->AddObject(OBJ_UI, pButton);
}

int CLogo::Update()
{
	CObjMgr::GetInstance()->Update();
	return 0;
}

void CLogo::LateUpdate()
{
	CObjMgr::GetInstance()->LateUpdate();
}

void CLogo::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::GetInstance()->FindImage(L"Login");

	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
	CObjMgr::GetInstance()->Render(hDC);
}

void CLogo::Release()
{
	CObjMgr::GetInstance()->DeleteObj(OBJ_UI);
}
