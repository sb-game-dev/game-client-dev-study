#include<iostream>
using namespace std;
void ex1()
{
	for (int i = 1; i <= 5; i++)
	{
		for (int j = 1; j <= i; j++)
		{
			cout << "*";
		}
		cout << endl;
	}
}
void ex2()
{
	for (int i = 1; i <= 5; i++)
	{
		for (int j = 1; j <= 6-i; j++)
		{
			cout << "*";
		}
		cout << endl;
	}
}
void ex3()
{
	for (int i = 1; i <=5; i++)
	{
		for (int j = 1; j <= 5 - i; j++)
		{
			cout << " ";
		}
		for (int j = 1; j <= i; j++)
		{
			cout << "*";
		}
		cout << endl;
	}
}
void ex4()
{
	for (int i = 1; i <= 5; i++)
	{
		for (int j = 1; j <i; j++)
		{
			cout << " ";
		}
		for (int j = 0; j <=5- i; j++)
		{
			cout << "*";
		}
		cout << endl;
	}
}
int main()
{

//3. 2중 for문을 이용하여 다음과 같이 별을 출력하라

//*
//**
//***
//****
//*****
	ex1();

//*****
//****
//***
//**
//*
//
	ex2();

//	  *
//   **
//  ***
// ****
//*****
//
	ex3();

//*****
// ****
//  ***
//   **
//	  *
	ex4();
}