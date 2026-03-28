#include<iostream>
#include<ctime>
using namespace std;
void CreateLottoNum(int pArr[], int iArrSize);
void PrintLotto(int pArr[],int iCnt);
void Swap(int* pLeft, int* pRight);
void BubbleSort(int pArr[],int iArrSize);
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
		BubbleSort(iArr,sizeof(iArr)/sizeof(int));
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


void Swap(int* pLeft, int* pRight)
{
	int iTemp = *pLeft;
	*pLeft = *pRight;
	*pRight = iTemp;
}
void BubbleSort(int pArr[], int iArrSize)
{
	for (int i = iArrSize-1; i > 0; i--)
	{
		for (int j = 0; j < i; j++)
		{
			if (pArr[j] > pArr[j + 1])
			{
				Swap(&pArr[j], &pArr[j + 1]);
			}
		}
	}
}