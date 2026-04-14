#pragma once
#define SAFE_DELETE(p) if(p) {delete p;p = nullptr;}
struct Info
{
	char szName[32];
	int iHp, iAttack;
};