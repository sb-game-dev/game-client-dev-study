#include "pch.h"
#include "CEdit.h"
#include "CImgMgr.h"
#include "CObjMgr.h"
#include "CButton.h"
#include "CAbstractFactory.h"

CEdit::CEdit()
{
}

CEdit::~CEdit()
{
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

}

int CEdit::Update()
{
	CObjMgr::GetInstance()->Update();
    return 0;
}

void CEdit::LateUpdate()
{
	CObjMgr::GetInstance()->LateUpdate();
}

void CEdit::Render(Graphics* _pGraphics)
{
	Gdiplus::Image* pBackGround = CImgMgr::GetInstance()->FindImg(L"edit_background");

	Rect rect = { 0,0,
				WINCX,
				WINCY};

	//ImageAttributes attr;
	//attr.SetColorKey(
	//	Color(255, 0, 255),
	//	Color(255, 0, 255));

	_pGraphics->DrawImage(pBackGround, rect,
		0,0,
		WINCX, WINCY,
		UnitPixel);


	CObjMgr::GetInstance()->Render(_pGraphics);
}

void CEdit::Release()
{
}
