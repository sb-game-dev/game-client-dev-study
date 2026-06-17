#include "pch.h"
#include "CTile.h"
#include "CImgMgr.h"
#include "CBmpMgr.h"
#include "CObjMgr.h"
#include "CItem.h"
#include "CAbstractFactory.h"
CTile::CTile(): m_dwFrameCount(GetTickCount64()), m_pImg(nullptr), m_eDirection(DIR_END), m_eCurMotion(IDLE),m_ePreMotion(MOTION_END),
m_eTileID(TILE_END), m_iCurIndex(0),m_iDstIndex(0),m_bMove(false),m_fDstX(0.f),m_fDstY(0.f)
{

}

CTile::~CTile()
{
	Release();
}

void CTile::Initialize()
{
	m_eRenderID = GAMEOBJECT;

	m_tInfo.fCX = 40.f;
	m_tInfo.fCY = 40.f;
	m_pFrameKey = L"tile";
	m_fSpeed = 0;
	m_tFrame.iEnd = 20;
	m_tFrame.iMotion = 0;
	m_tFrame.bLoop = false;
	m_tFrame.iCX = TILECX;
	m_tFrame.iCY = TILECY;
	m_tFrame.dwSpeed = 123.f;
	m_tFrame.dwTime = GetTickCount64();
}

int CTile::Update()
{
	if (m_bDead == DEAD)
		return DEAD;

	if (m_eCurMotion == HIT)
	{
		MoveFrame();
		CheckFrame();
	}
	if (m_bMove == true)
	{
		Move();
	}
	return NOEVENT;
}

void CTile::LateUpdate()
{

}

void CTile::Render(HDC hDC)
{
	if (m_bDraw == false)
		return;

	if (m_tFrame.iStart <= 1)// || (m_tFrame.iStart >= 11 && m_tFrame.iStart <= 17))
		return;

	HDC hTile = CBmpMgr::GetInstance()->FindImage(m_pFrameKey);

	GdiTransparentBlt(hDC,			// 목적지 DC
		int(m_tInfo.fX - (m_tFrame.iCX / 2)),
		int(m_tInfo.fY - (m_tFrame.iCY - m_tInfo.fCY * 0.5)),
		m_tFrame.iCX,				// 목적지 공간의 가로, 세로 사이즈
		m_tFrame.iCY,
		hTile,						// 원본 이미지 DC
		m_tFrame.iCX * m_tFrame.iStart,							// 원본 이미지 LEFT, TOP
		0,
		m_tFrame.iCX,			// 원본 이미지 가로, 세로 사이즈
		m_tFrame.iCY,
		RGB(255, 0, 255));		// 제거할 픽셀 색상

	//int iX = (m_tInfo.fX - MAP_LEFT) / TILECX;
	//int iY = (m_tInfo.fY - MAP_TOP) / TILECX;
	////
	////int Index = iY * MAP_CNT_X + iX;
	//TCHAR	szBuff[32] = L"";
	//swprintf_s(szBuff, L"(%d,%d)", iX,iY);
	//TextOut(hDC, m_tInfo.fX - 20, m_tInfo.fY-10, szBuff, lstrlen(szBuff));
}

void CTile::Release()
{
}
void CTile::ChangeMotion()
{
	if (m_ePreMotion == m_eCurMotion)
		return;
	switch (m_eCurMotion)
	{
	case HIT:
		m_pFrameKey = L"tile_hit";
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 13;
		m_tFrame.iMotion = 0;
		m_tFrame.bLoop = false;
		m_tFrame.iCX = 44;
		m_tFrame.iCY = 48;
		m_tFrame.dwSpeed = 50.f;
		m_tFrame.dwTime = GetTickCount64();
		m_dwFrameCount = GetTickCount64();
		break;
	default:
		break;
	}
	m_ePreMotion = m_eCurMotion;
}
void CTile::Move()
{
	if (!lstrcmp(m_pFrameKey, L"tile_hit"))
	{
		m_bMove = false;
		return;
	}
	//for (auto& pTile : CObjMgr::GetInstance()->GetTile())
	//{
	//	if (pTile == this) continue;
	//
	//	if (pTile->GetFrame().iStart >= 1
	//		&&fabsf(m_fDstX - pTile->GetInfo()->fX) <= 20.f
	//		&& fabsf(m_fDstY - pTile->GetInfo()->fY) <= 20.f)
	//	{
	//		m_bMove = false;
	//		return;
	//	}
	//	//if (pTile->GetFrame().iStart >= 1
	//	//	&& m_fDstX == pTile->GetInfo()->fX
	//	//	&& m_fDstY == pTile->GetInfo()->fY)
	//	//{
	//	//	m_bMove = false;
	//	//	return;
	//	//}
	//}
	int x = (m_fDstX - MAP_LEFT) / TILECX;
	int y = (m_fDstY - MAP_TOP) / TILECX;
	int Index = y * MAP_CNT_X + x;

	if (CObjMgr::GetInstance()->GetTile()[Index]->GetFrame().iStart >= 1)
	{
		m_bMove = false;
		return;
	}

	if (m_tInfo.fX < m_fDstX) m_tInfo.fX += 2.0f;
	else if (m_tInfo.fX > m_fDstX) m_tInfo.fX -= 2.0f;
	else if (m_tInfo.fY < m_fDstY) m_tInfo.fY += 2.0f;
	else if (m_tInfo.fY > m_fDstY)m_tInfo.fY -= 2.0f;
	else
	{
		CObjMgr::GetInstance()->TileSwap(m_iCurIndex, m_iDstIndex);
		m_bMove = false;
	}
}
void CTile::SetMove(DIRECTION eDIR)
{
	m_bMove = true;
	m_eDirection = eDIR;
	m_fDstX = m_tInfo.fX;
	m_fDstY = m_tInfo.fY;

	switch (m_eDirection)
	{
	case DIR_LEFT:
		m_fDstX -= 40.f;
		break;
	case DIR_UP:
		m_fDstY -= 40.f;
		break;
	case DIR_RIGHT:
		m_fDstX += 40.f;
		break;
	case DIR_DOWN:
		m_fDstY += 40.f;
		break;
	}
	int iX = (m_tInfo.fX - MAP_LEFT) / TILECX;
	int iY = (m_tInfo.fY - MAP_TOP) / TILECX;
	
	m_iCurIndex = iY * MAP_CNT_X + iX;
	
	int iRightX = (m_fDstX - MAP_LEFT) / TILECX;
	int iRihgtY = (m_fDstY - MAP_TOP) / TILECX;
	
	m_iDstIndex = iRihgtY * MAP_CNT_X + iRightX;
}

void CTile::CheckFrame()
{
	if (m_dwFrameCount + m_tFrame.dwSpeed * m_tFrame.iEnd <= GetTickCount64())
	{
		m_eCurMotion = DEATH;
		m_pFrameKey = L"tile";
		m_fSpeed = 0;
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 1;
		m_tFrame.iMotion = 0;
		m_tFrame.bLoop = false;


		if(rand()%10 < 4)
			CreateItem();

		//m_tFrame.iCX = TILECX;
		//m_tFrame.iCY = TILECY;
		//m_tFrame.dwSpeed = 1.f;
		//m_tFrame.dwTime = GetTickCount64();
	}
}

void CTile::CreateItem()
{
	const WCHAR* pItemType[8] = { 
		L"bubble" ,L"roller",L"fluid" ,L"needle" ,
		L"dart" ,L"shield" ,L"shoe" ,L"trampoline"
	};
	
	CObjMgr::GetInstance()->AddObject(OBJ_ITEM ,CAbstractFactory<CItem>::Create(m_tInfo.fX, m_tInfo.fY, pItemType[rand() % 8]));
}
