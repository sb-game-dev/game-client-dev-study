#pragma once
#include "pch.h"
#include "Define.h"

class CStudent
{
public:
	CStudent();
	~CStudent();
public:
	void Initialize();
	void Update();
	void Release();
private:
	Info* m_Student;
	int m_iSize;
public:
	void AddStudent();
	void PrintStudent();
	void SearchStudent();
};