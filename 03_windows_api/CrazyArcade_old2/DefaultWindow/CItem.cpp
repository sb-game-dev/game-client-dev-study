#include "pch.h"
#include "CItem.h"
#include "CBmpMgr.h"

CItem::CItem()
{
}

CItem::~CItem()
{
}

void CItem::Initialize()
{
	m_tInfo.fCX = 40.f;
	m_tInfo.fCY = 40.f;
	CBmpMgr::GetInstance()->InsertBmp(L"../Image/크레이지 아케이드 리소스/Resource/Item/Item_0.bmp", L"IT_Bomb");
	CBmpMgr::GetInstance()->InsertBmp(L"../Image/크레이지 아케이드 리소스/Resource/Item/Item_1.bmp", L"IT_Power");
	CBmpMgr::GetInstance()->InsertBmp(L"../Image/크레이지 아케이드 리소스/Resource/Item/Item_2.bmp", L"IT_Speed");
	CBmpMgr::GetInstance()->InsertBmp(L"../Image/크레이지 아케이드 리소스/Resource/Item/Item_3.bmp", L"IT_Needle");
}

int CItem::Update()
{
	if (m_bDead == DEAD)
		return DEAD;
	return NONEVENT;
}

void CItem::LateUpdate()
{
}

void CItem::Render(HDC hDC)
{
	HDC hMemDC = nullptr;
	switch (m_eType)
	{
	case IT_BOMB_UP:
		hMemDC = CBmpMgr::GetInstance()->FindImage(L"IT_Bomb");
		break;
	case IT_POWER_UP:
		hMemDC = CBmpMgr::GetInstance()->FindImage(L"IT_Power");
		break;
	case IT_SPEED_UP:
		hMemDC = CBmpMgr::GetInstance()->FindImage(L"IT_Speed");
		break;
	case IT_NEEDLE:
		hMemDC = CBmpMgr::GetInstance()->FindImage(L"IT_Needle");
		break;
	}
	GdiTransparentBlt(hDC,
		m_tRect.left,
		m_tRect.top,
		38,//(int)m_tInfo.fCX
		38,//(int)m_tInfo.fCY
		hMemDC,
		m_tRenderInfo.iRectStartX + 70 * m_iFrame,
		m_tRenderInfo.iRectStartY,
		38,//(int)m_tInfo.fCX
		38,//(int)m_tInfo.fCY
		RGB(255, 255, 255));
}

void CItem::Release()
{
}
