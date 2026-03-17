#include<iostream>
using namespace std;

int main()
{
	float korean, math, english;
	cin >> korean >> math >> english;
	cout << "±¹¾î ¼öÇÐ ¿µ¾î ÃÑÁ¡ Æò±Õ"<< endl;
	
	cout << " " << korean << "   " << math << "   " << english << "  " << (korean + math + english);
	cout << fixed;
	cout.precision(2);
	cout<< "  " << (korean + math + english) / 3 << endl;
}