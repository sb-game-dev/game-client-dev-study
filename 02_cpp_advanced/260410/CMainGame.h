#pragma once
#include "pch.h"
#include "Cstudent.h"
class CMainGame
{
public:
	CMainGame();
	~CMainGame();
public:
	void Initialize();
	void Update();
	void Release();
private:
	CStudent* stu;
};