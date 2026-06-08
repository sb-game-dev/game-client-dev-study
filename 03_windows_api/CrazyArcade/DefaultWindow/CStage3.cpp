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
}

void CStage3::Initialize()
{
	CImgMgr::GetInstance()->InsertImg(L"../Resource/BackGround/stage_background.png", L"stage_background");
	CImgMgr::GetInstance()->InsertImg(L"../Resource/BackGround/iceMap.png", L"iceMap");
	CObjMgr::GetInstance()->AddObject(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create(WINCX * 0.5f, WINCY * 0.5f, L"player_start"));
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

void CStage3::Render(Graphics* _pGraphics)
{
	Gdiplus::Image* pGround = CImgMgr::GetInstance()->FindImg(L"stage_background");
	Gdiplus::Image* pTotalTile = CImgMgr::GetInstance()->FindImg(L"iceMap");
	Rect rect = { 0,0,WINCX,WINCY };
	_pGraphics->DrawImage(pGround, rect, 0, 0, WINCX, WINCY, UnitPixel);
	rect = { 20,40,600,520 };
	_pGraphics->DrawImage(pTotalTile, rect, 0, 0, 600, 520, UnitPixel);
	CObjMgr::GetInstance()->Render(_pGraphics);
}

void CStage3::Release()
{
}
