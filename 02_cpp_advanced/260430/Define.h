#pragma once

struct Info
{
	int iKor, iMath, iEng,iSum;
	float fAver; 
	char szName[32];
};

template<typename T>
void SafeDelete(T*& p)
{
	delete p;
	p = nullptr;
}