#include<iostream>
using namespace std;
void ex1()
{
	for (int i = 2; i < 10; i++)
	{
		cout << "<" << i << "단>" << endl;
		for (int j = 1; j < 10; j++)
		{
			cout << i << " x " << j << " = " << i * j << endl;
		}
	}
}
void ex2()
{
	int iDan = 2, iGob = 1;
	cin >> iDan >> iGob;
	for (int i = 2; i <= iDan + 1; i++)
	{
		cout << "------------------------" << endl;
		for (int j = 1; j <= iGob; j++)
		{
			cout << i << " x " << j << " = " << i * j << endl;
		}
	}
}
int main()
{
	//2. 구구단 2~9단까지의 출력을 2중 for문을 이용하여 만들어라 
	// ex1();
	//	- (심화)단과 곱을 입력받아 해당 단과 곱까지만 출력하기
	// ex2();
	
}