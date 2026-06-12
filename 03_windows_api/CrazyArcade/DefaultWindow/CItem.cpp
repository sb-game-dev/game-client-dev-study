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

	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 1;
	m_tFrame.iMotion = 0;
	m_tFrame.iCX = 40;
	m_tFrame.iCY = 40;

	m_eRenderID = GAMEOBJECT;
}

int CItem::Update()
{
	if (m_bDead == DEAD)
		return DEAD;
	return 0;
}

void CItem::LateUpdate()
{
}

void CItem::Render(HDC hDC)
{
	HDC hItem = CBmpMgr::GetInstance()->FindImage(m_pFrameKey);
	GdiTransparentBlt(hDC,			// 목적지 DC
		int(m_tInfo.fX - (m_tFrame.iCX * 0.5)),
		int(m_tInfo.fY - (m_tFrame.iCY - m_tInfo.fCY * 0.5)),
		m_tFrame.iCX,				// 목적지 공간의 가로, 세로 사이즈
		m_tFrame.iCY,
		hItem,						// 원본 이미지 DC
		m_tFrame.iCX * m_tFrame.iStart,// 원본 이미지 LEFT, TOP
		0,
		m_tFrame.iCX,			// 원본 이미지 가로, 세로 사이즈
		m_tFrame.iCY,
		RGB(255, 0, 255));		// 제거할 픽셀 색상
}

void CItem::Release()
{
}
