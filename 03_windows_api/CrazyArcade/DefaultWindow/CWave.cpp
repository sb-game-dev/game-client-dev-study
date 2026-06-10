#include "pch.h"
#include "CWave.h"
#include "CBmpMgr.h"
#include "CAbstractFactory.h"
#include "CObjMgr.h"

CWave::CWave():m_dwFrameCount(GetTickCount64())
{
}

CWave::~CWave()
{
	Release();
}

void CWave::Initialize()
{
	m_tInfo.fCX = 35.f;
	m_tInfo.fCY = 35.f;
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Wave/WaveCenter.bmp", L"WaveCenter");

	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Wave/down.bmp", L"down");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Wave/left.bmp", L"left");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Wave/right.bmp", L"right");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Wave/up.bmp", L"up");

	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Wave/down_end.bmp", L"down_end");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Wave/left_end.bmp", L"left_end");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Wave/right_end.bmp", L"right_end");
	CBmpMgr::GetInstance()->InsertBmp(L"../Resource/Wave/up_end.bmp", L"up_end");

	m_fSpeed = 0;
	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 11;
	m_tFrame.iMotion = 0;
	m_tFrame.bLoop = false;
	m_tFrame.iCX = 40;
	m_tFrame.iCY = 40;
	m_tFrame.dwSpeed = 50.f;
	m_tFrame.dwTime = GetTickCount64();
}

int CWave::Update()
{
	if (m_bDead == DEAD)
		return DEAD;
	MoveFrame();
	CheckFrame();
	return 0;
}

void CWave::LateUpdate()
{
}

void CWave::Render(HDC hDC)
{
	

	HDC hTile = CBmpMgr::GetInstance()->FindImage(m_pFrameKey);
	GdiTransparentBlt(hDC,			// 목적지 DC
		int(m_tInfo.fX - (m_tFrame.iCX * 0.5)),
		int(m_tInfo.fY - (m_tFrame.iCY - m_tInfo.fCY * 0.5)),
		m_tFrame.iCX,				// 목적지 공간의 가로, 세로 사이즈
		m_tFrame.iCY,
		hTile,						// 원본 이미지 DC
		m_tFrame.iCX * m_tFrame.iStart,// 원본 이미지 LEFT, TOP
		0,
		m_tFrame.iCX,			// 원본 이미지 가로, 세로 사이즈
		m_tFrame.iCY,
		RGB(255, 0, 255));		// 제거할 픽셀 색상

	//if (!lstrcmp(m_pFrameKey, L"WaveCenter"))
	//{
	//	vector<CObj*> tempTileVec = CObjMgr::GetInstance()->GetTile();
	//	int x = (m_tInfo.fX - MAP_LEFT) / TILECX;
	//	int y = (m_tInfo.fY - MAP_TOP) / TILECX;
	//
	//	int Index = y * MAP_CNT_X + x;
	//
	//	int RightIndex = y * MAP_CNT_X + x + 1;
	//
	//	TCHAR	szBuff[32] = L"";
	//	swprintf_s(szBuff, L"TileID : %d", tempTileVec[RightIndex]->GetFrame().iStart);// dynamic_cast<CTile*>(tempTileVec[RightIndex])->GetTileID());
	//	TextOut(hDC, 50, 150, szBuff, lstrlen(szBuff));
	//}

	//if (!lstrcmp(m_pFrameKey, L"right"))
	//{
	//	TCHAR	szBuff[32] = L"";
	//	swprintf_s(szBuff, L"X : %.0f", m_tInfo.fX);
	//	TextOut(hDC, 50, 150, szBuff, lstrlen(szBuff));
	//	TCHAR	szBuff2[32] = L"";
	//	swprintf_s(szBuff2, L"Y : %.0f", m_tInfo.fY);
	//	TextOut(hDC, 50, 175, szBuff2, lstrlen(szBuff2));
	//}
}

void CWave::Release()
{
}

void CWave::CheckFrame()
{
	if (m_dwFrameCount + m_tFrame.dwSpeed * m_tFrame.iEnd <= GetTickCount64())
	{
		m_bDead = DEAD;
	}
}

void CWave::Spread(int iBombRange)
{
	vector<CObj*> tempTileVec = CObjMgr::GetInstance()->GetTile();
	int x = (m_tInfo.fX - MAP_LEFT) / TILECX;
	int y = (m_tInfo.fY - MAP_TOP) / TILECX;
	for (int i = 1; i <= iBombRange; ++i)
	{
		int RightIndex = y * MAP_CNT_X + x + i;
		if (RightIndex/ MAP_CNT_X != (RightIndex-1) / MAP_CNT_X)
			break;
		if (tempTileVec[RightIndex]->GetFrame().iStart <= 1)
		{
			if (i == iBombRange)
				CObjMgr::GetInstance()->AddObject(OBJ_WAVE, CAbstractFactory<CWave>::Create(m_tInfo.fX + m_tInfo.fCX * i, m_tInfo.fY, L"right_end"));

			else
				CObjMgr::GetInstance()->AddObject(OBJ_WAVE, CAbstractFactory<CWave>::Create(m_tInfo.fX + m_tInfo.fCX * i, m_tInfo.fY, L"right"));
		}
		else if (tempTileVec[RightIndex]->GetFrame().iStart <= 3)
		{
			if (i == iBombRange)
				CObjMgr::GetInstance()->AddObject(OBJ_WAVE, CAbstractFactory<CWave>::Create(m_tInfo.fX + m_tInfo.fCX * i, m_tInfo.fY, L"right_end"));

			else
				CObjMgr::GetInstance()->AddObject(OBJ_WAVE, CAbstractFactory<CWave>::Create(m_tInfo.fX + m_tInfo.fCX * i, m_tInfo.fY, L"right"));
			break;
		}
		else
			break;
	}
	for (int i = 1; i <= iBombRange; ++i)
	{
		int LeftIndex = y * MAP_CNT_X + x - i;
		if (LeftIndex<0 ||LeftIndex / MAP_CNT_X != (LeftIndex + 1) / MAP_CNT_X)
			break;
		if (tempTileVec[LeftIndex]->GetFrame().iStart <= 1)
		{
			if (i == iBombRange)
				CObjMgr::GetInstance()->AddObject(OBJ_WAVE, CAbstractFactory<CWave>::Create(m_tInfo.fX - m_tInfo.fCX * i, m_tInfo.fY , L"left_end"));

			else
				CObjMgr::GetInstance()->AddObject(OBJ_WAVE, CAbstractFactory<CWave>::Create(m_tInfo.fX - m_tInfo.fCX * i, m_tInfo.fY , L"left"));
		}
		else if (tempTileVec[LeftIndex]->GetFrame().iStart <= 3)
		{
			if (i == iBombRange)
				CObjMgr::GetInstance()->AddObject(OBJ_WAVE, CAbstractFactory<CWave>::Create(m_tInfo.fX - m_tInfo.fCX * i, m_tInfo.fY , L"left_end"));

			else
				CObjMgr::GetInstance()->AddObject(OBJ_WAVE, CAbstractFactory<CWave>::Create(m_tInfo.fX - m_tInfo.fCX * i, m_tInfo.fY , L"left"));
			break;
		}
		else
			break;
	}
	for (int i = 1; i <= iBombRange; ++i)
	{
		int TopIndex = (y - i) * MAP_CNT_X + x;
		if (TopIndex < 0)
			break;
		if (tempTileVec[TopIndex]->GetFrame().iStart <= 1)
		{
			if (i == iBombRange)
				CObjMgr::GetInstance()->AddObject(OBJ_WAVE, CAbstractFactory<CWave>::Create(m_tInfo.fX, m_tInfo.fY - m_tInfo.fCY * i, L"up_end"));

			else
				CObjMgr::GetInstance()->AddObject(OBJ_WAVE, CAbstractFactory<CWave>::Create(m_tInfo.fX, m_tInfo.fY - m_tInfo.fCY * i, L"up"));
		}
		else if (tempTileVec[TopIndex]->GetFrame().iStart <= 3)
		{
			if (i == iBombRange)
				CObjMgr::GetInstance()->AddObject(OBJ_WAVE, CAbstractFactory<CWave>::Create(m_tInfo.fX, m_tInfo.fY - m_tInfo.fCY * i, L"up_end"));

			else
				CObjMgr::GetInstance()->AddObject(OBJ_WAVE, CAbstractFactory<CWave>::Create(m_tInfo.fX, m_tInfo.fY - m_tInfo.fCY * i, L"up"));
			break;
		}
		else
			break;
	}
	for (int i = 1; i <= iBombRange; ++i)
	{
		int BottomIndex = (y + i) * MAP_CNT_X + x;
		if (BottomIndex > 194)
			return;
		if (tempTileVec[BottomIndex]->GetFrame().iStart <= 1)
		{
			if (i == iBombRange)
				CObjMgr::GetInstance()->AddObject(OBJ_WAVE, CAbstractFactory<CWave>::Create(m_tInfo.fX, m_tInfo.fY + m_tInfo.fCY * i, L"down_end"));

			else
				CObjMgr::GetInstance()->AddObject(OBJ_WAVE, CAbstractFactory<CWave>::Create(m_tInfo.fX, m_tInfo.fY + m_tInfo.fCY * i, L"down"));
		}																										   
		else if (tempTileVec[BottomIndex]->GetFrame().iStart <= 3)													   
		{																										   
			if (i == iBombRange)																				   
				CObjMgr::GetInstance()->AddObject(OBJ_WAVE, CAbstractFactory<CWave>::Create(m_tInfo.fX, m_tInfo.fY + m_tInfo.fCY * i, L"down_end"));
																												   
			else																								   
				CObjMgr::GetInstance()->AddObject(OBJ_WAVE, CAbstractFactory<CWave>::Create(m_tInfo.fX, m_tInfo.fY + m_tInfo.fCY * i, L"down"));
			break;
		}
		else
			break;
	}
	//
	////right
	//bool bRunning = true;
	//for (int i = 1; i <= iBombRange; ++i)
	//{
	//	if (bRunning == false) break;
	//	CObj* pWater = nullptr;
	//	if (i == iBombRange)
	//		pWater = CAbstractFactory<CWave>::Create(m_tInfo.fX + m_tInfo.fCX * i, m_tInfo.fY, L"right_end");
	//	else
	//		pWater = CAbstractFactory<CWave>::Create(m_tInfo.fX + m_tInfo.fCX * i, m_tInfo.fY, L"right");
	//
	//	
	//	if (i + 1 > iBombRange) break;
	//	for (auto& pBlock : CObjMgr::GetInstance()->GetTile())
	//	{
	//		if (fabsf(pWater->GetInfo()->fX - pBlock->GetInfo()->fX) <= 10.f &&
	//			fabsf(pWater->GetInfo()->fY - pBlock->GetInfo()->fY) <= 10.f)
	//		{
	//			bRunning = false;
	//			break;
	//		}
	//		CObjMgr::GetInstance()->AddObject(OBJ_WAVE, pWater);
	//	}
	//}
	////left
	//bRunning = true;
	//for (int i = 1; i <= iBombRange; ++i)
	//{
	//	if (bRunning == false) break;
	//
	//	CObj* pWater = nullptr;
	//	if (i == iBombRange)
	//		pWater = CAbstractFactory<CWave>::Create(m_tInfo.fX - m_tInfo.fCX * i, m_tInfo.fY, L"left_end");
	//	else
	//		pWater = CAbstractFactory<CWave>::Create(m_tInfo.fX - m_tInfo.fCX * i, m_tInfo.fY, L"left");
	//
	//	CObjMgr::GetInstance()->AddObject(OBJ_WAVE, pWater);
	//	if (i + 1 > iBombRange) break;
	//	for (auto& pBlock : CObjMgr::GetInstance()->GetTile())
	//	{
	//		if (fabsf(pWater->GetInfo()->fX - pBlock->GetInfo()->fX) <= 10.f &&
	//			fabsf(pWater->GetInfo()->fY - pBlock->GetInfo()->fY) <= 10.f)
	//		{
	//			bRunning = false;
	//			break;
	//		}
	//	}
	//}
	////top
	//bRunning = true;
	//for (int i = 1; i <= iBombRange; ++i)
	//{
	//	if (bRunning == false) break;
	//	CObj* pWater = nullptr;
	//	if (i == iBombRange)
	//		pWater = CAbstractFactory<CWave>::Create(m_tInfo.fX, m_tInfo.fY - m_tInfo.fCY * i, L"up_end");
	//	else
	//		pWater = CAbstractFactory<CWave>::Create(m_tInfo.fX, m_tInfo.fY - m_tInfo.fCY * i, L"up");
	//
	//	CObjMgr::GetInstance()->AddObject(OBJ_WAVE, pWater);
	//	if (i + 1 > iBombRange) break;
	//	for (auto& pBlock : CObjMgr::GetInstance()->GetTile())
	//	{
	//		if (fabsf(pWater->GetInfo()->fX - pBlock->GetInfo()->fX) <= 10.f &&
	//			fabsf(pWater->GetInfo()->fY - pBlock->GetInfo()->fY) <= 10.f)
	//		{
	//			bRunning = false;
	//			break;
	//		}
	//	}
	//}
	////bottom
	//bRunning = true;
	//for (int i = 1; i <= iBombRange; ++i)
	//{
	//	if (bRunning == false) break;
	//	CObj* pWater = nullptr;
	//	if (i == iBombRange)
	//		pWater = CAbstractFactory<CWave>::Create(m_tInfo.fX, m_tInfo.fY + m_tInfo.fCY * i, L"down_end");
	//	else
	//		pWater = CAbstractFactory<CWave>::Create(m_tInfo.fX, m_tInfo.fY + m_tInfo.fCY * i, L"down");
	//	CObjMgr::GetInstance()->AddObject(OBJ_WAVE, pWater);
	//	if (i + 1 > iBombRange) break;
	//	for (auto& pBlock : CObjMgr::GetInstance()->GetTile())
	//	{
	//		if (fabsf(pWater->GetInfo()->fX - pBlock->GetInfo()->fX) <= 10.f &&
	//			fabsf(pWater->GetInfo()->fY - pBlock->GetInfo()->fY) <= 10.f)
	//		{
	//			bRunning = false;
	//			break;
	//		}
	//	}
	//}
}
