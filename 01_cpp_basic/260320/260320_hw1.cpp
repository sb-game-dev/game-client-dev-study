#include<iostream>

using namespace std;

int main()
{
	// 1. 숙제 : 평균 값을 기준으로 성적을 부여하는 프로그램을 만들어라
	// 
	// 90점 이상 100점 이하일 경우 "A학점"
	// 80점 이상 90점 미만일 경우 "B학점"
	// 70점 이상 80점 미만일 경우 "C학점"
	// 60점 이상 70점 미만일 경우 "D학점"
	// 나머지는 "F학점"
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