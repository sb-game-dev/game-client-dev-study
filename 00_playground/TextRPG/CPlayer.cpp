#include "CPlayer.h"
#include "pch.h"

void CPlayer::SetName(const char cTemp[]) { strcpy_s(m_szName,sizeof(m_szName),cTemp); }
char* CPlayer::GetName() {return m_szName;}
void CPlayer::SetHp(int iNum) {m_iHp = iNum;}
int CPlayer::GetHp() { return m_iHp; }
void CPlayer::SetPower(int iNum) { m_iPower = iNum; }
int CPlayer::GetPower() { return m_iPower; }
void CPlayer::SetLevel(int iNum) { m_iLevel = iNum; }
int CPlayer::GetLevel() { return m_iLevel; }
void CPlayer::SetGold(int iNum) { m_iGold = iNum; }
int CPlayer::GetGold() { return m_iGold; }
void CPlayer::SetItem(int iNum) { m_iItem = iNum; }
int CPlayer::GetItem() { return m_iItem; }

void CPlayer::PrintPlayer()
{
	system("cls");
	cout << "==================================" << endl;
	cout << "레벨: " << m_iLevel	<< ((m_iLevel > 9) ? "\t" : "\t\t")	<< "직업: " << m_szName << endl;
	cout << "체력: " << m_iHp		<< ((m_iHp > 9) ? "\t" : "\t\t")	<< "공격력: " << m_iPower<< endl;
	cout << "골드: " << m_iGold		<< ((m_iGold > 9) ? "\t" : "\t\t")	<< "아이템: " << m_szName << endl;
	//색 추가
}

void CPlayer::SelectJob(CPlayer** ppPlayer)
{
	int iInput = 0;
	while (true)
	{
		cout << "직업을 선택하세요(1. 전사 2. 마법사 3. 도적 . 4. 불러오기): ";
		cin >> iInput;
		switch (iInput)
		{
		case Warrior:
			CreatePlayer("전사",100,10);
			SavePlayer();
			return;
		case Mage:
			CreatePlayer("마법사", 100, 10);
			SavePlayer();
			return;
		case Thief:
			CreatePlayer("도적", 100, 10);
			SavePlayer();
			return;
		case LastJob:
			LoadPlayer(*ppPlayer);
			return;
		default:
			break;
		}
	}
}

void CPlayer::CreatePlayer(const char szName[], int iHp, int iPower)
{
	SetName(szName);
	SetHp(iHp);
	SetPower(iPower);
}

void CPlayer::LoadPlayer(CPlayer* ppPlayer)
{
	FILE* fRead = nullptr;
	errno_t err = fopen_s(&fRead, "./Data/PlayerInfo.txt", "rb");
	if (err == 0)
	{
		fread((ppPlayer), sizeof(CPlayer), 1, fRead);
		fclose(fRead);
	}
}

void CPlayer::SavePlayer()
{
	FILE* fWrite = nullptr;
	errno_t err = fopen_s(&fWrite, "./Data/PlayerInfo.txt", "wb");
	if (err == 0)
	{
		fwrite(this, sizeof(CPlayer), 1, fWrite);
		fclose(fWrite);	
	}
}

void CPlayer::EnemyAttack(int iPower)
{
	m_iHp -= iPower;
}