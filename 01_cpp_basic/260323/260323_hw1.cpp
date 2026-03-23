#include<iostream>
#include<ctime>
using namespace std;
int main()
{
	// 1. 가위 바위 보 게임 만들기

// - 난수 0 ~ 2까지 중 하나를 생성한다.(컴퓨터)
// - 1.가위 2.바위 3.보 4.종료(사용자)
// - 사용자가 낸 것과 컴퓨터가 낸 것을 비교 게임 결과를 매 라운드마다 출력
// - 총 5라운드를 실시하여 마지막 라운드가 끝나면(총 라운드), (승), (무), (패)출력!
	int iRound = 0, iWin = 0, iDraw = 0, iLose = 0, iInput = 0,iCom=0;
	srand(unsigned(time(NULL)));
	while (iRound<5)
	{
		iCom = rand() % 3;
		cout << "컴퓨터 숫자: " << iCom<<endl;
		cout << "1.가위 2.바위 3.보 4.종료(사용자):";
		cin >> iInput;
		if (iInput == 4)
		{
			break;
		}
		if (iCom == 0 && iInput == 2 || iCom == 1 && iInput == 3 || iCom == 2 && iInput==1) 
		{
			iWin++;
		}
		else if (iCom + 1 == iInput)
		{
			iDraw++;
		}
		else
		{
			iLose++;
		}
		iRound++;
	}
	cout << "총 라운드: " << iRound << " 승리: " << iWin << " 무승부: " << iDraw << " 패배: " << iLose << endl;
}