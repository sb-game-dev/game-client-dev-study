#include <iostream>
using namespace std;

int main()
{
    cout << "Hello World!\n";
}
// 
// 메모리계층 -> (code) // data(data,bss,readOnlyData) // heap // stack
// 메모리 계층을 넘나드는 것은 좋지 않음
// static,      정적,    컴파일 타임 , data에 저장
// dynamic,     동적,    런타임,       stack에 저장
//      
// 지역변수(중괄호 안에 있는 변수) -> stack에 저장, 함수 종료시 반환, 함수 내부에서 접근할 수 있는 정적변수<for문의 변수도?>
// 전역변수 -> data에 저장, 프로그램 종료시 반환,  외부에서 접근할 수 있는 정적변수
// 
// 전역변수 선언시 값 초기화를 하지 않으면 bss에서 0으로 초기화 후 data에 저장됨 
// 값 초기화 하면 초기화한 값으로 data에 저장됨
// 
// main()의 return 0 -> 함수에서 사용한 모든 변수 메모리 반환하겠다 라는 뜻.
// 
// <구분>              <메모리>          <접근 범위>
// 지역변수             stack           함수 내부
// static 지역변수      Data            함수 내부
// 전역변수             Data            모든 파일
// static 전역변수      Data            현재 파일만
// 