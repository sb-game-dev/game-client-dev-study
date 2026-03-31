#include<iostream>
#include<ctime>
using namespace std;
void PrintArr(int (*pArr)[5],int pPlayer[],int pCom[]);
void InputPlayer(int (*pArr)[5], int pPlayer[], int pCom[]);
void ComTurn(int (*pArr)[5], int pPlayer[], int pCom[],int iCnt);
int CheckWinner(int (*pArr)[5], int pPlayer[]);
int main()
{
	int iArr[5][5] = {};
	int iPlayer[26] = {};
	int iCom[26] = {};
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			iArr[i][j] = i * 5 + j + 1;
		}
	}
	srand(unsigned(time(NULL)));
	for (int i = 0; i < 500; i++)
	{
		int iDstRow = 0, iSrcCol = 0, iDstCol = 0, iSrcRow = 0;
		iDstRow = rand() % 5;
		iSrcRow = rand() % 5;
		iDstCol = rand() % 5;
		iSrcCol = rand() % 5;

		swap(iArr[iDstRow][iDstCol], iArr[iSrcRow][iSrcCol]);
	}
	int iCnt = 0;
	while (true)
	{
		system("cls");
		PrintArr(iArr, iPlayer, iCom);
		
		InputPlayer(iArr, iPlayer, iCom);
		iCnt++;

		ComTurn(iArr, iPlayer, iCom, iCnt);
		iCnt++;

		if (CheckWinner(iArr, iPlayer)||CheckWinner(iArr,iCom)||iCnt>=25) break;
		system("pause");
	}
	if (CheckWinner(iArr, iPlayer)) cout << "플레이어 승!" << endl;
	else if (CheckWinner(iArr, iCom)) cout << "컴퓨터 승!" << endl;
	else cout << "무승부!" << endl;
}

void PrintArr(int (*pArr)[5], int pPlayer[], int pCom[])
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (pPlayer[pArr[i][j]]) cout << "p"<<"\t";
			else if(pCom[pArr[i][j]]) cout << "c"<<"\t";
			else cout << pArr[i][j] << "\t";
		}
		cout << endl;
	}
}

void InputPlayer(int (*pArr)[5], int pPlayer[], int pCom[])
{
	int iInput;
	cout << "플레어이 차례입니다. 숫자를 입력해주세요: ";
	cin >> iInput;
	if (pPlayer[iInput] || pCom[iInput])
	{
		cout << "이미 선택된 숫자입니다. 다시 입력하세요" << endl;
		InputPlayer(pArr, pPlayer, pCom);
	}
	else
	{
		pPlayer[iInput] = 1;
	}
}

void ComTurn(int (*pArr)[5], int pPlayer[], int pCom[], int iCnt)
{
	int iCom = rand() % 25 + 1;
	if (iCnt == 25) return;
	if (pPlayer[iCom] || pCom[iCom])
	{
		ComTurn(pArr, pPlayer, pCom,iCnt);
	}
	else
	{
		cout << "컴퓨터가 선택한 숫자는: " << iCom << endl;
		pCom[iCom] = 1;
	}
}

int CheckWinner(int (*pArr)[5], int pCheckArr[])
{
	int iCnt = 0;
	for (int i = 0; i < 5; i++)
	{
		int bFlag = true;
		for (int j = 0; j < 4; j++)
		{
			if (pCheckArr[pArr[i][j]] == 0 || pCheckArr[pArr[i][j + 1]]==0)
			{
				bFlag = false;
				break;
			}
		}
		if (bFlag) iCnt++;
	}
	for (int i = 0; i < 5; i++)
	{
		int bFlag = true;
		for (int j = 0; j < 4; j++)
		{
			if (pCheckArr[pArr[j][i]] == 0 || pCheckArr[pArr[j+1][i]] == 0)
			{
				bFlag = false;
				break;
			}
		}
		if (bFlag) iCnt++;
	}

	int bFlag = true;
	for (int i = 0; i < 4; i++)
	{
		if (pCheckArr[pArr[i][i]] ==0 || pCheckArr[pArr[i+1][i + 1]]==0)
		{
			bFlag = false;
			break;
		}
	}
	if (bFlag) iCnt++;

	bFlag = true;
	for (int i = 0; i < 4; i++)
	{
		if (pCheckArr[pArr[i][4-i]] == 0 || pCheckArr[pArr[i + 1][4-(i + 1)]]==0)
		{
			bFlag = false;
			break;
		}
	}
	if (bFlag) iCnt++;
	
	
	if (iCnt >= 5) return 1;
	else return 0;
}
