#include "pch.h"
#include "CObjMgr.h"
#include "CKeyMgr.h"
#include "CMouse.h"
#include "CTile.h"
#include "CAbstractFactory.h"
#include "CCollisionMgr.h"
#include "CBomb.h"
#include "CSceneMgr.h"
CObjMgr* CObjMgr::m_pInstance = nullptr;
CObjMgr::CObjMgr():m_pPlayMode(nullptr)
{
	m_pPlayMode = CSceneMgr::GetInstance()->GetPlayModePtr();
	m_TileVec.reserve(195);
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
	{
		pObj->LateUpdate();
		m_RenderList[GAMEOBJECT].push_back(pObj);
	}

	//for (int i = 0; i < OBJ_END; ++i)
	//{
	//	for (auto& pObj : m_ObjList[i])
	//	{
	//		pObj->LateUpdate();
	//	}
	//}

	for (size_t i = 0; i < OBJ_END; ++i)
	{

		for (auto& pObj : m_ObjList[i])
		{
			pObj->LateUpdate();

			RENDERID eID = pObj->GetRenderID();

			m_RenderList[eID].push_back(pObj);
		}

	}

	if(!m_ObjList[OBJ_BUTTON].empty())
		ChoiceButton();

	if (dynamic_cast<CMouse*>(m_ObjList[OBJ_MOUSE].front())->GetChoiceTile() != TILE_END)
		PutTile();
	if (!m_ObjList[OBJ_MARK].empty() && !m_ObjList[OBJ_PLAYER].empty())
	{
		CCollisionMgr::CollisionAttack(m_ObjList[OBJ_MARK], m_ObjList[OBJ_PLAYER]);
	}
	if (!m_ObjList[OBJ_BOMB].empty() && !m_ObjList[OBJ_PLAYER].empty())
	{
		CCollisionMgr::CollisionBody(m_ObjList[OBJ_BOMB], m_ObjList[OBJ_PLAYER]);
		CCollisionMgr::CollisionBody(m_ObjList[OBJ_BOMB], m_ObjList[OBJ_BOMB]);
		CCollisionMgr::CollisionAttack(m_ObjList[OBJ_BOMB], m_ObjList[OBJ_WAVE]);
		CCollisionMgr::CollisionAttack(m_ObjList[OBJ_BOMB], m_ObjList[OBJ_DART]);


		CCollisionMgr::CollisionBody(m_ObjList[OBJ_BOMB], m_ObjList[OBJ_PLAYER2]);
	}
	
	if (!m_ObjList[OBJ_ITEM].empty() && !m_ObjList[OBJ_PLAYER].empty())
	{
		CCollisionMgr::CollisionAttack(m_ObjList[OBJ_ITEM], m_ObjList[OBJ_PLAYER]);
		CCollisionMgr::CollisionAttack(m_ObjList[OBJ_ITEM], m_ObjList[OBJ_WAVE]);
	}
	if (!m_ObjList[OBJ_MONSTER].empty() && !m_ObjList[OBJ_PLAYER].empty())
	{
		CCollisionMgr::CollisionAttack(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_MONSTER]);
		CCollisionMgr::CollisionAttack(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_WAVE]);
		//CCollisionMgr::CollisionBody(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_BOMB]);
		CCollisionMgr::CollisionAttack(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_BOMB]);
		//CCollisionMgr::CollisionBody(m_ObjList[OBJ_MONSTER], m_TileVec);
	}

	if (!m_ObjList[OBJ_BOSS].empty() && !m_ObjList[OBJ_PLAYER].empty())
	{
		CCollisionMgr::CollisionAttack(m_ObjList[OBJ_BOSS], m_ObjList[OBJ_WAVE]);
		CCollisionMgr::CollisionAttack(m_ObjList[OBJ_BOMB], m_ObjList[OBJ_BOSS]);
		CCollisionMgr::CollisionAttack(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_BOSS]);
		if (GetRemainTile() == 0)
		{
			CCollisionMgr::CollisionBody(m_ObjList[OBJ_BOSS_BOMB], m_ObjList[OBJ_PLAYER]);
			CCollisionMgr::CollisionBody(m_ObjList[OBJ_BOSS_BOMB], m_ObjList[OBJ_BOSS_BOMB]);
			CCollisionMgr::CollisionBody(m_ObjList[OBJ_BOMB], m_ObjList[OBJ_BOSS_BOMB]);
			CCollisionMgr::CollisionBody(m_ObjList[OBJ_BOMB2], m_ObjList[OBJ_BOSS_BOMB]);
			CCollisionMgr::CollisionAttack(m_ObjList[OBJ_BOSS_BOMB], m_ObjList[OBJ_WAVE]);
		}
	}
	if(GetRemainTile() > 0 && !m_ObjList[OBJ_PLAYER].empty())
	{
		CCollisionMgr::CollisionAttack(m_TileVec, m_ObjList[OBJ_DART]);
		CCollisionMgr::CollisionAttack(m_TileVec, m_ObjList[OBJ_WAVE]);
		CCollisionMgr::CollisionBody(m_TileVec, m_ObjList[OBJ_PLAYER]);
		CCollisionMgr::CollisionBody(m_TileVec, m_ObjList[OBJ_BOMB]);
		CCollisionMgr::CollisionBody(m_TileVec, m_ObjList[OBJ_BOMB2]);
		CCollisionMgr::CollisionBody(m_ObjList[OBJ_BOMB], m_TileVec);
		CCollisionMgr::CollisionBody(m_ObjList[OBJ_BOMB2], m_TileVec);
	}
	if (!m_ObjList[OBJ_GASSTATION].empty() && !m_ObjList[OBJ_PLAYER].empty())
	{
		CCollisionMgr::CollisionBody(m_ObjList[OBJ_GASSTATION], m_ObjList[OBJ_PLAYER]);
	}

	if (!m_ObjList[OBJ_PLAYER].empty())
	{
		CCollisionMgr::CollisionAttack(m_ObjList[OBJ_ITEM], m_ObjList[OBJ_BOMB]);
		CCollisionMgr::CollisionAttack(m_ObjList[OBJ_ITEM], m_ObjList[OBJ_BOSS_BOMB]);
		CCollisionMgr::CollisionAttack(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_WAVE]);
	}

	if (*m_pPlayMode == MODE2P)
	{
		if (!m_ObjList[OBJ_MARK].empty() && !m_ObjList[OBJ_PLAYER2].empty())
		{
			CCollisionMgr::CollisionAttack(m_ObjList[OBJ_MARK], m_ObjList[OBJ_PLAYER2]);
		}
		if (!m_ObjList[OBJ_BOMB2].empty() && !m_ObjList[OBJ_PLAYER2].empty())
		{
			CCollisionMgr::CollisionBody(m_ObjList[OBJ_BOMB2], m_ObjList[OBJ_PLAYER2]);
			CCollisionMgr::CollisionBody(m_ObjList[OBJ_BOMB2], m_ObjList[OBJ_BOMB2]);
			CCollisionMgr::CollisionBody(m_ObjList[OBJ_BOMB2], m_ObjList[OBJ_BOMB]);
			CCollisionMgr::CollisionBody(m_ObjList[OBJ_BOMB], m_ObjList[OBJ_BOMB2]);
			CCollisionMgr::CollisionAttack(m_ObjList[OBJ_BOMB2], m_ObjList[OBJ_WAVE]);
			CCollisionMgr::CollisionAttack(m_ObjList[OBJ_BOMB2], m_ObjList[OBJ_DART]);


			CCollisionMgr::CollisionBody(m_ObjList[OBJ_BOMB2], m_ObjList[OBJ_PLAYER]);
		}

		if (!m_ObjList[OBJ_ITEM].empty() && !m_ObjList[OBJ_PLAYER2].empty())
		{
			CCollisionMgr::CollisionAttack(m_ObjList[OBJ_ITEM], m_ObjList[OBJ_PLAYER2]);

			//CCollisionMgr::CollisionAttack(m_ObjList[OBJ_ITEM], m_ObjList[OBJ_WAVE]);
		}
		if (!m_ObjList[OBJ_MONSTER].empty() && !m_ObjList[OBJ_PLAYER2].empty())
		{
			CCollisionMgr::CollisionAttack(m_ObjList[OBJ_PLAYER2], m_ObjList[OBJ_MONSTER]);
			CCollisionMgr::CollisionAttack(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_BOMB2]);

			//CCollisionMgr::CollisionBody(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_BOMB2]);
			//CCollisionMgr::CollisionAttack(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_WAVE]);
			//CCollisionMgr::CollisionBody(m_ObjList[OBJ_MONSTER], m_TileVec);
		}

		if (!m_ObjList[OBJ_BOSS].empty() && !m_ObjList[OBJ_PLAYER2].empty())
		{
			CCollisionMgr::CollisionAttack(m_ObjList[OBJ_BOSS], m_ObjList[OBJ_WAVE]);
			CCollisionMgr::CollisionAttack(m_ObjList[OBJ_BOMB2], m_ObjList[OBJ_BOSS]);
			CCollisionMgr::CollisionAttack(m_ObjList[OBJ_PLAYER2], m_ObjList[OBJ_BOSS]);
			if (GetRemainTile() == 0)
			{
				CCollisionMgr::CollisionBody(m_ObjList[OBJ_BOSS_BOMB], m_ObjList[OBJ_PLAYER2]);
				CCollisionMgr::CollisionBody(m_ObjList[OBJ_BOSS_BOMB], m_ObjList[OBJ_BOSS_BOMB]);
				CCollisionMgr::CollisionBody(m_ObjList[OBJ_BOMB2], m_ObjList[OBJ_BOSS_BOMB]);
				CCollisionMgr::CollisionAttack(m_ObjList[OBJ_BOSS_BOMB], m_ObjList[OBJ_WAVE]);
			}
		}
		if (GetRemainTile() > 0 && !m_ObjList[OBJ_PLAYER2].empty())
		{
			CCollisionMgr::CollisionAttack(m_TileVec, m_ObjList[OBJ_DART]);
			CCollisionMgr::CollisionAttack(m_TileVec, m_ObjList[OBJ_WAVE]);
			CCollisionMgr::CollisionBody(m_TileVec, m_ObjList[OBJ_PLAYER2]);
			CCollisionMgr::CollisionBody(m_TileVec, m_ObjList[OBJ_BOMB2]);
			CCollisionMgr::CollisionBody(m_ObjList[OBJ_BOMB2], m_TileVec);
		}
		if (!m_ObjList[OBJ_GASSTATION].empty() && !m_ObjList[OBJ_PLAYER2].empty())
		{
			CCollisionMgr::CollisionBody(m_ObjList[OBJ_GASSTATION], m_ObjList[OBJ_PLAYER2]);
		}

		if (!m_ObjList[OBJ_PLAYER2].empty())
		{
			CCollisionMgr::CollisionAttack(m_ObjList[OBJ_ITEM], m_ObjList[OBJ_BOMB2]);
			CCollisionMgr::CollisionAttack(m_ObjList[OBJ_ITEM], m_ObjList[OBJ_BOSS_BOMB]);
			CCollisionMgr::CollisionAttack(m_ObjList[OBJ_PLAYER2], m_ObjList[OBJ_WAVE]);
		}
	}


	if (!m_ObjList[OBJ_PLAYER].empty())
	{
		PlayerBombCollision();
	}
	if (!m_ObjList[OBJ_PLAYER2].empty())
	{
		Player2BombCollision();
	}
	if (!m_ObjList[OBJ_PLAYER].empty() && !m_ObjList[OBJ_PLAYER2].empty())
	{
		CCollisionMgr::CollisionAttack(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_PLAYER2]);
		CCollisionMgr::CollisionAttack(m_ObjList[OBJ_PLAYER2], m_ObjList[OBJ_PLAYER]);
	}
	for (auto& pObj : m_TileVec)
			pObj->Update_Rect();
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& pObj : m_ObjList[i])
		{
			pObj->Update_Rect();
		}
	}

	//cout << GetRemainDart() << endl;
}
void CObjMgr::Render(HDC hDC)
{

	if (CSceneMgr::GetInstance()->GetCurScene() == SC_LOGIN)
	{
		for (int i = 0; i < OBJ_END; ++i)
		{
			for (auto& pObj : m_ObjList[i])
			{
				pObj->Render(hDC);
			}
		}
	}
	else
	{
		for (size_t i = 0; i < RENDER_END; ++i)
		{
			m_RenderList[i].sort([](CObj* pDst, CObj* pSrc)->bool
				{
					return pDst->GetRect()->bottom < pSrc->GetRect()->bottom;
				});

			for (auto& pObj : m_RenderList[i])
				pObj->Render(hDC);
			m_RenderList[i].clear();
		}
	}
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
		if (!lstrcmp(pButton->GetFrameKey(), L"button_edit"))
		{
			if (PtInRect(pButton->GetRect(), ptMouse)
				&& CKeyMgr::GetInstance()->KeyDown(VK_LBUTTON))
			{
				dynamic_cast<CMouse*> (m_ObjList[OBJ_MOUSE].front())->SetChoiceTile(pButton->GetFrame().iStart);
			}
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
			if (CKeyMgr::GetInstance()->KeyPressing(VK_RBUTTON))
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
	case 4:
		pFilePath = L"../Data/Tile4.dat";
		break;
	case 5:
		pFilePath = L"../Data/Tile5.dat";
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
	bool		bDraw;
	for (auto& pTile : m_TileVec)
	{
		iStartFrame = pTile->GetFrame().iStart;
		WriteFile(hFile, pTile->GetInfo(), sizeof(INFO), &dwByte, nullptr);
		WriteFile(hFile, &iStartFrame, sizeof(TILEID), &dwByte, nullptr);
	}

	CloseHandle(hFile);

	MessageBox(g_hWnd, pFilePath, L"Success", MB_OKCANCEL);
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

void CObjMgr::LoadStage4()
{
	HANDLE	hFile = CreateFile(L"../Data/Tile4.dat",		// 파일의 경로
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
void CObjMgr::LoadStage5()
{
	HANDLE	hFile = CreateFile(L"../Data/Tile5.dat",		// 파일의 경로
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
	//cout << "TileSwap" << endl;
	//cout << "LeftIndex = " << iLeftIndex << "\tRightIndex = " << iRightIndex << endl;
	swap(m_TileVec[iLeftIndex], m_TileVec[iRightIndex]);
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
void CObjMgr::Player2BombCollision()
{
	for (auto& pBomb : m_ObjList[OBJ_BOMB2])
	{
		CBomb* pTempBomb = dynamic_cast<CBomb*>(pBomb);
		if (pTempBomb->GetPlayerCollision() == false)
		{
			float fTemp1 = 0.f;
			float fTemp2 = 0.f;
			if (!CCollisionMgr::CheckRect(pTempBomb, m_ObjList[OBJ_PLAYER2].front(), fTemp1, fTemp2))
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
		if (pTile->GetFrame().iStart == 2 
			|| pTile->GetFrame().iStart == 3 
			|| pTile->GetFrame().iStart == 18 
			|| pTile->GetFrame().iStart == 19
			|| (pTile->GetFrame().iStart>=31 && pTile->GetFrame().iStart<=34))
			++iCnt;
	}
	return iCnt;
}

void CObjMgr::DestroyMonster()
{
	for (auto& pMonster : m_ObjList[OBJ_MONSTER])
	{
		pMonster->SetHit();
	}
}

void CObjMgr::ReleaseRenderList()
{
	for (size_t i = 0; i < RENDER_END; ++i)
		m_RenderList[i].clear();
}

