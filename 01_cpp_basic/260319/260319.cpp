#include <iostream>
#include <bitset>

using namespace std;

int main()
{
#pragma region 연산자
	// 기본 연산자
	// +, -, *, /, %(나머지 연산자)

	// cout << (10 / 3) << endl;
	// cout << (10 % 3) << endl;

	//(tmi) 0 나누기(zero devide)

	// NAN(Not A Number) : 숫자가 아닌 이상한 결과 값이 나왔을 때 디버그 단계에서 표현되는 용어

	//cout << (10 / 0) << endl;
	//cout << (10 % 0) << endl;

	//int iDst(10), iSrc(0);
	//
	//cout << (iDst / iSrc) << endl;
	//cout << (iDst % iSrc) << endl;

	// sizeof 연산자 : 자료형의 크기를 계산해주는 연산자

	//cout << sizeof(char) << endl;			//	1
	//cout << sizeof(bool) << endl;			//  1
	//	
	//cout << sizeof(short) << endl;		// 2
	//cout << sizeof(int) << endl;			// 4
	//	
	//cout << sizeof(long long) << endl;	// 8
	//cout << sizeof(double) << endl;		// 8

	// char cDst = 'A', cSrc = 'B';
	// cout << sizeof(cDst + cSrc) << endl;

	// 대입 연산자(=) : '같다'라는 의미가 아니라 값을 대입하는 용도로 사용
	// - '할당 연산자'라고도 불린다.

	// 1. 좌항과 우항의 자료형이 일치해야 한다.
	// 2. 반드시 오른쪽에서 왼쪽으로만 대입을 수행한다.

	// int		iData = 3.14f;
	// cout << iData << endl;

	//int iA(10), iB(20), iC(30);
	//
	//iA = iC;
	//iB = iA;
	//
	//iA = iB = iC = 200;
	//
	//cout << iA << " " << iB << " " << iC << endl;

	// (tmi) L - Value 와 R - Value;

	//int iTest = 100;		// R - Value : 연산자를 기준으로 오른쪽에만 위치할 수 있는 데이터 형식
							// - 리터럴 상수들이 R-Value에 해당
	// 100 = 200;

	//int	iSour = iTest;		// L - Value : 왼쪽, 오른쪽 모두 위치 가능한 데이터 형식

	//cout << iSour << endl;

	// const int iConst = 100;
	// int iTest = iConst;
	// cout << iTest << endl;

	// const int iConst = 100;
	// //&100;
	// &iConst;

	// 관계 연산자 : 두 숫자를 대소 비교하여 참 또는 거짓을 반환하는 연산자
	// >, <, >=, <=, ==(같다), !=(같지 않다)

	// int iDst(10), iSrc(20);
	// 
	// cout << (iDst < iSrc) << endl;		// 1	
	// cout << (iDst > iSrc) << endl;		// 0
	// cout << (iDst <= iSrc) << endl;		// 1
	// cout << (iDst >= iSrc) << endl;		// 0
	// cout << (iDst == iSrc) << endl;		// 0
	// cout << (iDst != iSrc) << endl;		// 1

	// 논리 연산자 : 두 논리의 상태를 보고 참 또는 거짓을 반환하는 연산자
	// &&(and), ||(or), !(not)

	// && : 비교하는 두 논리 모두 참인 경우에만 참을 반환

	// cout << (true  && true) << endl;
	// cout << (false && true) << endl;
	// cout << (true	&& false) << endl;
	// cout << (false && false) << endl;

	// || : 비교하는 두 논리 중 하나라도 참인 경우 참을 반환

	// cout << (true  || true) << endl;
	// cout << (false || true) << endl;
	// cout << (true  || false) << endl;
	// cout << (false || false) << endl;

	// a && b && c && d
	// a || b || c || d

	// ! : 참을 거짓으로 거짓을 참으로 변경하는 연산자

	// bool	bStart = true;
	// cout << bStart << endl;
	// bStart = !bStart;
	// cout << bStart << endl;

#pragma endregion

#pragma region 비트 단위 연산자

// 비트 단위 연산자 : 2진수 형태에서 연산을 수행시켜주는 연산자, 정수만 사용 가능
// &(and), |(or), ~(not), ^(xor) : 비교하는 두 비트의 값이 서로 다를 경우 참을 반환

// int		iDst(10), iSrc(13);
// 
// cout << bitset<8>(iDst) << endl;
// cout << "----------~-----------" << endl;
// cout << bitset<8>(~iDst) << endl;
// cout << (~iDst) << endl;

//cout << bitset<8>(iSrc) << endl;

//cout << "----------^-----------" << endl;
//cout << bitset<8>(iDst ^ iSrc) << endl;
//cout << (iDst ^ iSrc) << endl;

//cout << "----------|-----------" << endl;
//cout << bitset<8>(iDst | iSrc) << endl;
//cout << (iDst | iSrc) << endl;

//cout << "----------&-----------" << endl;
//cout << bitset<8>(iDst & iSrc) << endl;
//cout << (iDst & iSrc) << endl;

// (tmi) 2의 보수

#pragma endregion

#pragma region 증감 연산자

// 증감 연산자 : 본래 값에서 하나 더하거나 하나 빼는 연산자
// ++, --

	//int		iScore = 10;

	//++(++iScore);		// 전위 연산 : 선 연산, 후 대입
	//(iScore++)++;		// 후위 연산 : 선 대입, 후 연산

	//cout << (++iScore) << endl;
	//cout << (iScore++) << endl;
	//cout << (iScore) << endl;

#pragma endregion

#pragma region 연산자 축약형

// 연산자 축약형 : 자기 자신의 데이터의 값을 변경하려는 코드를 줄여서 표기하는 방법
// +=, -=, *=, /=, %=, <<=, >>=

	//int		iNumber = 50;

	// iNumber = iNumber + 10;

	//iNumber += 10;

	//cout << iNumber << endl;



#pragma endregion

#pragma region 삼항 연산자

// 삼항 연산자 : 연산의 항목이 세 개이며, 짧막한 코드로 분기를 하고자 할 때 사용
// - 주로 최대, 최소 값을 표현하는 용도로 사용
// - 긴 코드를 작성하기 까다롭고, 가독성이 떨어진다.

// 1항(조건식) ? 2항(조건이 참인 경우) : 3항(조건이 거짓인 경우)

// int iDst(10), iSrc(20);
// 
// int iResult = (iDst < iSrc) ? iDst : iSrc;
// 
// cout << "최소 값 : " << iResult << endl;

#pragma endregion

	return 0;
}

// LEFT			0001
// RIGHT		0010
// UP			0100
// DOWN			1000
// 
// LEFT | UP   ->  0101
// 0101 & LEFT ->  0001
// LEFT ^ LEFT ->  0000

