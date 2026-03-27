#include <iostream>
using namespace std;

int main()
{
	
}

// const와 포인터 
// const int* p = &iData -> 읽기 전용 포인터(참조하는 대상의 변수값을 변경할 수 없음, 주소 변경은 가능, 문자열 다룰 때)
// int* const p = &iData -> 상수 포인터(참조하는 주소 변경이 불가능함, 값 변경은 가능, 배열이 여기에 해당)
// const int* const p = &iData -> 읽기 전용 상수 포인터

// 2중 포인터
// 
// int iData = 0;
// int*p = &iData;
// int**pp = &p;
// 2중 포인터도 8byte
// 
// 포인터 연산
// int *p = iData;
// ++p
// 
// 포인터 연산 후 참조하는 대상의 값을 변경하는 경우 변경이 되긴 하지만 오류가 발생함
// 변수를 만들 때 메모리는 메모리 공간을 연속적으로 할당하지않음. 비어있는 공간을 만듬
// 
// 
// 