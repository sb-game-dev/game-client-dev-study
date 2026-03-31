#include<iostream>
using namespace std;
void PrintArr(int(*pArr)[5]);
void MoveZero(int(*pArr)[5],int* ,int*);
bool CheckEnd(int(*pArr)[5]);
int main()
{
	int iArr[5][5] = {};
	int iPlayer[26] = {};
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			iArr[i][j] = i * 5 + j + 1;
		}
	}
	iArr[4][4] = 0;
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
	int iZeroRow = 0, iZeroCol = 0;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (iArr[i][j] == 0)
			{
				iZeroRow = i;
				iZeroCol = j;
			}
		}
	}
	while (true)
	{
		system("cls");
		
		PrintArr(iArr);
		MoveZero(iArr,&iZeroRow,&iZeroCol);
		
		if (CheckEnd(iArr))break;
	}
	PrintArr(iArr);
	cout << "승리!" << endl;
}

void PrintArr(int(*pArr)[5])
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (!pArr[i][j]) cout << "[ ]" << "\t";
			else cout << pArr[i][j]<<"\t";
		}
		cout << endl;
	}
}


void MoveZero(int(*pArr)[5], int* iZeroRow, int* iZeroCol)
{
	char iInput = 0;
	cout << "w,a,s,d중 하나의 숫자를 입력해주세요: ";
	cin >> iInput;
	if (iInput == 's')
	{
		if (*iZeroRow + 1 >= 5) cout << "다시 입력하세요" << endl;
		else
		{
			swap(pArr[*iZeroRow][*iZeroCol], pArr[*iZeroRow + 1][*iZeroCol]);
			*iZeroRow += 1;
		}
	}
	if (iInput == 'a')
	{
		if (*iZeroCol - 1 < 0) cout << "다시 입력하세요" << endl;
		else
		{
			swap(pArr[*iZeroRow][*iZeroCol], pArr[*iZeroRow][*iZeroCol - 1]);
			*iZeroCol -= 1;
		}
	}

	if (iInput == 'd')
	{
		if (*iZeroCol + 1 >= 5) cout << "다시 입력하세요" << endl;
		else
		{
			swap(pArr[*iZeroRow][*iZeroCol], pArr[*iZeroRow][*iZeroCol + 1]);
			*iZeroCol += 1;
		}
	}

	if (iInput == 'w')
	{
		if (*iZeroRow - 1 < 0) cout << "다시 입력하세요" << endl;
		else
		{
			swap(pArr[*iZeroRow][*iZeroCol], pArr[*iZeroRow - 1][*iZeroCol]);
			*iZeroRow -= 1;
		}
	}
}

bool CheckEnd(int(*pArr)[5])
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (i * 5 + j + 1 == 25) break;
			if (pArr[i][j] != i*5+j+1)return false;
		}
	}
	return true;
}