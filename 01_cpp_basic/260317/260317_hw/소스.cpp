#include<iostream>
using namespace std;

int main()
{
	float korean=0, math=0, english=0;
	cin >> korean >> english >> math;

	cout << "±¹¾î ¿µ¾î ¼öÇÐ ÃÑÁ¡ Æò±Õ"<< endl;
	
	cout << " " << korean 
		<< "    " << english
		<< "   " << math 
		<< "   " << (korean + math + english)
		<< "    " << (korean + math + english) / 3 << endl;
}