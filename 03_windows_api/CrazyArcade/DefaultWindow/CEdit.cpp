#include "pch.h"
#include "CEdit.h"
#include "CImgMgr.h"
#include "CObjMgr.h"
#include "CButton.h"
#include "CAbstractFactory.h"
#include "CKeyMgr.h"
#include "CBmpMgr.h"
#include "CMouse.h"

CEdit::CEdit()
{
}

CEdit::~CEdit()
{
	Release();
}

void CEdit::Initialize()
{
	CObjMgr::GetInstance()->AddObject(OBJ_BUTTON, CAbstractFactory<CButton>::Create(657, 277, L"button_edit", PUSH));
	CObjMgr::GetInstance()->AddObject(OBJ_BUTTON, CAbstractFactory<CButton>::Create(693, 277, L"button_edit", BREAK));
	CObjMgr::GetInstance()->AddObject(OBJ_BUTTON, CAbstractFactory<CButton>::Create(731, 277, L"button_edit", WALL1));
	CObjMgr::GetInstance()->AddObject(OBJ_BUTTON, CAbstractFactory<CButton>::Create(763, 277, L"button_edit", WALL2));

	CObjMgr::GetInstance()->AddObject(OBJ_BUTTON, CAbstractFactory<CButton>::Create(657, 312, L"button_edit", WALL3));
	CObjMgr::GetInstance()->AddObject(OBJ_BUTTON, CAbstractFactory<CButton>::Create(693, 312, L"button_edit", WALL4));
	CObjMgr::GetInstance()->AddObject(OBJ_BUTTON, CAbstractFactory<CButton>::Create(731, 312, L"button_edit", WALL5));
	CObjMgr::GetInstance()->AddObject(OBJ_BUTTON, CAbstractFactory<CButton>::Create(763, 312, L"button_edit", WALL6));

	CObjMgr::GetInstance()->AddObject(OBJ_BUTTON, CAbstractFactory<CButton>::Create(657, 348, L"button_edit", WALL7));



	CObjMgr::GetInstance()->AddObject(OBJ_BUTTON, CAbstractFactory<CButton>::Create(693, 348, L"button_edit", STAGE2TILE1));
	CObjMgr::GetInstance()->AddObject(OBJ_BUTTON, CAbstractFactory<CButton>::Create(731, 348, L"button_edit", STAGE2TILE2));
	CObjMgr::GetInstance()->AddObject(OBJ_BUTTON, CAbstractFactory<CButton>::Create(763, 348, L"button_edit", STAGE2TILE3));


	CObjMgr::GetInstance()->AddObject(OBJ_BUTTON, CAbstractFactory<CButton>::Create(657, 384, L"button_edit", STAGE2TILE4));
	CObjMgr::GetInstance()->AddObject(OBJ_BUTTON, CAbstractFactory<CButton>::Create(693, 384, L"button_edit", STAGE2TILE5));
	CObjMgr::GetInstance()->AddObject(OBJ_BUTTON, CAbstractFactory<CButton>::Create(731, 384, L"button_edit", STAGE2TILE6));
	CObjMgr::GetInstance()->AddObject(OBJ_BUTTON, CAbstractFactory<CButton>::Create(763, 384, L"button_edit", STAGE2TILE7));


	CObjMgr::GetInstance()->AddObject(OBJ_BUTTON, CAbstractFactory<CButton>::Create(657, 420, L"button_edit", STAGE2TILE8));
	CObjMgr::GetInstance()->AddObject(OBJ_BUTTON, CAbstractFactory<CButton>::Create(693, 420, L"button_edit", STAGE2TILE9));




	CObjMgr::GetInstance()->AddObject(OBJ_BUTTON, CAbstractFactory<CButton>::Create(716, 577, L"button_save"));


	CObjMgr::GetInstance()->AddObject(OBJ_BUTTON, CAbstractFactory<CButton>::Create(25, 16, L"button_exitEdit"));

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

	else if (CKeyMgr::GetInstance()->KeyDown('4'))
		CObjMgr::GetInstance()->SaveTile(4);

	else if (CKeyMgr::GetInstance()->KeyDown('L'))
		CObjMgr::GetInstance()->LoadTile();
}

void CEdit::Render(HDC hDC)
{
	HDC hBackGround = CBmpMgr::GetInstance()->FindImage(L"edit_background");

	BitBlt(hDC,							    // 목적지 DC
		0, 0,
		WINCX, WINCY,
		hBackGround,							// 원본 DC
		0,								// 원본 이미지에서 가져오기 시작할 좌표의 LEFT, TOP
		0,
		SRCCOPY);						// 그대로 복사하여 출력

	CObjMgr::GetInstance()->Render(hDC);
}

void CEdit::Release()
{
	CObjMgr::GetInstance()->ReleaseRenderList();
	CObjMgr::GetInstance()->DeleteObj(OBJ_BUTTON);
	dynamic_cast<CMouse*>(CObjMgr::GetInstance()->GetList(OBJ_MOUSE).front())->SetChoiceTile(TILE_END);
}

