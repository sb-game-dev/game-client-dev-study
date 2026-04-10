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
	int iInput = 0;
	cout << "추가할 학생 수를 입력하세요: ";
	if(!m_Student)
		m_Student = new Info[iInput];
	else
	{
		Info* Temp = new Info[m_iSize + iInput];
		memcpy(Temp, m_Student, sizeof(Info) * m_iSize);

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
}

void CStudent::PrintStudent()
{

}

void CStudent::SearchStudent()
{

}
