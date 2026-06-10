#include "pch.h"
#include "CMouse.h"
#include "CImgMgr.h"

CMouse::CMouse():m_eChoiceTile(TILE_END)
{
}

CMouse::~CMouse()
{
	Release();
}

void CMouse::Initialize()
{
	//CImgMgr::GetInstance()->InsertImg(L"../Resource/Mouse/mouse.png", L"mouse");
	CImgMgr::GetInstance()->InsertImg(L"../Resource/Tile/tile.png", L"tile");

	m_pFrameKey = L"mouse";
	m_tInfo.fCX = 27.f;
	m_tInfo.fCY = 30.f;
}

int CMouse::Update()
{
	POINT		ptMouse{};

	GetCursorPos(&ptMouse);	// ½ºÅ©¸° ÁÂÇ¥ÀÇ ¸¶¿ì½º °ªÀ» ¾ò¾î¿È

	ScreenToClient(g_hWnd, &ptMouse); // ½ºÅ©¸° ÁÂÇ¥¸¦ Ã¢ ÁÂÇ¥·Î º¯È¯


	m_tInfo.fX = (float)ptMouse.x;
	m_tInfo.fY = (float)ptMouse.y;

	//ShowCursor(FALSE);

	return NOEVENT;
}

void CMouse::LateUpdate()
{
}

void CMouse::Render(HDC hDC)
{
	Graphics* _pGraphics = Graphics::FromHDC(hDC);

	if (m_tInfo.fX < MAP_RIGHT
		&& m_tInfo.fX > MAP_LEFT
		&& m_tInfo.fY < MAP_BOTTOM
		&& m_tInfo.fY > MAP_TOP
		&& m_eChoiceTile != TILE_END)
	{
		Gdiplus::Image* pImg = CImgMgr::GetInstance()->FindImg(L"tile");
		Rect rect = { AdjustPosX(m_tInfo.fX) - 20,
					AdjustPosY(m_tInfo.fY) - 36,
					40,56 };
		ImageAttributes attr;
		MakeAlphaAttr(attr, 0.5f);
		_pGraphics->DrawImage(pImg, rect,
			m_eChoiceTile* 40, 0,
			40, 56,
			UnitPixel,
			&attr);
	}

	Gdiplus::Image* pImg = CImgMgr::GetInstance()->FindImg(m_pFrameKey);
	
	Rect rect = { (int)m_tInfo.fX,(int)m_tInfo.fY,(int)m_tInfo.fCX,(int)m_tInfo.fCY };
	
	_pGraphics->DrawImage(pImg, rect,
		0,0,
		m_tInfo.fCX, m_tInfo.fCY,
		UnitPixel);
}

void CMouse::Release()
{

}

void CMouse::SetChoiceTile(int eID)
{
	switch (eID)
	{
	case 0:
		m_eChoiceTile = TILE1;
		break;
	case 1:
		m_eChoiceTile = TILE2;
		break;
	case 2:
		m_eChoiceTile = PUSH;
		break;
	case 3:
		m_eChoiceTile = BREAK;
		break;
	case 4:
		m_eChoiceTile = WALL1;
		break;
	case 5:
		m_eChoiceTile = WALL2;
		break;
	case 6:
		m_eChoiceTile = WALL3;
		break;
	case 7:
		m_eChoiceTile = WALL4;
		break;
	case 8:
		m_eChoiceTile = WALL5;
		break;
	case 9:
		m_eChoiceTile = WALL6;
		break;
	case 10:
		m_eChoiceTile = WALL7;
		break;
	default:
		break;
	}
}
