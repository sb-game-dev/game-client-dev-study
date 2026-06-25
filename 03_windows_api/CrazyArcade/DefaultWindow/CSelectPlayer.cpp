#include "pch.h"
#include "CSelectPlayer.h"
#include "CBmpMgr.h"

CSelectPlayer* CSelectPlayer::m_pInstance = nullptr;

CSelectPlayer::CSelectPlayer(): m_bDraw(false)
{
}

CSelectPlayer::~CSelectPlayer()
{
}

void CSelectPlayer::Update()
{

}
void CSelectPlayer::LateUpdate()
{

}
void CSelectPlayer::Render(HDC hDC)
{
	if (m_bDraw == false)
		return;

	HDC hSelect = CBmpMgr::GetInstance()->FindImage(L"UserSelect");
	GdiTransparentBlt(hDC, 240, 174, 320, 252, hSelect, 0, 0, 320, 252, RGB(255, 0, 255));
}
void CSelectPlayer::Release()
{

}


