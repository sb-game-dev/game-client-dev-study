#pragma once
#include "pch.h"
#include "Cstudent.h"
class GMainGame
{
public:
	void Initialize();
	void Update();
	void Release();
private:
	CStudent* stu;
};