#include<iostream>
#include<ctime>
using namespace std;

void CreateNum(int pArr[], int iArrSize);
void PrintAnswer(int pArr[]);
void InputAnswer(int pArr[],int iRound);
bool Check(int pArr[], int pInput[]);
int main()
{
	// 3. 야구 게임
	/*
	- 1 ~ 9까지의 숫자 중 무작위로 3개 추출하기
	- 추출한 숫자를 정렬 하지 않은 상태로 매번 화면에 출력
	
	- 3개의 숫자를 입력 받고 입력 받은 숫자와 추출한 숫자의 자리와 값이 모두 일치하면 strike
	- 자리를 다른데 값만 일치하면 ball
	- 매 회 입력 시 N Strike, N Ball 을 출력
	- 3 Strike일 시 게임 승리라고 출력 후 종료
	- 9 라운드까지 진행을 했으나 3 Strike를 완성하지 못하면 패배라고 출력 후 종료
	
	7	1	4
	
	1	2	3	-> 1회 0 스트라이크 1볼
	2	3	4	-> 2회 1 스트라이크 0볼
	1	7	4	-> 3회 1 스트라이크 2볼
	7	1	4	-> 4회 3 스트라이크 0볼
		⁝
	1	2	3	-> 9회 1 스트라이크 0볼 -> 패배 출력 후 종료
	*/
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