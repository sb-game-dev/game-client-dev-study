#include<iostream>
#include<ctime>
using namespace std;
struct st
{
	string even_odd;
};
int* InputPlayer(int*);
int* CreatCom(int* );
void CheckWin(int* pRound, int* pPlayer, int* pCom,int* pWin);
void PrintResult(int* pRound, int* pWin);

int main()
{	
	int iCom = 0, iPlayer = 0, iWin = 0, iRound = 5;
	bool bOnGoing = true;

	while (iRound--)
	{		
		system("cls");
		cout << "---<현재 상태>---" << endl;
		PrintResult(&iRound, &iWin);
		CheckWin(&iRound, InputPlayer(&iPlayer),CreatCom(&iCom),&iWin);
		system("pause");
	}
}

int* InputPlayer(int* pPlayer)
{
	cout << "1.홀수 2.짝수 3.종료: ";
	cin >> *pPlayer;
	return pPlayer;
}

int* CreatCom(int* pCom)
{
	srand(unsigned(time(NULL)));
	*pCom = rand() % 10 + 1;
	return pCom;
}


void CheckWin(int* pRound, int* pPlayer, int* pCom, int* pWin)
{
	st arr[] = { {"짝"},{"홀"} };
	if (*pPlayer > 3 || *pPlayer < 1)
	{
		cout << "잘못된 입력입니다" << endl;
		return;
	}

	if (*pPlayer == 3 )
	{
		cout << "---<경기 결과>---" << endl;
		*pRound += 1;
		PrintResult(pRound,pWin);
		*pRound = 0;
		return;
	}
	cout << "컴퓨터: " << arr[(*pCom+1) % 2].even_odd << "("<<(*pCom)%10+1 << ")" << endl << "사용자: " << arr[*pPlayer % 2].even_odd << endl;

	
	if ((*pCom+1) % 2 == *pPlayer % 2)
	{
		cout << "승!" << endl;
		*pWin+=1;
	}
	else cout << "패!" << endl;

	if (*pRound == 0)
	{
		cout << "---<경기 결과>---" << endl;
		PrintResult(pRound, pWin);
	}
}

void PrintResult(int* pRound,int* pWin)
{
	cout << "Round: " << 5 - *pRound << "\n승리: " << *pWin << "\n패배: " << 5 - *pRound - *pWin << endl;
	cout << "-----------------" << endl;
}