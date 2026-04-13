#pragma once
#include <iostream>
#define SAFE_DELETE(p) if(p) {delete p;p = nullptr;}
using namespace std;

struct Info
{
	char szName[32];
	int iHp, iAttack;
};