#include<iostream>
using namespace std;

int main()
{
	short sData = 0;
	int data = 0;
	cout << data << endl;
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


// 실수형 자료형 : float(4byte), double(8byte), long double(16byte)
// 소수점 이하 몇 자리까지 저장할 수 있는가(정밀도차이/연산량이 많음)
// float: 소수점 이하 6자리까지 저장 가능
// double: 소수점 이하 15자리까지 저장 가능
// 
// float fPi = 3.14f; // f 접미사 붙여야 float형으로 인식
// 
// 고정 소수점 방식: 소수점의 위치가 고정되어 있는 방식
// 
// 부동 소수점 방식: 소수점의 위치가 가변적인 방식, 오차가 있음
// 3.14 -> 314 * 10^-2
//  
// ieee floating point: 부동 소수점 방식의 표준 규격
// 
// 
// 문자열 자료형: char(1byte), wchar_t(2byte)
// sbcs -> MBCS -> wbcs
//
//
// 논리형 자료형 : bool(1byte)
// 0(false)과 1(true)로 표현, 논리 연산자와 함께 사용
// 
// 
// 숙제1: 국어 영어 수학 점수를 입력받고 총점과 평균을 구하여 출력하라
// 출력 형식: 국어 영어 수학 총점 평균
// 출력 형식:  ?     ?    ?    ?   ?

// 숙제 2: 숫자 20 ~ 30의 숫자를 2진수로 바꾸고 다시 10진수로 바꾸는 연산을 종이에 적어오세요.
