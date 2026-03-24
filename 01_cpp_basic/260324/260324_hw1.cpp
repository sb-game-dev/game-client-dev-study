#include<iostream>
using namespace std;

// 구구단 가로로 출력
void gugudan();

int main()
{
	gugudan();
	return 0;
}

void gugudan()
{
	for (int i = 2; i < 10; i += 3)
	{
		for (int j = 1; j < 10; j++)
		{
			cout << i << " x " << j << " = " << i * j << "\t";
			cout << i + 1 << " x " << j << " = " << (i + 1) * j << "\t";
			if (i + 2 < 9)cout << i + 2 << " x " << j << " = " << (i + 2) * j;
			cout<<endl;
		}
		cout << endl;
	}
}