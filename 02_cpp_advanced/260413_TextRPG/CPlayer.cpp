#include "CPlayer.h"
#include "Define.h"
CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::Initailize()
{
	int iInput;
	while (true)
	{
		cout << "1. 전사 2. 마법사 3. 도적 4. 데이터 불러오기: ";
		cin >> iInput;

		switch (iInput)
		{
		case CPlayer::WARRIOR:
			strcpy_s(m_tInfo.szName, sizeof(m_tInfo.szName), "전사");
			m_tInfo.iAttack = 10;
			m_tInfo.iHp = 100;
			return;
		case CPlayer::MAGE:
			strcpy_s(m_tInfo.szName, sizeof(m_tInfo.szName), "마법사");
			m_tInfo.iAttack = 10;
			m_tInfo.iHp = 100;
			return;
		case CPlayer::THIEF:
			strcpy_s(m_tInfo.szName, sizeof(m_tInfo.szName), "도적");
			m_tInfo.iAttack = 10;
			m_tInfo.iHp = 100;
			return;
		case CPlayer::LOADDATA:
			LoadData();
			return;
		default:
			break;
		}
	}
}


void CPlayer::Render()
{
	system("cls");
	cout << "===================================" << endl;
	cout << "이름: " << m_tInfo.szName << endl;
	cout << "체력: " << m_tInfo.iHp << "\t" << "공력력: " << m_tInfo.iAttack << endl;
}

void CPlayer::SaveData()
{
	FILE* fWrite = nullptr;
	errno_t err = fopen_s(&fWrite, "./Data/PlayerData.txt", "wb");
	if (err == 0)
	{
		fwrite(&m_tInfo, sizeof(Info), 1, fWrite);
		fclose(fWrite);
	}
}

void CPlayer::LoadData()
{
	FILE* fRead = nullptr;
	errno_t err = fopen_s(&fRead, "./Data/PlayerData.txt", "rb");
	if (err == 0)
	{
		fread(&m_tInfo, sizeof(Info), 1, fRead);
		fclose(fRead);
	}
}