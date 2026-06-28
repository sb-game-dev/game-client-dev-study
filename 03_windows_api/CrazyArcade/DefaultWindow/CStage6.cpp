#include "pch.h"
#include "CStage6.h"
#include "CAbstractFactory.h"
#include "CMaplePlayer.h"
#include "CBmpMgr.h"
#include "CObjMgr.h"

CStage6::CStage6()
{
}

CStage6::~CStage6()
{
}

void CStage6::Initialize()
{
	m_pPlayer = CAbstractFactory<CMaplePlayer>::Create(WINCX / 2, WINCY / 2, L"Player_RIGHT");
	CObjMgr::GetInstance()->AddObject(OBJ_PLAYER, m_pPlayer);
}

int CStage6::Update()
{
	CObjMgr::GetInstance()->Update();
	return 0;
}

void CStage6::LateUpdate()
{
	CObjMgr::GetInstance()->LateUpdate();
}

void CStage6::Render(HDC hDC)
{
	HDC hBackGround = CBmpMgr::GetInstance()->FindImage(L"MBackGround");
	BitBlt(hDC,
		0, 0,
		WINCX, WINCY,
		hBackGround,
		0,
		1080 - WINCY,
		SRCCOPY);
	CObjMgr::GetInstance()->Render(hDC);
}

void CStage6::Release()
{
}
