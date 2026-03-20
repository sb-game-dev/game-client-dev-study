#include<iostream>
using namespace std;

int main()
{
	// 3. 자판기 구현하기
	// 
	// - 소지금을 입력 받는다.
	// - 항상 잔액을 출력한다.
	// - 1. 콜라(100원), 2. 사이다(200원), 3. 환타(300원), 4. 반환
	// 
	// - 해당 목록 구매 시 “XX 구매 완료” 출력 후, 보유 잔액이 바뀐다.
	// - 단, 소지금이 부족할 경우 “소지금이 부족합니다.”가 출력된다.
	// - 4번을 고르면 “거스름 돈은(소지금) 입니다.” 출력 후 프로그램 종료

	int iMoney = 0,iNum=0;
	cout << "소지금을 입력해주세요: ";
	cin >> iMoney;
	while (1)
	{
		system("cls");
		cout << "현재 잔액: " << iMoney << endl;
		cout << "1. 콜라(100원), 2. 사이다(200원), 3. 환타(300원), 4. 반환: ";
		cin >> iNum;
		switch (iNum)
		{
		case 1:
			if (iMoney >= 100)
			{
				iMoney -= 100;
				cout << "콜라" << endl;
			}
			else
			{
				cout << "잔액이 부족합니다." << endl;
			}
			break;
		
		case 2:
			if (iMoney >= 200)
			{
				iMoney -= 200;
				cout << "사이다" << endl;
			}
			else
			{
				cout << "잔액이 부족합니다." << endl;
			}
			break;
		
		case 3:
			if (iMoney >= 300)
			{
				iMoney -= 300;
				cout << "환타" << endl;
			}
			else
			{
				cout << "잔액이 부족합니다." << endl;
			}
			break;
		case 4:
			cout << "거스름 돈은" << iMoney << "입니다." << endl;
			return 0;
		default:
			cout << "잘못된 입력입니다." << endl;
			break;
		}
		
		system("pause");
	}
	return 0;
}