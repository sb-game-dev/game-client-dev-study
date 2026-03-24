#include <iostream>

using namespace std;


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

// 함수 구성 요소

// 1.반환 타입 2. 함수 이름 (3. 매개 변수)
// {
// 		4. 함수 몸체
// }

void	Print(void);		// 함수 선언부
void	Draw(int iData);	// iData : 매개 변수, 인자값, parameter
int		GetNumber(void);
int		Add(int iDst, int iSrc);

int main()
{
	// 함수 : 입력되는 데이터를 가공하여 내보내는 구조, '기능', 동사형으로 이름을 지을 것
	// - 코드의 재사용성(한 번 만들어 놓은 코드를 계속 다시 사용하겠다)
	// - 함수 설계 -> 컴파일 -> 바이너리화 -> 메모리 저장 -> 필요할 때마다 메모리로 부터 불러서 사용(함수 호출하다)

	//Print();	// () : 함수 호출 연산자

	// Draw(10);

	//int iTest(20);	// 지역 변수
	//
	//Draw(iTest);	// 25 , call by value : 값 복사에 의한 호출
	//cout << iTest << endl;

	//cout << GetNumber() << endl;

	//int iResult = GetNumber();
	//cout << iResult << endl;

	// Draw(GetNumber());

	cout << Add(100, GetNumber()) << endl;


	return 0;
}

// 함수 몸체, 구현부, 정의부

void	Print(void)				// 함수를 정의하다
{
	cout << "hello world" << endl;
}
void	Draw(int iData)
{
	iData += 5;			// 쓰기

	cout << iData << endl;	// 읽기
}
int		GetNumber(void)
{
	// return 500;

	int iStack = 600;		// 지역 변수

	return iStack;
}

int Add(int iDst, int iSrc)
{
	return iDst + iSrc;
}
