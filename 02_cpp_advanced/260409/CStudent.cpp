#include "CStudent.h"
#include<iostream>
using namespace std;

void CStudent::SetszName(char* nameInput) { strcpy_s(m_szName,sizeof(nameInput),nameInput); }
char* CStudent::GetszName() { return m_szName; }

void CStudent::SetiKor(int iInput) { m_iKor = iInput; }
int CStudent::GetiKor() { return m_iKor; }

void CStudent::SetiMath(int iInput) { m_iMath = iInput; }
int CStudent::GetiMath() { return m_iMath; }

void CStudent::SetiEng(int iInput) { m_iEng = iInput; }
int CStudent::GetiEng() { return m_iEng; }

void CStudent::SetiSum(int iInput) { m_iSum = iInput; }
int CStudent::GetiSum() { return m_iSum; }

void CStudent::SetfAver(int iInput) { m_fAver = iInput; }
float CStudent::GetfAver() { return m_fAver; }

void CStudent::Sum() { m_iSum = m_iKor + m_iMath + m_iEng; }
void CStudent::Aver() {	m_fAver = float(m_iSum) / 3.0;}


