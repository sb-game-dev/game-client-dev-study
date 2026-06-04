#include "pch.h"
#include "CTile.h"
#include "CBmpMgr.h"
#include "CKeyMgr.h"

CTile::CTile():m_eDrawID(TILE_NORMAL),m_iOption(0)
{
}

CTile::~CTile()
{
	Release();
}

void CTile::NextDrawID()
{
	switch (m_eDrawID)
	{
	case TILE_NORMAL:
		m_eDrawID = TILE_MOUSE;
		break;
	case TILE_MOUSE:
		m_eDrawID = TILE_PUSH;
		break;
	case TILE_PUSH:
		m_eDrawID = TILE_BREAK;
		break;
	case TILE_BREAK:
		m_eDrawID = TILE_WALL;
		break;
	case TILE_WALL:
		m_eDrawID = TILE_NORMAL;
		break;
	case TILE_END:
		break;
	default:
		break;
	}
}

void CTile::SetFrameKey()
{
	switch (m_eDrawID)
	{
	case TILE_NORMAL:
		m_pFrameKey = nullptr;
		break;
	case TILE_MOUSE:
		m_pFrameKey = nullptr;
		break;
	case TILE_PUSH:
		m_pFrameKey = L"Push";
		break;
	case TILE_BREAK:
		m_pFrameKey = L"Break";
		break;
	case TILE_WALL:
		m_pFrameKey = L"Wall";
		break;
	case TILE_END:
		break;
	default:
		break;
	}
}

void CTile::Initialize()
{
	m_tInfo.fCX = TILECX;
	m_tInfo.fCY = TILECY;
}

int CTile::Update()
{
	return 0;
}

void CTile::LateUpdate()
{
	POINT		ptMouse;
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);

	if(m_eDrawID == TILE_MOUSE || m_eDrawID == TILE_NORMAL)
	{
		if (PtInRect(&m_tRect, ptMouse))
		{
			m_eDrawID = TILE_MOUSE;
		}
		else
		{
			m_eDrawID = TILE_NORMAL;
		}
	}
	
	Update_Rect();
}

void CTile::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::GetInstance()->FindImage(m_pFrameKey);

	GdiTransparentBlt(hDC,		// 목적지 DC
		m_tRect.left,			// 목적지 LEFT,RIGHT
		m_tRect.top - 7,
		(int)40.f,				// 원본 DC에서 가져올 영역의 크기
		(int)40.f + 7,
		hMemDC,							// 원본 DC
		m_eDrawID * TILECX,		// 원본 이미지에서 가져오기 시작할 좌표의 LEFT, TOP
		0,
		(int)40.f,				// 원본 DC에서 가져올 영역의 크기
		(int)40.f + 7,
		RGB(255, 0, 255));		// 제거할 픽셀 색상
}

void CTile::Release()
{

}
