#include <iostream>

using namespace std;

int main()
{
#pragma region do while
	// do while : while문과 동일하게 무한 루프를 전제로 동작
	// - 무조건 한 번은 실행한 뒤, 반복을 결정

	//int iCount(3);

	// int iSum(0), iInput(0);
	// 
	// do
	// {
	// 	cin >> iInput;
	// 
	// 	//if(iInput % 2 == 0)
	// 	//	iSum += iInput;
	// 
	// 	if (iInput % 2 != 0)		// 홀수 일때
	// 	{
	// 		continue;				// continue : 반복문 안에서만 사용이 가능, skip과 같은 기능
	// 	}							// 현재 속한 반복문의 맨 끝으로 코드의 흐름을 강제 이동
	// 
	// 	iSum += iInput;
	// 
	// } while (-1 != iInput);
	// 	
	// cout << iSum << endl;

#pragma endregion

#pragma region for

	// for : 반복의 횟수를 정해놓고 사용하는 반복 문법

	//for (1. 초기화식; 2. 조건식; 3. 증감식)
	//{
	//	4. 코드 몸체
	//}

	/*for (int i = 0; i < 3; ++i)
	{
		cout << "hello world" << endl;
	}*/
	// 1번의 초기화식은 for문이 동작하는 최초에만 진입, 그 이후부터 코드의 흐름이 가지 않는다
	// 1 -> 2 -> 4 -> 3 -> 2 -> 4 -> 3

	// 다중 성격의 반복 조건을 만들면 가독성이 떨어짐
	//for (int i = 0, j = 0; i < 3 || j < 10; ++i, j +=3)
	//{
	//	cout << i << "\t" << j << endl;
	//}

	//int iSize(100);
	//
	//for (int i = 0; i < 3; ++i, ++iSize)
	//{
	//	cout << i << endl;
	//}
	//
	//cout << iSize << endl;

	//int i = 999;
	//
	//for (int i = 0; i < 3; ++i)
	//{
	//	cout << i << endl;	// naming의 지역 우선권(독점권)
	//}
	//
	//cout << i << endl;

#pragma endregion

#pragma region 2중 for문

	for (int i = 0; i < 2; ++i)
	{
		cout << 1 << endl;

		for (int j = 0; j < 3; ++j)
		{
			cout << 2 << endl;
		}

		cout << 3 << endl;
	}

	// 1 - 2 - 2 - 2 - 3 - 1 - 2 - 2 - 2 - 3

#pragma endregion

	return 0;
}

// 1. 가위 바위 보 게임 만들기

// - 난수 0 ~ 2까지 중 하나를 생성한다.(컴퓨터)
// - 1.가위 2.바위 3.보 4.종료(사용자)
// - 사용자가 낸 것과 컴퓨터가 낸 것을 비교 게임 결과를 매 라운드마다 출력
// - 총 5라운드를 실시하여 마지막 라운드가 끝나면(총 라운드), (승), (무), (패)출력!

/*
2. 구구단 2~9단까지의 출력을 2중 for문을 이용하여 만들어라

- (심화) 단과 곱을 입력받아 해당 단과 곱까지만 출력하기

5단 4곱

2 * 1 = 2
2 * 2 = 2
2 * 3 = 2
2 * 4 = 2

3 * 1 = 2
3 * 2 = 2
3 * 3 = 2
3 * 4 = 2

4 * 1 = 2
4 * 2 = 2
4 * 3 = 2
4 * 4 = 2

5 * 1 = 2
5 * 2 = 2
5 * 3 = 2
5 * 4 = 2
*/

/*
3. 2중 for문을 이용하여 다음과 같이 별을 출력하라

*
**
***
****
*****

*****
****
***
**
*

	*
   **
  ***
 ****
*****

*****
 ****
  ***
   **
	*

*/
