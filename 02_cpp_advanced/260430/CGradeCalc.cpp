#include "CGradeCalc.h"
#include "CMainGame.h"

CGradeCalc::CGradeCalc()
{
}

CGradeCalc::~CGradeCalc()
{
}


void CGradeCalc::Add()
{
	int iInput;
	char szName[32];
	int iKor;
	int iMath;
	int iEng;
	system("cls");
	cout << "추가할 학생 수를 입력해주세요: ";
	cin >> iInput;

	for (int i = 0; i < iInput; ++i)
	{
		system("cls");
		cout << i + 1 << "번째 학생 이름: ";
		cin >> szName;
		cout << i + 1 << "번째 학생 국어 점수: ";
		cin >> iKor;
		cout << i + 1 << "번째 학생 수학 점수: ";
		cin >> iMath;
		cout << i + 1 << "번째 학생 영어 점수: ";
		cin >> iEng;
		vecInfo.push_back({ iKor,iMath,iEng,iKor+iMath+iEng,float((iKor + iMath + iEng)/3.f)});
		strcpy_s(vecInfo.back().szName, sizeof(vecInfo.back().szName), szName);
	}
}

void CGradeCalc::Render()
{
	system("cls");
	if (vecInfo.size() == 0)
	{
		cout << "학생을 한 명이라도 입력해주세요" << endl;
		system("pause");
		return;
	}
	for (int i = 0; i < vecInfo.size(); ++i)
	{
		cout << i + 1 << "번째 학생 이름: " << vecInfo[i].szName << endl;
		cout << i + 1 << "번째 학생 국어: " << vecInfo[i].iKor << endl;
		cout << i + 1 << "번째 학생 수학: " << vecInfo[i].iMath << endl;
		cout << i + 1 << "번째 학생 영어: " << vecInfo[i].iEng << endl;
		cout << i + 1 << "번째 학생 평균: " << vecInfo[i].iSum << endl;
		cout << i + 1 << "번째 학생 총점: " << vecInfo[i].fAver << endl;
		cout << "=========================================" << endl;
	}
	system("pause");
}

void CGradeCalc::Search()
{
	system("cls");
	if (vecInfo.size() == 0)
	{
		cout << "학생을 한 명이라도 입력해주세요" << endl;
		system("pause");
		return;
	}
	char szTempName[32];

	cout << "찾을 학생의 이름을 입력해주세요: ";
	cin >> szTempName;
	for (vector<Info>::iterator it = vecInfo.begin();it!=vecInfo.end();++it)
	{
		if (!strcmp(it->szName, szTempName))
		{
			cout << "이름: " << it->szName << endl;
			cout << "국어: " << it->iKor << endl;
			cout << "수학: " << it->iMath << endl;
			cout << "영어: " << it->iEng << endl;
			cout << "평균: " << it->iSum << endl;
			cout << "총점: " << it->fAver << endl;
			cout << "=========================================" << endl;
			system("pause");
			return;
		}
	}
	cout << "찾는 학생이 없습니다." << endl;
	system("pause");
	return;
}

void CGradeCalc::Delete()
{
	system("cls");
	if (vecInfo.size() == 0)
	{
		cout << "학생을 한 명이라도 입력해주세요" << endl;
		system("pause");
		return;
	}
	char szTempName[32];

	cout << "삭제할 학생의 이름을 입력해주세요: ";
	cin >> szTempName;
	for (vector<Info>::iterator it = vecInfo.begin(); it != vecInfo.end(); ++it)
	{
		if (!strcmp(it->szName, szTempName))
		{
			vecInfo.erase(it);
			cout << "삭제되었습니다." << endl;
			system("pause");
			return;
		}
	}
	cout << "찾는 학생이 없습니다." << endl;
	system("pause");
	return;
}


