#include<iostream>
using namespace std;
// 자판기 -> 함수로 사용 -> 입력함수, 선택함수, 거스름돈 반환 함수 등등... 함수 최대한 많이
// 구구단 가로로 출력
void gugudan();

int main()
{
	gugudan();
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
			cout << endl;
		}
		cout << endl;
	}
}