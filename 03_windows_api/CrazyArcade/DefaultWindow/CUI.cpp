#include "pch.h"
#include "CUI.h"
#include "CBmpMgr.h"

CUI::CUI()
{
}

CUI::~CUI()
{
}

void CUI::Initialize()
{
	m_eRenderID = UI;
	if (!lstrcmp(L"UI_Respawn", m_pFrameKey))
	{
		m_tInfo.fCX = 56;
		m_tInfo.fCY = 79;

		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 4;
		m_tFrame.iMotion = 0;
		m_tFrame.bLoop = true;
		m_tFrame.iCX = m_tInfo.fCX;
		m_tFrame.iCY = m_tInfo.fCY;
		m_tFrame.dwSpeed = 80.f;
		m_tFrame.dwTime = GetTickCount64();
	}
}

int CUI::Update()
{
	if (m_bDraw == true)
		MoveFrame();
	return 0;
}

void CUI::LateUpdate()
{
}

void CUI::Render(HDC hDC)
{
	if (m_bDraw == false)
		return;
	cout << "UIRender" << endl;
	HDC hUI = CBmpMgr::GetInstance()->FindImage(m_pFrameKey);
	GdiTransparentBlt(hDC,					// 목적지 DC
		m_tRect.left,		// 목적지 LEFT,RIGHT
		m_tRect.top,
		(int)m_tFrame.iCX,				// 원본 DC에서 가져올 영역의 크기
		(int)m_tFrame.iCY,
		hUI,						// 원본 이미지 DC
		m_tFrame.iCX * m_tFrame.iStart,	// 원본 이미지 LEFT, TOP
		0,
		m_tFrame.iCX,			// 원본 이미지 가로, 세로 사이즈
		m_tFrame.iCY,
		RGB(255, 0, 255));		// 제거할 픽셀 색상
}

void CUI::Release()
{
}
