#include<iostream>
using namespace std;
void InputScore(float* pScore);
void PrintScore(float* );
int main()
{
	float fScore = 0.f;
	InputScore(&fScore);
	PrintScore(&fScore);
}

void InputScore(float* pScr)
{
	cout << "점수를 입력해주세요: ";
	cin >> *pScr;
}

void PrintScore(float* pScore)
{
	if (*pScore > 100.f || *pScore < 0.f)
	{
		cout << "잘못입력하셨습니다." << endl;
	}
	else
	{
		if (*pScore >= 90.f) cout << "A학점" << endl;
		else if (*pScore >= 80.f) cout << "B학점" << endl;
		else if (*pScore >= 70.f) cout << "C학점" << endl;
		else if (*pScore >= 60.f) cout << "D학점" << endl;
		else cout << "F학점" << endl;
	}
}
