#include <iostream>
using namespace std;

int iMoney;
bool bIsDoing = true;

void MoneyInput();
void PrintMoney();
int ChoiceInput();
void CheckPurchase(int choiceInput);

int main()
{
	MoneyInput();
	while (bIsDoing)
	{
		system("cls");
		PrintMoney();
		CheckPurchase(ChoiceInput());
		system("pause");
	}
	return 0;
}
void MoneyInput()
{
	cout << "소지금을 입력해주세요:";
	cin >> iMoney;
}

void PrintMoney()
{
	cout << "잔액: "<<iMoney<<endl;
}

int ChoiceInput()
{
	int ichoiceInput;
	cout << "1. 콜라(100원), 2. 사이다(200원), 3. 환타(300원), 4. 반환 : ";
	cin >> ichoiceInput;
	return ichoiceInput;
}

void CheckPurchase(int ichoiceInput)
{
	if (ichoiceInput > 4 || ichoiceInput < 1)
	{
		cout << "잘못된 입력입니다." << endl;
		return;
	}
	if (ichoiceInput == 4)
	{
		bIsDoing = false;
		system("cls");
		cout << "거스름 돈은 "<< iMoney <<"원 입니다."<<endl;
		return;
	}
	if (iMoney >= ichoiceInput * 100)
	{
		iMoney -= ichoiceInput *100;
		switch (ichoiceInput)
		{
		case 1:
			cout << "콜라 구매완료" << endl;
			return;
		case 2:
			cout << "사이다 구매완료" << endl;
			return;
		case 3:
			cout << "환타 구매완료" << endl;
			return;
		}
	}
	else cout << "잔액이 부족합니다." << endl;
}