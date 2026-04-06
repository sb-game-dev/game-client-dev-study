#include "pch.h"
#define NUMBER 7

#if NUMBER > 7
void print() { cout << "7보다 크다" << endl; }

#elif NUMBER < 7
void print() { cout << "7보다 작다" << endl; }

#else
void print() { cout << "7이다" << endl; }

#endif


#ifdef _DEBUG
void CheckMode() { cout << "디버그 모드" << endl; }

#elif NDEBUG
void CheckMode() {cout << "릴리즈 모드" << endl;}

#else
void CheckMode() { cout << "코드 오류" << endl; }

#endif // _DEBUG

using namespace std;
int main()
{
	CheckMode();

	print();
	// 전처리기 문법
	// 
	// 매크로: 자주 사용하는 코드를 전처리기 시점에 실행파일에 삽입하는 문법. 코드 삽입 / 강제 치환
	// 전처리기 시점에 사용하는 문법이라 세미콜론 사용하지 X
	// 매크로 내부의 코드 오류를 컴파일러가 감지할 수 없음. 컴파일 시점이 아니라 전처리기 시점이라
	// 컴파일 시점에는 감지할 수 있음.
	// 
	// 상수 매크로: 자주 사용하는 리터럴 상태의 상수를 전처리기 시점에 삽입하는 문법
	// 
	// 
	// 함수 매크로: 짧은 코드를 자주 사용할 때 전처리기 시점에 삽입하는 문법
	// 코드를 단순 치환하는 문법 -> 자료형을 밝히거나 명시할 필요가 없이 모두 동작 가능
	// 여러 줄을 사용해야 할 경우 역슬래쉬(\)로 마무리 해야 함 마지막 줄은 제외함 
	// 
	// 

	// 조건부 컴파일: 조건에 따라 전처리기 시점에 컴파일 여부를 결정하는 문법 -> 메인함수에서 쓰는거야?
	// 
	// #if 조건			-> 조건이 참이면 컴파일
	// #elif 조건		-> 조건이 참이면 컴파일
	// #else			-> 위 조건이 모두 거짓이면 컴파일
	// #endif			-> 조건부 컴파일 종료
	// 
	// 
	// 
	// #ifdef
	// 
	// 
	// #ifndef
	// pch_h 사용할 때 precompileheader
	// 

	// 입출력: 콘솔, 파일, 소켓
	// 
	// 
	// 텍스트 모드 입출력 함수 : 
	// 바이너리 모드 입출력 함수 : 
	// 
	// 텍스트 모드 입출력 함수
	// 
}