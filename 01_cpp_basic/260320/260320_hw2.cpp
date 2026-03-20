#include<iostream>
using namespace std;

int main()
{
	// 2. while문을 이용하여 구구단 2 ~ 9단까지 출력하기
	int i = 2;
	while (i < 10)
	{
		int j = 1;
		cout << "<" << i << "단>" << endl;
		while (j < 10)
		{
			cout << i << " x " << j << " = " << i * j << endl;
			j++;
		}
		i++;
	}
}