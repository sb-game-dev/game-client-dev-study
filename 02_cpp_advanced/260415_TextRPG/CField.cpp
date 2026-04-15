#include "CField.h"
#include "CPlayer.h"

CField::CField()
{
	m_copyPlayer = nullptr;
}

CField::~CField()
{
	Release();
}

void CField::Initialize()
{
}

void CField::Update()
{
	int iInput;
	while (true)
	{
		m_copyPlayer->Render();
		cout << "1. 사냥 2. 종료: ";
		cin >> iInput;
		switch (iInput)
		{
		case 1:
			break;
		case 2:
			return;
		default:
			break;
		}
	}
}

void CField::Release()
{
	m_copyPlayer->Destroy();
}

CField* CField::Create()
{
	CField* pField = new CField;
	return pField;
}

void CField::Destroy()
{
	delete this;
}