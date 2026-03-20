#include <iostream>
#include <ctime>

using namespace std;

// typedef : 기존의 존재하던 자료형의 이름을 사용자의 편의를 위해 변경하거나 추가하는 문법

// typedef short			_int;
// typedef int				BOOL;
// typedef unsigned long	DWORD;

int main()
{
	// 반복문 : 동일한 코드를 반복해야 수행하는 문법
	//	while, do while, for

#pragma region while

	// while (조건식)
	// {
	// 	코드 몸체
	// }

	// while (0)
	// {
	// 	cout << "hello world" << endl;
	// 	break;
	// }

	//int iCount(3);

	//while (--iCount) cout << "hello world" << endl;

	//while (true)
	//{
	//	cout << "hello world" << endl;	
	//
	//	--iCount;
	//
	//	if (0 == iCount)
	//	{
	//		break;		// 단일 코드 : 한 줄짜리 코드, 중괄호를 생략하여 표기 가능
	//	}
	//}

	// 2 * 1 = 2
	// 2 * 2 = 4
	// 2 * 3 = 6

	// int i = 1;
	// 
	// while (i < 10)
	// {
	// 	 cout << 2 << " * " << i << " = " << i * 2 << endl;
	// 	 ++i;
	// }		

	//int iInput(0);
	//
	//while (true)
	//{
	//	system("cls");
	//
	//	cout << "숫자 입력 : ";
	//	cin >> iInput;
	//
	//	cout << iInput << endl;
	//
	//	system("pause");
	//}

#pragma endregion

#pragma region 난수 생성

	// 난수 : 랜덤한 값
	// 난수표 : 정수 값들을 정리해놓은 테이블 파일

	// srand(값) : 넣어준 값에 해당하는 난수 테이블로 변경
	// time() : 현재 시간을 초 단위로 변경하여 불러오는 함수

	//time_t	Temp;
	//
	//time(&Temp);
	//
	//cout << Temp << endl;		//	1773983333
								//  1773983346
	// srand(unsigned(time(NULL)));
	// 
	// int iDst = rand();	 // 0 ~ 32767 사이 값중 무작위로 하나를 뽑아줌
	// int iSrc = rand();
	// int iTmp = rand();
	// 
	// cout << iDst << endl;
	// cout << iSrc << endl;
	// cout << iTmp << endl;

#pragma endregion

	

	// 분기문 : 어떤 조건에 의해 실행할 코드와 실행하지 않을 코드로 구분하는 문법
	// if, switch, goto

#pragma region goto
	// goto : 선언한 레이블을 기준으로 이전, 이후 코드로 분기하는 문법

	// goto Jump;
	// 
	// int		iTemp = 100;
	// cout << 1 << endl;
	// 
	// Jump :
	// 
	// cout << 2 << endl;
	// cout << iTemp << endl;
#pragma endregion

#pragma region if

	// if 문 : 조건문이라고 불리우는 문법, 조건이 참인 경우에만 실행

	// if (조건식)
	// {
	// 	코드 몸체(body)
	// }

	// if와 부속문 사이에 다른 코드가 삽입될 수 있다.
	// if와 부속문 중 가장 먼저 참인 코드만 실행된다.

	//if (1)
	//{
	//	//int iTest = 100;
	//	cout << 1 << endl;
	//}
	////int iTest = 100;		// if와 else 사이에는 다른 코드가 위치 할 수 없다.
	//else if (1)
	//{
	//	cout << 2 << endl;
	//}
	//
	//else		// if가 참이면 거짓, if가 거짓이면 참이 되는 문법
	//{
	//	//cout << iTest << endl;
	//	cout << 3 << endl;
	//}

	 // int iA(20), iB(5);
	 // 
	 // if ((iA < iB) && (iB = 999))
	 // {
	 // 	cout << iB << endl;
	 // }

	// 1. 컴파일 에러 : 동훈, 예진, 희현, 신영
	// 2. 5 : 광덕, 승환, 시은
	// 3. 999 : 성범 (승자)
	// 4. 쓰레기 값 : 현수, 준형, 찬욱


	// if (a && b && c && d)
	// {
	// 
	// }

	//if ()
	//{
	//	if ()
	//	{
	//		cout << "hello world" << endl;
	//	}
	//
	//	cout << "hello world" << endl;
	//}


#pragma endregion

#pragma region switch

	// switch : 상수 (조건) 분기문, 조건식에 무조건 정수만 올 수 있음.

	// switch (조건식(정수))
	// {
	// case 상수 :
	// 
	// case 상수 :
	// 
	// case 상수 :
	// }

	//int iInput(0);
	//const int iOne(1), iTwo(2), iThree(3);

	//cout << "1. 콜라 2. 사이다 3. 환타 : ";
	//cin >> iInput;
	//
	//switch (iInput)
	//{
	//case 1:
	//	cout << "콜라" << endl;
	//	break;					// 현재 코드의 흐름을 멈추고 구문에서 탈출
	//
	//case 2:
	//	cout << "사이다" << endl;
	//	break;
	//
	//case 3:
	//	cout << "환타" << endl;
	//	break;
	//
	//default:			// case 에 해당하지 않는 값이 들어오는 경우 실행
	//	cout << "잘못 입력하셨습니다" << endl;
	//	break;
	//}

	//switch (iInput)
	//{
	//case iOne:
	//	cout << "콜라" << endl;
	//	break;					// 현재 코드의 흐름을 멈추고 구문에서 탈출
	//
	//case iTwo:
	//	cout << "사이다" << endl;
	//	break;
	//
	//case iThree:
	//	cout << "환타" << endl;
	//	break;
	//}

// int iInput(0);
// 
// cout << "1. 콜라 2. 사이다 3. 환타 : ";
// cin >> iInput;
// 
// switch (iInput)
// {
// case 'A':
// 	cout << "콜라" << endl;
// 	break;					// 현재 코드의 흐름을 멈추고 구문에서 탈출
// 
// case 'B':
// 	cout << "사이다" << endl;
// 	break;
// 
// case 'C':
// 	cout << "환타" << endl;
// 	break;
// }

	//if (1)
	//{
	//	cout << " 1 " << endl;
	//	
	//	break;		// if문 안에서 단독적으로는 사용 할 수 없고, if문을 감싸는 다른 구문의 탈출 용도로 사용
	//
	//	cout << " 2 " << endl;
	//}

	int iInput(0);

	cin >> iInput;

	switch (iInput)
	{
		// int iResult = 0; // switch 문 안에서 변수 생성 불가

	case 1:
	{
		int iResult = 0;	// case 구문 안에서 변수 생성
		iResult = 100;
		cout << iResult << endl;
	}
	break;

	case 2:
		//iResult = 200;
		//cout << iResult << endl;
		break;

	case 3:
		//iResult = 300;
		//cout << iResult << endl;
		break;
	}

#pragma endregion

	return 0;
}

// 1. 숙제 : 평균 값을 기준으로 성적을 부여하는 프로그램을 만들어라
// 
// 90점 이상 100점 이하일 경우 "A학점"
// 80점 이상 90점 미만일 경우 "B학점"
// 70점 이상 80점 미만일 경우 "C학점"
// 60점 이상 70점 미만일 경우 "D학점"
// 나머지는 "F학점"

// 2. while문을 이용하여 구구단 2 ~ 9단까지 출력하기

// 3. 자판기 구현하기
// 
// - 소지금을 입력 받는다.
// - 항상 잔액을 출력한다.
// - 1. 콜라(100원), 2. 사이다(200원), 3. 환타(300원), 4. 반환
// 
// - 해당 목록 구매 시 “XX 구매 완료” 출력 후, 보유 잔액이 바뀐다.
// - 단, 소지금이 부족할 경우 “소지금이 부족합니다.”가 출력된다.
// - 4번을 고르면 “거스름 돈은(소지금) 입니다.” 출력 후 프로그램 종료

// 4. 홀짝 게임
// 
// - 난수를 이용하여 맞춰야 할 숫자를 매번 생성한다.
// - 난수 1 ~ 10까지 숫장 중 하나를 생성한다.
// - 1.홀수 2.짝수 3.종료
// - 총 5라운드를 실시하여 마지막 라운드가 끝나면, 몇 승, 몇 패 출력!
