#include "pch.h"
#include "CMouse.h"
#include "CImgMgr.h"
#include "CBmpMgr.h"

CMouse::CMouse():m_eChoiceTile(TILE_END), m_iChoiceItem(-1)
{
}

CMouse::~CMouse()
{
	Release();
}

void CMouse::Initialize()
{
	m_eRenderID = MOUSE;

	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Mouse/mouse.bmp", L"mouse");
	CImgMgr::GetInstance()->InsertImg(L"../Resource/Tile/tile2.png", L"tile");

	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/UI/MouseItem.bmp", L"MouseItem");
	

	m_pFrameKey = L"mouse";
	m_tInfo.fCX = 37.f;
	m_tInfo.fCY = 39.f;
	ShowCursor(FALSE);
}

int CMouse::Update()
{
	POINT		ptMouse{};
	GetCursorPos(&ptMouse);				// 스크린 좌표의 마우스 값을 얻어옴
	ScreenToClient(g_hWnd, &ptMouse);	// 스크린 좌표를 창 좌표로 변환

	m_tInfo.fX = (float)ptMouse.x;
	m_tInfo.fY = (float)ptMouse.y;

#ifdef _DEBUG
	//cout << "Mouse X: " << m_tInfo.fX << "\tMouse Y: " << m_tInfo.fY << endl;
#endif // _DEBUG


	return NOEVENT;
}

void CMouse::LateUpdate()
{
}

void CMouse::Render(HDC hDC)
{
	if (m_tInfo.fX < MAP_RIGHT
		&& m_tInfo.fX > MAP_LEFT
		&& m_tInfo.fY < MAP_BOTTOM
		&& m_tInfo.fY > MAP_TOP
		&& m_eChoiceTile != TILE_END)
	{
		Graphics* _pGraphics = Graphics::FromHDC(hDC);
		Gdiplus::Image* pImg = CImgMgr::GetInstance()->FindImg(L"tile");
		Rect rect = { AdjustPosX(m_tInfo.fX) - 20,
					AdjustPosY(m_tInfo.fY) - 47,
					40,67 };
		ImageAttributes attr;
		MakeAlphaAttr(attr, 0.5f);
		_pGraphics->DrawImage(pImg, rect,
			m_eChoiceTile* 40, 0,
			40, 67,
			UnitPixel,
			&attr);
	}
	if (m_iChoiceItem >= 0)
	{
		HDC hItem = CBmpMgr::GetInstance()->FindImage(L"MouseItem");
		GdiTransparentBlt(hDC,					// 목적지 DC
			m_tInfo.fX - 30,	// 목적지 LEFT, TOP
			m_tInfo.fY - 25,
			60,			// 목적지 공간의 가로, 세로 사이즈
			50,
			hItem,						// 원본 이미지 DC
			m_iChoiceItem * 60,							// 원본 이미지 LEFT, TOP
			0,
			60,			// 원본 이미지 가로, 세로 사이즈
			50,
			RGB(255, 0, 255));		// 제거할 픽셀 색상
	}
	//cout << m_iChoiceItem << endl;
	HDC hMouse = CBmpMgr::GetInstance()->FindImage(L"mouse");
	GdiTransparentBlt(hDC,					// 목적지 DC
		m_tInfo.fX,	// 목적지 LEFT, TOP
		m_tInfo.fY,
		(int)m_tInfo.fCX,			// 목적지 공간의 가로, 세로 사이즈
		(int)m_tInfo.fCY,
		hMouse,						// 원본 이미지 DC
		0,							// 원본 이미지 LEFT, TOP
		0,
		(int)m_tInfo.fCX,			// 원본 이미지 가로, 세로 사이즈
		(int)m_tInfo.fCY,
		RGB(255, 0, 255));		// 제거할 픽셀 색상


	//Gdiplus::Image* pImg = CImgMgr::GetInstance()->FindImg(m_pFrameKey);
	//
	//Rect rect = { (int)m_tInfo.fX,(int)m_tInfo.fY,(int)m_tInfo.fCX,(int)m_tInfo.fCY };
	//
	//_pGraphics->DrawImage(pImg, rect,
	//	0,0,
	//	m_tInfo.fCX, m_tInfo.fCY,
	//	UnitPixel);
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
	case 11:
		m_eChoiceTile = STAGE2TILE1;
		break;
	case 12:
		m_eChoiceTile = STAGE2TILE2;
		break;
	case 13:
		m_eChoiceTile = STAGE2TILE3;
		break;
	case 14:
		m_eChoiceTile = STAGE2TILE4;
		break;
	case 15:
		m_eChoiceTile = STAGE2TILE5;
		break;
	case 16:
		m_eChoiceTile = STAGE2TILE6;
		break;
	case 17:
		m_eChoiceTile = STAGE2TILE7;
		break;
	case 18:
		m_eChoiceTile = STAGE2TILE8;
		break;
	case 19:
		m_eChoiceTile = STAGE2TILE9;
		break;
	case 20:
		m_eChoiceTile = STAGE3TILE1;
		break;
	case 21:
		m_eChoiceTile = STAGE3TILE2;
		break;
	case 22:
		m_eChoiceTile = STAGE3TILE3;
		break;
	case 23:
		m_eChoiceTile = STAGE3TILE4;
		break;
	case 24:
		m_eChoiceTile = STAGE3TILE5;
		break;
	case 25:
		m_eChoiceTile = STAGE3TILE6;
		break;
	case 26:
		m_eChoiceTile = STAGE3TILE7;
		break;
	case 27:
		m_eChoiceTile = STAGE3TILE8;
		break;
	case 28:
		m_eChoiceTile = STAGE3TILE9;
		break;
	case 29:
		m_eChoiceTile = STAGE3TILE10;
		break;
	case 30:
		m_eChoiceTile = STAGE3TILE11;
		break;
	case 31:
		m_eChoiceTile = STAGE3TILE12;
		break;
	case 32:
		m_eChoiceTile = STAGE3TILE13;
		break;
	case 33:
		m_eChoiceTile = STAGE3TILE14;
		break;
	case 34:
		m_eChoiceTile = STAGE3TILE15;
		break;
	case 35:
		m_eChoiceTile = TILE_END;
		break;
	default:
		break;
	}
}
