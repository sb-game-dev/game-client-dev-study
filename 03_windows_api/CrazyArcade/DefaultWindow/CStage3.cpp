#include "pch.h"
#include "CStage3.h"
#include "CObjMgr.h"
#include "CAbstractFactory.h"
#include "CPlayer.h"
#include "CImgMgr.h"
CStage3::CStage3()
{
}

CStage3::~CStage3()
{
	Release();
}

void CStage3::Initialize()
{
	CImgMgr::GetInstance()->InsertImg(L"../Resource/BackGround/stage_background.png", L"stage_background");
	CObjMgr::GetInstance()->AddObject(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create(WINCX * 0.5f, WINCY * 0.5f, L"player_start"));
	CObjMgr::GetInstance()->LoadTile();
	
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
	Graphics* _pGraphics = Graphics::FromHDC(hDC);

	Gdiplus::Image* pGround = CImgMgr::GetInstance()->FindImg(L"stage_background");
	Rect rect = { 0,0,WINCX,WINCY };
	_pGraphics->DrawImage(pGround, rect, 0, 0, WINCX, WINCY, UnitPixel);

	CObjMgr::GetInstance()->Render(hDC);
}

void CStage3::Release()
{
}
