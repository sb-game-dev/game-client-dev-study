#include "CMainGame.h"
#include "CGradeCalc.h"

CMainGame::CMainGame()
{
	m_pGradeCalc = nullptr;
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	m_pGradeCalc = new CGradeCalc;
}

void CMainGame::Update()
{
	int iInput;

	while (true)
	{
		system("cls");
		cout<<"1. 추가 2. 출력 3. 검색 4. 삭제 5. 종료: ";
		cin >> iInput;
		switch (iInput)
		{
		case ADD:
			m_pGradeCalc->Add();
			break;
		case RENDER:
			m_pGradeCalc->Render();
			break;
		case SEARCH:
			m_pGradeCalc->Search();
			break;
		case DELETE:
			m_pGradeCalc->Delete();
			break;
		case END:
			return;
		default:
			break;
		}
	}
}

void CMainGame::Release()
{
	SafeDelete(m_pGradeCalc);
}