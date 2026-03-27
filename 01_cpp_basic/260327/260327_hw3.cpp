#include<iostream>
#include<ctime>
using namespace std;

void CreateNum(int pArr[], int iArrSize);
void PrintAnswer(int pArr[]);
void InputAnswer(int pArr[],int iRound);
bool Check(int pArr[], int pInput[]);
int main()
{
	srand(unsigned(time(NULL)));
	int iArrSize = 0;
	int iArr[3] = {};
	while (iArrSize < 3)
	{
		CreateNum(iArr, iArrSize);
		iArrSize++;
	}

	int iRound = 1;
	while (iRound < 10)
	{
		int iInput[3];
		PrintAnswer(iArr);
		InputAnswer(iInput,iRound);
		if (Check(iArr, iInput))
		{
			cout << "승리!" << endl;
			return 0;
		}
		iRound++;
	}
	cout << "패배!";
}

void CreateNum(int pArr[], int iArrSize)
{
	int iRandNum = rand() % 9 + 1;
	bool bFlag = true;
	for (int i = 0; i < iArrSize; i++)
	{
		if (pArr[i] == iRandNum)
		{
			bFlag = false;
			break;
		}
	}
	if (bFlag) pArr[iArrSize] = iRandNum;
	else CreateNum(pArr, iArrSize);
}

void PrintAnswer(int pArr[])
{
	for (int i = 0; i < 3; i++) cout << pArr[i] << "\t";
}
void InputAnswer(int pArr[],int iRound)
{
	cout <<"/ "<< iRound << "회: ";
	cin >> pArr[0] >> pArr[1] >> pArr[2];
}

bool Check(int pArr[], int pInput[])
{
	int ball = 0, strike = 0;
	for (int i = 0; i < 3; i++)//pInput
	{
		for (int j = 0; j < 3; j++)//pArr
		{
			if (pInput[i] == pArr[j])
			{
				if (i == j)strike++;
				else ball++;
			}
		}
	}
	cout << strike << " 스트라이크, " << ball << "볼" << endl;
	cout << "-----------------------------" << endl;
	if (strike == 3) return 1;
	else return 0;
}