#include "pch.h"
#include "CEdit.h"
#include "CImgMgr.h"
#include "CObjMgr.h"
#include "CButton.h"
#include "CAbstractFactory.h"
#include "CKeyMgr.h"

CEdit::CEdit()
{
}

CEdit::~CEdit()
{
	Release();
}

void CEdit::Initialize()
{
	CImgMgr::GetInstance()->InsertImg(L"../Resource/BackGround/edit_background.png", L"edit_background");

	CObjMgr::GetInstance()->AddObject(OBJ_BUTTON, CAbstractFactory<CButton>::Create(657, 277, L"button_edit", PUSH));
	CObjMgr::GetInstance()->AddObject(OBJ_BUTTON, CAbstractFactory<CButton>::Create(693, 277, L"button_edit", BREAK));
	CObjMgr::GetInstance()->AddObject(OBJ_BUTTON, CAbstractFactory<CButton>::Create(731, 277, L"button_edit", WALL1));
	CObjMgr::GetInstance()->AddObject(OBJ_BUTTON, CAbstractFactory<CButton>::Create(763, 277, L"button_edit", WALL2));

	CObjMgr::GetInstance()->AddObject(OBJ_BUTTON, CAbstractFactory<CButton>::Create(657, 312, L"button_edit", WALL3));
	CObjMgr::GetInstance()->AddObject(OBJ_BUTTON, CAbstractFactory<CButton>::Create(693, 312, L"button_edit", WALL4));
	CObjMgr::GetInstance()->AddObject(OBJ_BUTTON, CAbstractFactory<CButton>::Create(731, 312, L"button_edit", WALL5));
	CObjMgr::GetInstance()->AddObject(OBJ_BUTTON, CAbstractFactory<CButton>::Create(763, 312, L"button_edit", WALL6));
	
	CObjMgr::GetInstance()->AddObject(OBJ_BUTTON, CAbstractFactory<CButton>::Create(657, 348, L"button_edit", WALL7));

	for (int i = 0; i < 13; ++i)
	{
		for (int j = 0; j < 15; ++j)
		{
			CObjMgr::GetInstance()->AddTile(CAbstractFactory<CTile>::Create((j * 40) + 40, (i * 40) + 60, L"tile", TILE1));
		}
	}
}

int CEdit::Update()
{
	CObjMgr::GetInstance()->Update();
    return 0;
}

void CEdit::LateUpdate()
{
	CObjMgr::GetInstance()->LateUpdate();
	if (CKeyMgr::GetInstance()->KeyDown('S'))
		CObjMgr::GetInstance()->SaveTile(0);

	else if (CKeyMgr::GetInstance()->KeyDown('1'))
		CObjMgr::GetInstance()->SaveTile(1);

	else if (CKeyMgr::GetInstance()->KeyDown('2'))
		CObjMgr::GetInstance()->SaveTile(2);

	else if (CKeyMgr::GetInstance()->KeyDown('3'))
		CObjMgr::GetInstance()->SaveTile(3);

	else if (CKeyMgr::GetInstance()->KeyDown('L'))
		CObjMgr::GetInstance()->LoadTile();
}

void CEdit::Render(HDC hDC)
{
	Graphics* _pGraphics = Graphics::FromHDC(hDC);

	Gdiplus::Image* pBackGround = CImgMgr::GetInstance()->FindImg(L"edit_background");
	Rect rect = { 0,0,WINCX,WINCY};
	_pGraphics->DrawImage(pBackGround, rect,
		0,0,
		WINCX, WINCY,
		UnitPixel);

	CObjMgr::GetInstance()->Render(hDC);
}

void CEdit::Release()
{
}
