#include<iostream>

using namespace std;

int main()
{
	int iScore = 0;
	cin >> iScore;
	if (iScore <= 100)
	{
		if (iScore >= 90) cout << "A학점" << endl;
		else if (iScore >= 80) cout << "B학점" << endl;
		else if (iScore >= 70) cout << "C학점" << endl;
		else if (iScore >= 60) cout << "D학점" << endl;
		else cout << "F학점" << endl;
	}
	else cout << "F학점" << endl;
}