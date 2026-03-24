
#include<iostream>
using namespace std;

int main()
{
	float korean = 0, math = 0, english = 0;
	cin >> korean >> english >> math;

	cout << "±¹¾î\t¿µ¾î\t¼öÇÐ\tÃÑÁ¡\tÆò±Õ" << endl;

	cout << korean
		<< "\t" << english
		<< "\t" << math
		<< "\t" << (korean + math + english)
		<< "\t" << (korean + math + english) / 3.f << endl;
}