#include<iostream>
#include<ctime>
using namespace std;
struct st
{
	string even_odd;
};
int* InputPlayer(int*);
int* CreatCom(int*);
void CheckWin(int* pRound, int* pPlayer, int* pCom, int* pWin, int* pDraw, int* pLose);
void PrintResult(int* pRound, int* pWin,int* pDraw,int *pLose);

int main()
{
	// 4. 가위 바위 보 게임 만들기
// - 난수 0 ~ 2까지 중 하나를 생성한다.(컴퓨터)
// - 1.가위 2.바위 3.보 4.종료(사용자)
// - 사용자가 낸 것과 컴퓨터가 낸 것을 비교 게임 결과를 매 라운드마다 출력
// - 총 5라운드를 실시하여 마지막 라운드가 끝나면(총 라운드), (승), (무), (패)출력!

	int iCom = 0, iPlayer = 0, iWin = 0, iLose = 0, iDraw =0,iRound = 5;
	bool bOnGoing = true;

	while (iRound--)
	{
		system("cls");
		cout << "---<현재 상태>---" << endl;
		PrintResult(&iRound, &iWin, &iDraw, &iLose);
		CheckWin(&iRound, InputPlayer(&iPlayer), CreatCom(&iCom), &iWin,&iDraw,&iLose);
		system("pause");
	}
}

int* InputPlayer(int* pPlayer)
{
	cout << "1.가위 2.바위 3.보 4.종료: ";
	cin >> *pPlayer;
	return pPlayer;
}

int* CreatCom(int* pCom)
{
	srand(unsigned(time(NULL)));
	*pCom = rand() % 3+1;
	return pCom;
}


void CheckWin(int* pRound, int* pPlayer, int* pCom, int* pWin, int* pDraw, int* pLose)
{

	st arr[] = { {""}, { "가위" },{"바위"},{"보"} };
	if (*pPlayer > 4 || *pPlayer < 1)
	{
		cout << "잘못된 입력입니다" << endl;
		return;
	}

	if (*pPlayer == 4)
	{
		system("cls");
		cout << "---<경기 결과>---" << endl;
		*pRound += 1;
		PrintResult(pRound, pWin,pDraw,pLose);
		*pRound = 0;
		return;
	}
	cout << "컴퓨터: " << arr[*pCom].even_odd << endl << "사용자: " << arr[*pPlayer].even_odd << endl;
	//com: 1.가위 2.바위 3.보
	//p-1: 1.바위 2.보   0.가위

	if (*pCom%3 == *pPlayer-1)
	{
		cout << "승!" << endl;
		*pWin += 1;
	}
	else if (*pCom == *pPlayer)
	{
		cout << "무!" << endl;
		*pDraw += 1;
	}
	else
	{
		cout << "패!" << endl;
		*pLose += 1;
	}

	if (*pRound == 0)
	{
		cout << "---<경기 결과>---" << endl;
		PrintResult(pRound, pWin, pDraw, pLose);
	}
}

void PrintResult(int* pRound, int* pWin, int* pDraw, int* pLose)
{
	cout << "Round: " << 5 - *pRound << "\n승리: " << *pWin <<"\n무승부: "<<*pDraw<< "\n패배: " << *pLose << endl;
	cout << "-----------------" << endl;
}