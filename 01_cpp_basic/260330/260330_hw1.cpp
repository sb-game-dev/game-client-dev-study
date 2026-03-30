#include<iostream>
using namespace std;

int main()
{
	int iArr[5][5] = {};
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			iArr[i][j] = i * 5 + j + 1;
		}
	}

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			cout << iArr[i][j] << "\t";
		}
		cout << endl;
	}

}