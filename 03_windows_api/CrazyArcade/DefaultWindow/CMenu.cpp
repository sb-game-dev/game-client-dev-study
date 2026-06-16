#include "pch.h"
#include "CMenu.h"
#include "CImgMgr.h"
#include "CBmpMgr.h"
#include "CObjMgr.h"
#include "CButton.h"
#include "CAbstractFactory.h"
#include "CSoundMgr.h"

CMenu::CMenu()
{
}

CMenu::~CMenu()
{
	Release();
}

void CMenu::Initialize()
{
	InsertImg();

	CObjMgr::GetInstance()->AddObject(OBJ_BUTTON, CAbstractFactory<CButton>::Create(722, 36, L"button_creator"));
	CObjMgr::GetInstance()->AddObject(OBJ_BUTTON, CAbstractFactory<CButton>::Create(296, 36, L"button_fastStart"));
	srand(unsigned(time(NULL)));
	if(rand()%2 == 1)
		CSoundMgr::Get_Instance()->PlayBGM(L"Channel.wav", 0.1f);
	else
		CSoundMgr::Get_Instance()->PlayBGM(L"Lobby.wav", 0.1f);

}

int CMenu::Update()
{
	CObjMgr::GetInstance()->Update();
	return 0;
}

void CMenu::LateUpdate()
{

	CObjMgr::GetInstance()->LateUpdate();
}

void CMenu::Render(HDC hDC)
{
	HDC hBackGround = CBmpMgr::GetInstance()->FindImage(L"menu_background");

	BitBlt(hDC,							// 목적지 DC
		0, 0,
		WINCX, WINCY,
		hBackGround,					// 원본 DC
		0,								// 원본 이미지에서 가져오기 시작할 좌표의 LEFT, TOP
		0,
		SRCCOPY);						// 그대로 복사하여 출력
	//Graphics* _pGraphics = Graphics::FromHDC(hDC);
	//Gdiplus::Image* pBlackImg = CImgMgr::GetInstance()->FindImg(L"black_bg");
	//
	//Rect rect = { 0,0,800,600 };
	//
	//ImageAttributes attr;
	//MakeAlphaAttr(attr, m_fAlpha);
	//_pGraphics->DrawImage(pBlackImg, rect, 0, 0, WINCX, WINCY, UnitPixel, &attr);
	CObjMgr::GetInstance()->Render(hDC);
}

void CMenu::Release()
{
	CObjMgr::GetInstance()->DeleteObj(OBJ_BUTTON);
	CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
}

void CMenu::InsertImg()
{
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/BackGround/menu_background.bmp", L"menu_background");
	CImgMgr::GetInstance()->InsertImg(L"../Resource/BackGround/black_bg.png", L"black_bg");

	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Button/bmp/button_creator.bmp", L"button_creator");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Button/bmp/button_fastStart.bmp", L"button_fastStart");
}
