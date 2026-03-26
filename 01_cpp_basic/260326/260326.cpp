#include <iostream>
using namespace std;
void swap(int* _iDst, int* _Src);
int main()
{
    // 함수 오버로딩: 함수 이름이 같을 때 어떤 함수 호출할 지 컴파일 타임(컴파일 하는 시점)에 결정
    // 1. 매개변수의 형식(자료형)에 따라 결정
    // 2. 매개변수의 개수에 따라 결정
    // 3. 반환 타입과는 무관
    
    // default 매개변수: 매개변수에 기본 값을 삽입하는 문법 (선언할 때만)
    // -> 선언부에 초기화 식을 삽입(함수 몸체에는 삽입하지 않음, 선언과 동시에 초기화 하는 문법)
    // -> 반드시 뒤쪽부터 순차적으로 삽입 가능
    // -> 오버로딩과 같이 사용하는 경우 모호함이 발생할 수 있음.
    
    // 재귀함수: 스텍 프레임(?)
    // - 매번 스택 프레임을 생성하기 때문에 메모리 효율이 좋지 못함.
    // - 반복문으로 변경할 수 있다면 바꾸는 것이 좋음.
    // - 재귀의 조건은 감소하는 방향으로 하는 것이 관습임. (병합 정렬)
    // - 꼬리 재귀함수는 스택 프레임을 재생성하지 않음 (ex. return n*Fact(n-1))
    //

    // 포인터: 주소값을 저장하는 용도의 변수
    // int iData = 0; -> 4byte 할당 받음(0x1,0x2,0x3,0x4) -> 대표주소(0x1) 하나만 알아도 전체를 사용가능 -> 주소를 통한 참조
    // int* p = &iData; -> 주소값 저장하는 변수 p
    // cout<< p; or cout<<&iData -> 0x1 같은 주소가 출력
    // cout<< *p; or cout<<iData -> 0x1 에 저장된 값 출력(간접 참조, 직접 참조는 *(0x1) = 10과 같은 형태) 
    // *(&iData) == iData  *과&가 만나면 상쇄
    // 
    // int* p가 8byte인 이유 64bit 기반의 프로그램에서는 8byte, 32bit 는 4byte
    // 4byte의 경우 0xffff ffff까지 표현 가능(f-> 15 -> 1111 -> 4bit)
    // 8byte의 경우 0xffff ffff ffff ffff까지 가능
    //
    int iA = 0;
    cout << &iA<<endl;
    cout << *&iA<<endl;
    
    int* p = &iA; // 간접 참조
    *p = 30;
    cout << p << endl;
    cout << iA << endl;
    //int iDst = 30, iSrc = 20;
    //swap(&iDst, &iSrc);
    //cout << iDst << " " << iSrc << endl;
}

void swap(int* pDst, int* pSrc)
{
    int pTemp = *pDst;
    *pDst = *pSrc;
    *pSrc = pTemp;
}


// 모든 과제를 포인터를 사용하는 함수로 바꿔보기(매개변수, 반환값을 포인터로)