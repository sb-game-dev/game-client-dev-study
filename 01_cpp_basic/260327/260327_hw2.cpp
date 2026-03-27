#include<iostream>
#include<ctime>
using namespace std;
void CreateLottoNum(int pArr[], int iArrSize);
void PrintLotto(int pArr[],int iCnt);
int main()
{
	srand(unsigned(time(NULL)));
	int iCnt = 5;
	while (iCnt--)
	{
		int iArrSize = 0;
		int iArr[6] = {};
		while (iArrSize < 6)
		{
			CreateLottoNum(iArr, iArrSize);
			iArrSize++;
		}
		PrintLotto(iArr, iCnt);
	}
}

void CreateLottoNum(int pArr[], int iArrSize)
{
	int iRandNum = rand() % 45 + 1;
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
	else CreateLottoNum(pArr, iArrSize);
}
void PrintLotto(int pArr[], int iCnt)
{

	cout << "<" << 5 - iCnt << "ȸ>\n";
	for (int i = 0; i < 6; i++)
	{
		cout << pArr[i] << "\t";
	}
	cout << endl;
}