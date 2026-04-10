#include "CStudent.h"
#include "pch.h"
CStudent::CStudent()
{
	m_iSize = 0;
	m_Student = nullptr;
}

CStudent::~CStudent()
{
	Release();
}

void CStudent::Initialize()
{
	
}

void CStudent::Update()
{

}

void CStudent::Release()
{
	SAFE_DELETE(m_Student);
}

void CStudent::AddStudent()
{
	system("cls");
	int iInput = 0;
	cout << "추가할 학생 수를 입력하세요: ";
	cin >> iInput;
	if(!m_Student)
		m_Student = new Info[iInput];
	else
	{
		Info* Temp = new Info[m_iSize + iInput];
		memcpy(Temp, m_Student, sizeof(Info) * m_iSize);
		Release();
		m_Student = Temp;
	}
	for (int i = m_iSize; i < m_iSize + iInput; i++)
	{
		cout << "이름: ";
		cin >> m_Student[i].szName;
		cout << "국어: ";
		cin >> m_Student[i].iKor;
		cout << "수학: ";
		cin >> m_Student[i].iMath;
		cout << "영어: ";
		cin >> m_Student[i].iEng;
		m_Student[i].iSum = m_Student[i].iKor + m_Student[i].iMath + m_Student[i].iEng;
		m_Student[i].fAver = float(m_Student[i].iSum) / 3.f;
	}
	m_iSize += iInput;
}

void CStudent::PrintStudent()
{
	for (int i = 0; i < m_iSize; i++)
	{
		cout << "================================" << endl;
		cout << "이름: ";
		cout << m_Student[i].szName << endl;
		cout << "국어: ";
		cout << m_Student[i].iKor << endl;
		cout << "수학: ";
		cout << m_Student[i].iMath << endl;
		cout << "영어: ";
		cout << m_Student[i].iEng << endl;
		cout << "총합: ";
		cout << m_Student[i].iSum << endl;
		cout << "평균: ";
		cout << m_Student[i].fAver << endl;

	}
}

void CStudent::SearchStudent()
{
	char Temp[32];
	cout << "찾을 학생의 이름을 입력하세요: ";
	cin >> Temp;
	for (int i = 0; i < m_iSize; i++)
	{
		if (!strcmp(Temp, m_Student[i].szName))
		{
			cout << "================================" << endl;
			cout << "이름: ";
			cout << m_Student[i].szName << endl;
			cout << "국어: ";
			cout << m_Student[i].iKor << endl;
			cout << "수학: ";
			cout << m_Student[i].iMath << endl;
			cout << "영어: ";
			cout << m_Student[i].iEng << endl;
			cout << "총합: ";
			cout << m_Student[i].iSum << endl;
			cout << "평균: ";
			cout << m_Student[i].fAver << endl;
			return;
		}
	}
}
