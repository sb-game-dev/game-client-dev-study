#include <iostream>
using namespace std;
class CSortRule
{
public:
	virtual bool operator()(int dst, int src) = 0;
};

class CAsending :public CSortRule
{
public:
	bool operator()(int dst, int src) override {return dst < src;}
};

class CDesending :public CSortRule
{
public:
	bool operator()(int dst, int src) override {return dst > src;}
};

void BubbleSort(int pArr[], int iSize, CSortRule&& Funtor)
{
	for (int i = 0; i < iSize; i++)
	{
		for (int j = 0; j < iSize; j++)
		{
			if (Funtor(pArr[i],pArr[i+1]))
			{
				swap(pArr[i], pArr[i + 1]);
			}
		}
	}
}
int main()
{

}

// && -> 이중 레퍼런스
// 
// **연산자 오버로딩의 절대 규칙
// 기존 연산자의 기능과 전혀 다른 연산자로의 사용은 금지
//
//
// **함수객체
// 객체를 함수처럼 사용하는 문법
// 일반 함수 포인터 보다 빠름 람다로 대체 됨
// 
// **임시객체
// 
// **템플릿
// 기능은 결정되어있지만 자료형은 결정되지 않은 상태로 코드를 생성하는 틀
// 
// 함수 템플릿: 함수를 찍어내는 틀(함수가 아님 템플릿임)
// 클래스 템플릿: 클래스를 찍어내는 틀
// 
// 템플릿 특수화
// 
// data 영역을 사용하는 static 변수의 경우 같은 자료형으로 만들면 메모리 공간을 공유함
// 
// 클래스 템플릿의 부분 특수화
// 
// 클래스 멤버함수를 만들 때 몸체 구현할 때 inline으로 만듬 헤더파일만 만듬
// 
// string은 템플릿 특수화 된 컨테이너
// 
// 
// 
// 
// 
// 
// 
// 
//  