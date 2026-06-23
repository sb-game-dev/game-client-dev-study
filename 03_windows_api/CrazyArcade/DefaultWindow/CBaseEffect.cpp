#include "pch.h"
#include "CBaseEffect.h"
#include "CBmpMgr.h"

CBaseEffect::CBaseEffect():m_bMoveFrame(false)
{
}

CBaseEffect::~CBaseEffect()
{
	Release();
}

void CBaseEffect::Initialize()
{
	m_eRenderID = BACKGROUND;

	if (!lstrcmp(L"tile_final", m_pFrameKey) || !lstrcmp(L"tile_start1", m_pFrameKey) || !lstrcmp(L"tile_start2", m_pFrameKey))
		m_tInfo.fCY = 80.f;
	else
		m_tInfo.fCY = 40.f;

	m_tInfo.fCX = 40.f;
	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 2;
	m_tFrame.iCX = m_tInfo.fCX;
	m_tFrame.iCY = m_tInfo.fCY;
	m_tFrame.bLoop = true;
	m_tFrame.dwTime = GetTickCount64();
	m_tFrame.dwSpeed = 200.f;
}

int CBaseEffect::Update()
{

	MoveFrame();
	return 0;

}

void CBaseEffect::LateUpdate()
{
}

void CBaseEffect::Render(HDC hDC)
{
	if (m_bMoveFrame == false)
		return;
	HDC hPlayer = CBmpMgr::GetInstance()->FindImage(m_pFrameKey);

	GdiTransparentBlt(hDC,					// 목적지 DC
		int(m_tInfo.fX - (m_tFrame.iCX / 2)),	// 목적지 LEFT, TOP
		int(m_tInfo.fY - (m_tFrame.iCY - m_tInfo.fCY * 0.5)),
		m_tFrame.iCX,			// 목적지 공간의 가로, 세로 사이즈
		m_tFrame.iCY,
		hPlayer,						// 원본 이미지 DC
		m_tFrame.iCX * m_tFrame.iStart,	// 원본 이미지 LEFT, TOP
		0,
		m_tFrame.iCX,			// 원본 이미지 가로, 세로 사이즈
		m_tFrame.iCY,
		RGB(255, 0, 255));		// 제거할 픽셀 색상
}

void CBaseEffect::Release()
{
}
