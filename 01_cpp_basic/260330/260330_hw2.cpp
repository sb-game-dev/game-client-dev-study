#include<iostream>
using namespace std;

int main()
{
	int iArr[3][3] = {};
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			iArr[i][j] = i * 3 + j + 1;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << iArr[i][j] << "\t";
		}
		cout << endl;
	}
	cout << "=============================" << endl;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 2; j > -1; j--)
		{
			cout << iArr[j][i] << "\t";
		}
		cout << endl;
	}

	cout << "=============================" << endl;
	for (int i = 2; i > -1; i--)
	{
		for (int j = 2; j > -1; j--)
		{
			cout << iArr[i][j] << "\t";
		}
		cout << endl;
	}

	cout << "=============================" << endl;
	for (int i = 2; i > -1; i--)
	{
		for (int j = 0; j <3; j++)
		{
			cout << iArr[j][i] << "\t";
		}
		cout << endl;
	}

	cout << "=============================" << endl;

}