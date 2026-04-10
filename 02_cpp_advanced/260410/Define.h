#pragma once
#include "pch.h"
#define SAFE_DELETE(p) if(p){delete p;p = nullptr;}
#define SAFE_DELETE_ARRAY(p) if(p){delete[] p;p = nullptr;}

struct Info
{
	char szName[32];
	int iKor;
	int iMath;
	int iEng;
	int iSum;
	float fAver;
};