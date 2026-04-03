#include<iostream>
using namespace std;
struct tagStudentInfo
{
	char szName[32];
	int iKor;
	int iEng;
	int iMath;
	int iTotal;
	float fAver;
};
void InputInfo(tagStudentInfo st[]);
void OutPutInfo(tagStudentInfo st[]);
void SearchInfo(tagStudentInfo st[]);
int main()
{
	// 구조체를 이용하여 세 명의 학생의 성적 입출력 프로그램을 만들어라
	// 
	// - 1. 입력 2. 출력 3. 검색 4. 종료
	// - 입력은 세 명 학생의 이름, 국어, 영어, 수학 점수를 입력 받고, 총점과 평균을 계산
	// - 출력은 세 명 학생의 모든 성적 정보를 출력
	// - 검색은 이름을 검색하여 일치하는 이름의 학생 성적 정보만 출력


	tagStudentInfo Arr[3];
	void (*pScoreCalc[3])(tagStudentInfo st[]) = { InputInfo,OutPutInfo,SearchInfo };
	int iInput;
	while (true)
	{
		system("cls");
		cout << "1. 입력 2. 출력 3. 검색 4. 종료: ";
		cin >> iInput;
		if (iInput < 1 || iInput>4)
		{
			cout << "잘못된 입력입니다." << endl;
			continue;
		}
		else if (iInput == 4) return 0;
		pScoreCalc[iInput - 1](Arr);
		system("pause");
	}
}
void InputInfo(tagStudentInfo st[])
{
	for (int i = 0; i < 3; i++)
	{
		cout << i + 1 << "번째 학생 이름: ";
		cin >> st[i].szName;
		cout << i + 1 << "번째 학생 국어점수: ";
		cin >> st[i].iKor;
		cout << i + 1 << "번째 학생 수학점수: ";
		cin >> st[i].iMath;
		cout << i + 1 << "번째 학생 영어점수: ";
		cin >> st[i].iEng;
		st[i].iTotal = st[i].iKor + st[i].iMath + st[i].iEng;
		st[i].fAver = float(st[i].iTotal) / 3.f;
	}
}

void OutPutInfo(tagStudentInfo st[])
{
	for (int i = 0; i < 3; i++)
	{
		cout << i + 1 << "번째 학생 이름: " << st[i].szName << endl;
		cout << i + 1 << "번째 학생 국어점수: " << st[i].iKor << endl;
		cout << i + 1 << "번째 학생 수학점수: " << st[i].iMath << endl;
		cout << i + 1 << "번째 학생 영어점수: " << st[i].iEng << endl;
		cout << i + 1 << "번째 학생 총합: " << st[i].iTotal << endl;
		cout << i + 1 << "번째 학생 평균 점수: " << st[i].fAver << endl;
		
	}
}

void SearchInfo(tagStudentInfo st[])
{
	char szName[32];
	cout << "찾고싶은 학생의 이름을 입력하세요: ";
	cin >> szName;
	for (int i = 0; i < 3; i++)
	{
		if (!strcmp(szName, st[i].szName))
		{
			cout << "이름: " << st[i].szName << endl;
			cout << "국어점수: " << st[i].iKor << endl;
			cout << "수학점수: " << st[i].iMath << endl;
			cout << "영어점수: " << st[i].iEng << endl;
			cout << "총합: " << st[i].iTotal << endl;
			cout << "평균 점수: " << st[i].fAver << endl;
			return;
		}
	}
}