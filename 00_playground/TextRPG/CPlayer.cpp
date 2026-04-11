#include "CPlayer.h"
#include "pch.h"
#include "CMonster.h"

CPlayer::CPlayer()
{
	Player = nullptr;
}
CPlayer::~CPlayer()
{
	Release();
}
void CPlayer::Initialize()
{
	Player = new stPlayer;
	SelectJob();
}
void CPlayer::Update()
{

}
void CPlayer::Release()
{
	SAFE_DELETE(Player);
}
int CPlayer::GetHp() { return Player->iHp; }
int CPlayer::GetGold() { return Player->iGold; }
int CPlayer::GetItem() { return Player->iItem; }
int CPlayer::GetLevel() { return Player->iLevel; }
int CPlayer::GetPower() { return Player->iPower; }

void CPlayer::SetName(const char sTemp[]) { strcpy_s(Player->szName,sizeof(Player->szName),sTemp); }
void CPlayer::SetHp(int iTemp) { Player->iHp = iTemp; }
void CPlayer::SetGold(int iTemp) { Player->iGold = iTemp; }
void CPlayer::SetItem(int iTemp) { Player->iItem = iTemp; }
void CPlayer::SetLevel(int iTemp) { Player->iLevel = iTemp; }
void CPlayer::SetPower(int iTemp) { Player->iPower = iTemp; }

void CPlayer::SelectJob()
{
	int iInput;
	while (true)
	{
		system("cls");
		cout << "직업을 선택하세요 1. 전사 2. 마법사 3. 도적 4. 불러오기: ";
		cin >> iInput;
		switch (iInput)
		{
		case Warrior:
			Player->SetStat("전사", 100, 10,0,1,1);
			return;

		case Mage:
			Player->SetStat("마법사", 100, 10, 0, 1, 1);
			return;

		case Theif:
			Player->SetStat("도적", 100, 10, 0, 1, 1);
			return;

		case LoadData:
			LoadInfo();
			return;
		default:
			SystemMessage("다시 입력해주세요");
			
			break;
		}
	}
}

void CPlayer::TakeDamage(int iEnemyDamage)
{
	if(Player->iHp>0)
		Player->iHp -= iEnemyDamage;
}

void CPlayer::PrintInfo()
{
	system("cls");
	cout << "==========================" << endl;
	cout << "레벨: " << Player->iLevel	<< (Player->iLevel > 9 || Player->iLevel < 0 ? "\t" : "\t\t")	<< "직업:"		<< Player->szName << endl;
	cout << "체력: " << Player->iHp		<< (Player->iHp > 9 || Player->iHp < 0 ? "\t" : "\t\t")			<< "공격력:"	<< Player->iPower << endl;
	cout << "골드: " << Player->iGold	<< (Player->iGold > 9 || Player->iGold < 0 ? "\t" : "\t\t")	<< "아이템:"	<< Player->iItem << endl;

}

void CPlayer::SaveData()
{
	FILE* fWrite = nullptr;
	errno_t err = fopen_s(&fWrite, "./Data/PlayerInfo.txt", "wt");
	if (err == 0)
	{
		fwrite(Player, sizeof(stPlayer), 1, fWrite);

		fclose(fWrite);
	}
}

void CPlayer::LoadInfo()
{
	FILE* fRead = nullptr;
	errno_t err = fopen_s(&fRead, "./Data/PlayerInfo.txt", "rt");
	if (err == 0)
	{
		fread(Player, sizeof(stPlayer), 1, fRead);
		fclose(fRead);
	}
}
