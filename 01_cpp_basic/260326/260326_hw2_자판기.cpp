#include<iostream>
using namespace std;
void InputMoney(int* pMoney);
void PrintMoney(int* );
void InputChoice(int*);
void CheckBuy(int* pNumber,int* pMoney,bool*);
struct st
{
	string menu_name;
	int iPrice;
};
int main()
{
	int iMoney = 0,iChoice=0;
	bool bOnGoing = true;
	InputMoney(&iMoney);
	while (bOnGoing)
	{
		system("cls");
		PrintMoney(&iMoney);
		InputChoice(&iChoice);
		CheckBuy(&iChoice, &iMoney, &bOnGoing);
		system("pause");
	}
}

void InputMoney(int* pMoney)
{
	cout << "돈을 입력하세요: ";
	cin >> *pMoney;
}
void PrintMoney(int* pMoney)
{
	cout << "현재 잔액: " << *pMoney << "원" << endl;
}
void InputChoice(int* pChoice)
{
	cout << "1. 콜라(100원), 2. 사이다(200원), 3. 환타(300원), 4. 반환: ";
	cin >> *pChoice;
}
void CheckBuy(int* pChoice, int* pMoney, bool* pOnGoing)
{
	st arr[] = { {"NULL",0},{"콜라",100},{"사이다",200},{"환타",300} };
	if (*pChoice > 4 || *pChoice < 1)
	{
		cout << "잘못 입력하셨습니다." << endl;
		return;
	}
	if (*pChoice == 4)
	{
		cout << "거스름돈은 " << *pMoney << "원 입니다." << endl;
		*pOnGoing = false;
		return;
	}
	if (*pMoney >= *pChoice*100)
	{
		*pMoney -= arr[*pChoice].iPrice;
		cout << arr[*pChoice].menu_name << endl;
	}
	else
	{
		cout << "잔액이 부족합니다." << endl;
	}
}