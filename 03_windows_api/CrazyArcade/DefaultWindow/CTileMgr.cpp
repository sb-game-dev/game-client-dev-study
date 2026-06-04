#include "pch.h"
#include "CTileMgr.h"
#include "CBmpMgr.h"
#include "CTile.h"
#include "CAbstractFactory.h"
#include "CKeyMgr.h"
CTileMgr* CTileMgr::m_pInstance = nullptr;

CTileMgr::CTileMgr()
{
}

CTileMgr::~CTileMgr()
{
	Release();
}


void CTileMgr::Initialize()
{
	CBmpMgr::GetInstance()->InsertBmp(L"../Image/크레이지 아케이드 리소스/Resource/Block/Tile_base.bmp", L"Tile_base");
	CBmpMgr::GetInstance()->InsertBmp(L"../Image/크레이지 아케이드 리소스/Resource/Block/block_v2.bmp", L"Push");
	CBmpMgr::GetInstance()->InsertBmp(L"../Image/크레이지 아케이드 리소스/Resource/Block/block_v1.bmp", L"Break");
	CBmpMgr::GetInstance()->InsertBmp(L"../Image/크레이지 아케이드 리소스/Resource/Block/Wall_f1.bmp", L"Wall");

	for (int i = 0; i < TILE_CNT_Y;++i)
	{
		for (int j = 0; j < TILE_CNT_X; ++j)
		{
			float fX = (float)(TILE_START_X + TILECX * 0.5) + (TILECX * j);
			float fY = (float)(TILE_START_Y + TILECY * 0.5) + (TILECY * i);

			m_vecTile.push_back(CAbstractFactory<CTile>::Create(fX, fY, L"Tile_base"));
		}
	}
}

int CTileMgr::Update()
{
	for (auto iter = m_vecTile.begin();iter!=m_vecTile.end(); )
	{
		int iResult = (*iter)->Update();
		if (iResult == DEAD)
		{
			Safe_Delete((*iter));
			iter = m_vecTile.erase(iter);
		}
		else
		{
			++iter;
		}
	}
	return NONEVENT;
}

void CTileMgr::LateUpdate()
{
	for (auto& pTile : m_vecTile)
		pTile->LateUpdate();
}

void CTileMgr::Render(HDC hDC)
{
	for (auto& pTile : m_vecTile)
		pTile->Render(hDC);
}

void CTileMgr::Release()
{
	for_each(m_vecTile.begin(), m_vecTile.end(), tagDelete());
	m_vecTile.clear();
}

void CTileMgr::PickingTile(POINT pt)
{
	int x = (pt.x - TILE_START_X) / TILECX;
	int y = (pt.y - TILE_START_Y) / TILECY;

	int iIndex = y * TILE_CNT_X + x;

	if (0 > iIndex || m_vecTile.size() <= (size_t)iIndex)
		return;

	dynamic_cast<CTile*>(m_vecTile[iIndex])->NextDrawID();
}

void CTileMgr::SaveTile()
{
	HANDLE	hFile = CreateFile(L"../Data/Tile.dat",		// 파일의 경로
		GENERIC_WRITE,			// 파일 접근 모드 / GENERIC_READ(읽기 전용)
		NULL,					// 공유 방식
		NULL,					// 보안 모드 설정
		CREATE_ALWAYS,			// 쓰기 전용일 때 파일이 없는 경우 파일 생성하여 저장, // OPEN_EXISTING : 파일이 있을 경우에만 불러오기
		FILE_ATTRIBUTE_NORMAL,	// 파일 속성(아무런 속성이 없는 일반 파일)
		NULL);					// 생성될 파일의 속성을 제공할 템플릿 파일(안쓰기 때문에 NULL)

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Save File"), L"Fail", MB_OKCANCEL);
		return;
	}
	TILEID			iDrawID(TILE_NORMAL);
	DWORD		dwByte(0);		// eof 역할하는 변수

	for (auto& pTile : m_vecTile)
	{
		iDrawID = dynamic_cast<CTile*>(pTile)->GetDrawID();
		WriteFile(hFile, pTile->GetInfo(), sizeof(INFO), &dwByte, nullptr);
		WriteFile(hFile, &iDrawID, sizeof(TILEID), &dwByte, nullptr);
	}

	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Save 완료"), L"Success", MB_OKCANCEL);
}

void CTileMgr::LoadTile()
{
	HANDLE	hFile = CreateFile(L"../Data/Tile.dat",		// 파일의 경로
		GENERIC_READ,			// 파일 접근 모드 / GENERIC_READ(읽기 전용)
		NULL,					// 공유 방식
		NULL,					// 보안 모드 설정
		OPEN_EXISTING,			// 쓰기 전용일 때 파일이 없는 경우 파일 생성하여 저장, // OPEN_EXISTING : 파일이 있을 경우에만 불러오기
		FILE_ATTRIBUTE_NORMAL,	// 파일 속성(아무런 속성이 없는 일반 파일)
		NULL);					// 생성될 파일의 속성을 제공할 템플릿 파일(안쓰기 때문에 NULL)

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Load File"), L"Fail", MB_OKCANCEL);
		return;
	}

	Release();

	TILEID		iDrawID(TILE_NORMAL);
	INFO		tTile{};
	DWORD		dwByte(0);		// eof 역할하는 변수

	while (true)
	{
		ReadFile(hFile, &tTile, sizeof(INFO), &dwByte, nullptr);
		ReadFile(hFile, &iDrawID, sizeof(TILEID), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		CObj* pTile = CAbstractFactory<CTile>::Create(tTile.fX, tTile.fY);
		dynamic_cast<CTile*>(pTile)->SetDrawID(iDrawID);
		pTile->SetFrameKey(L"Tile_base");
		m_vecTile.push_back(pTile);
	}

	CloseHandle(hFile);
	if(m_vecTile.size()>0)
		MessageBox(g_hWnd, _T("Load 완료"), L"Success", MB_OKCANCEL);
}

void CTileMgr::LoadStage()
{
	HANDLE	hFile = CreateFile(L"../Data/Tile.dat",		// 파일의 경로
		GENERIC_READ,			// 파일 접근 모드 / GENERIC_READ(읽기 전용)
		NULL,					// 공유 방식
		NULL,					// 보안 모드 설정
		OPEN_EXISTING,			// 쓰기 전용일 때 파일이 없는 경우 파일 생성하여 저장, // OPEN_EXISTING : 파일이 있을 경우에만 불러오기
		FILE_ATTRIBUTE_NORMAL,	// 파일 속성(아무런 속성이 없는 일반 파일)
		NULL);					// 생성될 파일의 속성을 제공할 템플릿 파일(안쓰기 때문에 NULL)

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Load File"), L"Fail", MB_OKCANCEL);
		return;
	}

	Release();

	TILEID		iDrawID(TILE_NORMAL);
	INFO		tTile{};
	DWORD		dwByte(0);		// eof 역할하는 변수
	CBmpMgr::GetInstance()->InsertBmp(L"../Image/크레이지 아케이드 리소스/Resource/Block/Tile_base.bmp", L"Tile_base");
	while (true)
	{
		ReadFile(hFile, &tTile, sizeof(INFO), &dwByte, nullptr);
		ReadFile(hFile, &iDrawID, sizeof(TILEID), &dwByte, nullptr);

		if (0 == dwByte)
			break;
		if (iDrawID == TILE_NORMAL || iDrawID == TILE_MOUSE)
			continue;
		CObj* pTile = CAbstractFactory<CTile>::Create(tTile.fX, tTile.fY);
		dynamic_cast<CTile*>(pTile)->SetDrawID(iDrawID);
		pTile->SetFrameKey(L"Tile_base");
		m_vecTile.push_back(pTile);
	}

	CloseHandle(hFile);
	if (m_vecTile.size() > 0)
		MessageBox(g_hWnd, _T("Load 완료"), L"Success", MB_OKCANCEL);
}
