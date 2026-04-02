#include <iostream>
using namespace std;
struct tagSt
{
	string s;
	int iKor;
	float fAver;
};
int main()
{
	// 유니코드 서식문자 L, 유니코드가 뭐야?
	// 
	char szName[32] = "school";
	char szTemp[32] = "";
	string s = "world";
	cout << szTemp<<endl;
	strcpy_s(szTemp,sizeof(szTemp), s.c_str());

	cout << szTemp << endl;

	// C언어 사용자 정의 자료형
	// 구조체 : struct
	// 공용체 : union 거의 안씀, 메모리가 풍족한 시대라서
	// 열거체 : enum 상수를 여러개 만드는 문법
	// 
	// c++에서는 클래스가 추가됨
	// 
	// <구조체> 
	// 구조체도 포인터로 사용할 수 있음
	// 
	// c -> 멤버변수 가능, 멤버 함수 x
	// c++ -> 멤버 변수 가능, 멤버 함수 가능
	// 
	// tagSt st ={};
	// tagSt* pSt = &st;
	// 
	// cout<< *pSt.iKor <<endl;
	// 
	// cout<< *pSt->iKor <<endl; // -> : 포인터로 멤버에 접근하고자 할 때 사용 이 연산자를 많이 사용함
	// 
	// c언어와 c++에서의 구조체 차이
	// 
	// 구조체도 상속 가능 부모 자식둘 다 가능하고 class와도 상속 가능
	// 데이터 집합체로도 사용 가능하고 객체로도 사용 가능함.
	// 
	// 구조체 메모리 할당 정책
	// 멤버변수 중 가장 큰 자료형의 크기만큼 메모리 블럭을 할당함.
	// 작은 크기의 자료형부터 멤버 변수를 선언해야 한다. 배열이 있더라도 배열의 크기가 아니라 자료형으로 계산
	// 멤버 변수가 없다면 디폴트 값으로 1byte로 계산
	// 멤버 함수는 데이터로 취급하지 않고 오로지 멤버 변수로만 계산함. 클래스도 동일함.
	// 가장 큰 자료형의 크기는 기본 자료형으로만 계산
	// sizeof 연산자를 잘 사용해야 함.
	// 
	// 
	// <공용체>
	// 다른 자료형을 사용한다면 정상적으로 저장이 안됨. 거의 사용 안됨 c#에는 없음.
	// 
}
