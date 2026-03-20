#include<iostream>
#include<ctime>
using namespace std;

int main()
{
	// 4. 홀짝 게임
	// 
	// - 난수를 이용하여 맞춰야 할 숫자를 매번 생성한다.
	// - 난수 1 ~ 10까지 숫장 중 하나를 생성한다.
	// - 1.홀수 2.짝수 3.종료
	// - 총 5라운드를 실시하여 마지막 라운드가 끝나면, 몇 승, 몇 패 출력!
	int iRandNum = 0, iInput=0,iCnt = 5,iWin=0;
	srand(time(NULL));
	while (iCnt--)
	{
		iRandNum = rand()%10 + 1;
		cout << "생성된 숫자:" << iRandNum << endl;
		cout << "숫자를 입력해주세요: ";
		cin >> iInput;
		if (iInput % 2 == iRandNum % 2)
		{
			iWin++;
		}
	}
	cout << iWin << "승 " << 5 - iWin << "패" << endl;

	return 0;
}