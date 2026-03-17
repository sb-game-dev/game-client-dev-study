#include<iostream>
using namespace std;

int main()
{
	int data = 0;
	cout << data;

	return 0;
}

// 자료형(데이터 형식): 정수,실수, 문자열, 논리 등과 같은 숫자의 상태 저장
// 
// 정수형 자료형: short, int, long, long long
// 실수형 자료형: float, double, long double
// 문자열 자료형: char, wchar_t
// 논리형 자료형: bool

// 선언: 변수나 상수의 이름과 자료형을 컴파일러에게 알려주는 것
// int data;
// 선언과 동시에 초기화: 변수나 상수의 이름과 자료형을 컴파일러에게 알려주고, 동시에 값을 할당하는 것
// 메모리를 할당 받는 최초의 시점만 동작하는 행위
// int data = 0;

// 상수: 변하지 않는 숫자(읽기 전용 데이터,쓰기 X)
// 리터럴: 원래 우리가 알고 있는 기호 체계 상태(10, 3.14, 'A', "Hello")
// 심볼릭: 우리가 알고 있는 기호 체계 상태를 키워드로 표현한 것(const, #define, enum)

// 변수	: 변하는 숫자(읽기/쓰기 모두 가능한 데이터)
// 표기법(관습)
// 헝가리안 표기법: 자료형을 접두사로 붙이는 표기법 ex) iData, fPi, cName, bIsTrue
// 파스칼 표기법: 단어의 첫 글자를 대문자로 하는 표기법 ex) PlayerHp
// 카멜 표기법: 단어와 단어사이의 글자를 대문자로 표기하는 방법	ex) playerHp
// 스네이크 표기법: 단어 사이를 언더바로 구분하는 표기법 ex) is_true
// 

// byte: 저장의 최소 단위
// bit: 연산의 최소 단위
// 1byte = 8bit
// 정수형 자료형: short(2byte), int(4byte), long(4byte), long long(8byte)

// signed: 양수와 음수 모두 저장 가능(- 표시 가능)
// unsigned: 양수만 저장 가능(- 표시 불가능)