#pragma once
#include "Define.h"
#include "pch.h"
class CGradeCalc
{
public:
	CGradeCalc();
	~CGradeCalc();

public:
	void Add();
	void Render();
	void Search();
	void Delete();

private:
	vector<Info> vecInfo;
};

