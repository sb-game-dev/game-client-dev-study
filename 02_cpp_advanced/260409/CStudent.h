#pragma once
#include<iostream>
using namespace std;

class CStudent
{
private:
	char m_szName[32];
	int m_iKor;
	int m_iMath;
	int m_iEng;
	int m_iSum ;
	float m_fAver ;
public:
	void SetszName(char*);
	char* GetszName();
	void SetiKor(int);
	int GetiKor();
	void SetiMath(int);
	int GetiMath();
	void SetiEng(int);
	int GetiEng();
	void SetiSum(int);
	int GetiSum();
	void SetfAver(int);
	float GetfAver();
public:
	void Sum();
	void Aver();
};