#include "pch.h"
#include "CObjMgr.h"
#include "CKeyMgr.h"
#include "CMouse.h"
#include "CTile.h"
#include "CAbstractFactory.h"
#include "CCollisionMgr.h"
#include "CBomb.h"
CObjMgr* CObjMgr::m_pInstance = nullptr;
CObjMgr::CObjMgr()
{
}

CObjMgr::~CObjMgr()
{
	Release();
}

void CObjMgr::AddObject(OBJID eID, CObj* pObj)
{
	if (eID >= OBJ_END || pObj == nullptr)
		return;
	m_ObjList[eID].push_back(pObj);
}

void CObjMgr::AddTile(CObj* pObj)
{
	if (pObj == nullptr)
		return;
	m_TileVec.push_back(pObj);
}

void CObjMgr::Initialize() 
{
	for (int i=0;i<OBJ_END;++i)
	{
		for (auto& pObj : m_ObjList[i])
			pObj->Initialize();
	}
}

int  CObjMgr::Update() 
{
	for (auto iter = m_TileVec.begin(); iter != m_TileVec.end();)
	{
		int iResult = (*iter)->Update();
		if (iResult == DEAD)
		{
			Safe_Delete((*iter));
			iter = m_TileVec.erase(iter);
		}
		else
		{
			++iter;
		}
	}

	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto iter = m_ObjList[i].begin();iter != m_ObjList[i].end();)
		{
			int iResult = (*iter)->Update();
			if (iResult == DEAD)
			{
				Safe_Delete((*iter));
				iter = m_ObjList[i].erase(iter);
			}
			else
			{
				++iter;
			}
		}
	}

	
	return 0;
}
void CObjMgr::LateUpdate() 
{
	for (auto& pObj : m_TileVec)
		pObj->Update_Rect();
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& pObj : m_ObjList[i])
		{
			pObj->LateUpdate();
		}
	}

	if(!m_ObjList[OBJ_BUTTON].empty())
		ChoiceButton();

	if (dynamic_cast<CMouse*>(m_ObjList[OBJ_MOUSE].front())->GetChoiceTile() != TILE_END)
		PutTile();

	CCollisionMgr::CollisionBody(m_TileVec, m_ObjList[OBJ_PLAYER]);
	CCollisionMgr::CollisionBody(m_ObjList[OBJ_BOMB], m_TileVec);
	CCollisionMgr::CollisionBody(m_ObjList[OBJ_BOMB], m_ObjList[OBJ_PLAYER]);
	
	CCollisionMgr::CollisionAttack(m_TileVec, m_ObjList[OBJ_WAVE]);
	CCollisionMgr::CollisionAttack(m_ObjList[OBJ_BOMB], m_ObjList[OBJ_WAVE]);
	CCollisionMgr::CollisionAttack(m_ObjList[OBJ_BOSS], m_ObjList[OBJ_WAVE]);

	CCollisionMgr::CollisionAttack(m_ObjList[OBJ_BOMB], m_ObjList[OBJ_DART]);
	CCollisionMgr::CollisionAttack(m_ObjList[OBJ_MONSTER_BOMB], m_ObjList[OBJ_DART]);
	CCollisionMgr::CollisionAttack(m_TileVec, m_ObjList[OBJ_DART]);

	CCollisionMgr::CollisionAttack(m_ObjList[OBJ_ITEM], m_ObjList[OBJ_PLAYER]);
	CCollisionMgr::CollisionAttack(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_BOSS]);
	CCollisionMgr::CollisionAttack(m_ObjList[OBJ_ITEM], m_ObjList[OBJ_WAVE]);

	if (GetRemainTile() == 0)
	{
		CCollisionMgr::CollisionBody(m_ObjList[OBJ_MONSTER_BOMB], m_ObjList[OBJ_PLAYER]);
		CCollisionMgr::CollisionBody(m_ObjList[OBJ_MONSTER_BOMB], m_ObjList[OBJ_MONSTER_BOMB]);
		CCollisionMgr::CollisionBody(m_ObjList[OBJ_BOMB], m_ObjList[OBJ_MONSTER_BOMB]);
		CCollisionMgr::CollisionAttack(m_ObjList[OBJ_MONSTER_BOMB], m_ObjList[OBJ_WAVE]);
	}

#ifdef NDEBUG

	CCollisionMgr::CollisionAttack(m_ObjList[OBJ_ITEM], m_ObjList[OBJ_BOMB]);
	CCollisionMgr::CollisionAttack(m_ObjList[OBJ_ITEM], m_ObjList[OBJ_MONSTER_BOMB]);
	CCollisionMgr::CollisionAttack(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_WAVE]);
	
#endif // _DEBUG

	PlayerBombCollision();

	for (auto& pObj : m_TileVec)
			pObj->Update_Rect();
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& pObj : m_ObjList[i])
		{
			pObj->Update_Rect();
		}
	}
}
void CObjMgr::Render(HDC hDC)
{
	for (auto& pObj : m_TileVec)
		pObj->Render(hDC);
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& pObj : m_ObjList[i])
		{
			pObj->Render(hDC);
		}
	}
	//for (size_t i = 0; i < RENDER_END; ++i)
	//{
	//	m_RenderList[i].sort([](CObj* pDst, CObj* pSrc)->bool
	//		{
	//			return pDst->GetInfo()->fY < pSrc->GetInfo()->fY;
	//		});
	//
	//	for (auto& pObj : m_RenderList[i])
	//		pObj->Render(hDC);
	//
	//	m_RenderList[i].clear();
	//}
}

void CObjMgr::Release() 
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& pObj : m_ObjList[i])
		{
			Safe_Delete(pObj);
		}
		m_ObjList[i].clear();
	}

	for (auto& pObj : m_TileVec)
	{
		Safe_Delete(pObj);
	}
	m_TileVec.clear();
}

void CObjMgr::ChoiceButton()
{
	POINT		ptMouse{};
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);

	for (auto& pButton : m_ObjList[OBJ_BUTTON])
	{
		if (lstrcmp(pButton->GetFrameKey(), L"button_edit"))
			continue;
		if (PtInRect(pButton->GetRect(), ptMouse)
			&& CKeyMgr::GetInstance()->KeyDown(VK_LBUTTON))
		{
			dynamic_cast<CMouse*> (m_ObjList[OBJ_MOUSE].front())->SetChoiceTile(pButton->GetFrame().iStart);
		}
	}
}

void CObjMgr::PutTile()
{
	if (m_ObjList[OBJ_MOUSE].front()->GetInfo()->fX > MAP_RIGHT)
		return;

	POINT		ptMouse{};
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);
	for (auto& pTile : m_TileVec)
	{
		if (PtInRect(pTile->GetRect(), ptMouse))
		{
			if (CKeyMgr::GetInstance()->KeyPressing(VK_LBUTTON))
			{
				TILEID eID = dynamic_cast<CMouse*> (m_ObjList[OBJ_MOUSE].front())->GetChoiceTile();

				pTile->SetStartFrame(eID);
			}
			else if (CKeyMgr::GetInstance()->KeyPressing(VK_RBUTTON))
			{
				pTile->SetStartFrame(0);
			}
		}	
	}
}

void CObjMgr::SaveTile(int iOption)
{
	const WCHAR* pFilePath = L"";
	switch (iOption)
	{
	case 0:
		pFilePath = L"../Data/Tile.dat";
		break;
	case 1:
		pFilePath = L"../Data/Tile1.dat";
		break;
	case 2:
		pFilePath = L"../Data/Tile2.dat";
		break;
	case 3:
		pFilePath = L"../Data/Tile3.dat";
		break;
	default:
		break;
	}
	HANDLE	hFile = CreateFile(pFilePath,		// 파일의 경로
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
	int			iStartFrame(0);
	DWORD		dwByte(0);		// eof 역할하는 변수

	for (auto& pTile : m_TileVec)
	{
		iStartFrame = pTile->GetFrame().iStart;
		WriteFile(hFile, pTile->GetInfo(), sizeof(INFO), &dwByte, nullptr);
		WriteFile(hFile, &iStartFrame, sizeof(TILEID), &dwByte, nullptr);
	}

	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Save 완료"), L"Success", MB_OKCANCEL);
}
void CObjMgr::LoadTile()
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

	DeleteTile();

	int			iStartFrame(0);
	INFO		tTile{};
	DWORD		dwByte(0);		// eof 역할하는 변수

	while (true)
	{
		ReadFile(hFile, &tTile, sizeof(INFO), &dwByte, nullptr);
		ReadFile(hFile, &iStartFrame, sizeof(TILEID), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		CObj* pTile = CAbstractFactory<CTile>::Create(tTile.fX, tTile.fY);
		pTile->SetStartFrame(iStartFrame);
		pTile->SetFrameKey(L"tile");
		m_TileVec.push_back(pTile);
	}

	CloseHandle(hFile);
}

void CObjMgr::LoadStage1()
{
	HANDLE	hFile = CreateFile(L"../Data/Tile1.dat",		// 파일의 경로
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

	DeleteTile();

	int			iStartFrame(0);
	INFO		tTile{};
	DWORD		dwByte(0);		// eof 역할하는 변수

	while (true)
	{
		ReadFile(hFile, &tTile, sizeof(INFO), &dwByte, nullptr);
		ReadFile(hFile, &iStartFrame, sizeof(TILEID), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		CObj* pTile = CAbstractFactory<CTile>::Create(tTile.fX, tTile.fY);
		pTile->SetStartFrame(iStartFrame);
		pTile->SetFrameKey(L"tile");
		m_TileVec.push_back(pTile);
	}

	CloseHandle(hFile);
}

void CObjMgr::LoadStage2()
{
	HANDLE	hFile = CreateFile(L"../Data/Tile2.dat",		// 파일의 경로
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

	DeleteTile();

	int			iStartFrame(0);
	INFO		tTile{};
	DWORD		dwByte(0);		// eof 역할하는 변수

	while (true)
	{
		ReadFile(hFile, &tTile, sizeof(INFO), &dwByte, nullptr);
		ReadFile(hFile, &iStartFrame, sizeof(TILEID), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		CObj* pTile = CAbstractFactory<CTile>::Create(tTile.fX, tTile.fY);
		pTile->SetStartFrame(iStartFrame);
		pTile->SetFrameKey(L"tile");
		m_TileVec.push_back(pTile);
	}

	CloseHandle(hFile);
}

void CObjMgr::LoadStage3()
{
	HANDLE	hFile = CreateFile(L"../Data/Tile3.dat",		// 파일의 경로
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

	DeleteTile();

	int			iStartFrame(0);
	INFO		tTile{};
	DWORD		dwByte(0);		// eof 역할하는 변수

	while (true)
	{
		ReadFile(hFile, &tTile, sizeof(INFO), &dwByte, nullptr);
		ReadFile(hFile, &iStartFrame, sizeof(TILEID), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		CObj* pTile = CAbstractFactory<CTile>::Create(tTile.fX, tTile.fY);
		pTile->SetStartFrame(iStartFrame);
		pTile->SetFrameKey(L"tile");
		m_TileVec.push_back(pTile);
	}

	CloseHandle(hFile);
}

void CObjMgr::DeleteObj(OBJID eID)
{
	for (auto& pObj : m_ObjList[eID])
		Safe_Delete(pObj);
	m_ObjList[eID].clear();
	DeleteTile();
}

void CObjMgr::DeleteTile()
{
	for (auto& pObj : m_TileVec)
		Safe_Delete(pObj);
	m_TileVec.clear();
}

void CObjMgr::TileSwap(int iLeftIndex, int iRightIndex)
{
	int temp = m_TileVec[iLeftIndex]->GetFrame().iStart;
	m_TileVec[iLeftIndex]->SetStartFrame( m_TileVec[iRightIndex]->GetFrame().iStart);
	m_TileVec[iRightIndex]->SetStartFrame(temp);
	//swap(m_TileVec[iLeftIndex], m_TileVec[iRightIndex]);
}

void CObjMgr::PlayerBombCollision()
{
	for (auto& pBomb : m_ObjList[OBJ_BOMB])
	{
		CBomb* pTempBomb = dynamic_cast<CBomb*>(pBomb);
		if (pTempBomb->GetPlayerCollision() == false)
		{
			float fTemp1 = 0.f;
			float fTemp2 = 0.f;
			if (!CCollisionMgr::CheckRect(pTempBomb, m_ObjList[OBJ_PLAYER].front(), fTemp1, fTemp2))
			{
				pTempBomb->SetPlayerCollision();
			}
		}
	}
}

int CObjMgr::GetRemainTile()
{
	int iCnt = 0;
	for (auto& pTile : m_TileVec)
	{
		if (pTile->GetFrame().iStart == 2 || pTile->GetFrame().iStart == 3)
			++iCnt;
	}
	return iCnt;
}
