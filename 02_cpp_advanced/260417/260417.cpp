#include "pch.h"

class CObj
{
public:
    CObj() {
        m_iA = 100;
    }
    ~CObj() {
    }
public:
    int m_iA;
};

//#include "Obj.h" // 상속 관계에서 부모 클래스의 헤더를 자식 클래스에서는 반드시 포함해야 한다.

class CPlayer:public CObj
{
public:
    CPlayer() {
        m_iA = 200;
        //CObj::m_iA = 200;
    }
    ~CPlayer() {
    }
};
class CMonster :public CObj
{
public:
    CMonster() {
        m_iA = 300;
    }
    ~CMonster() {
    }
};
int main()
{
    //CObj Obj;
    //CPlayer Player;
    //CMonster Monster;
    //
    //
    //cout << Obj.m_iA << endl;
    //cout << Player.m_iA << endl;
    //cout << Monster.m_iA << endl;
    //
    //cout << Obj.m_iA << endl;

    //
    // 상속의 목적 -> 공통화
    // 
    // 
    // 자식 객체 생성 과정
    // 1. 메모리 할당 2. 부모 생성자 호출 3. 자식 생성자 호출
    // 상속이 많을 경우(부모가 많을 경우) 모든 부모의 생성자를 호출함
    // 부모의 메모리만큼 똑같이 자식도 메모리가 생성됨(용량이 커짐)
    // 
    // 자식 객체 소멸 과정
    // 1. 자식 소멸자 2. 부모 소멸자 3. 메모리 반환
    // 
    // protected : 자식에게만 public 외부에서는 private
    // 
    // 부모 private -> 자식은 쓰지 못하지만 용량은 그대로 가져감
    // 
    // 부모가 상속한다고 해서 부모의 변수에 접근할 수 있는건 아니다.
    // 엄마 -> 멤버 변수: 자동차
    // 아들 (엄마 상속)
    // 엄마 자동차 따로 있고 아들도 자동차 따로 있음
    // 
    // 만약 아들도 멤버 변수 이름을 자동차로 만들었을 때는 별다른 키워드 없을 때는 아들의 것으로 사용
    // 이때 엄마한테 상속받은 자동차로 사용하고싶다면 네임스페이스로 설정해야 함(엄마::자동차)
    // 
    //

    // 업캐스팅: 자료형 통일 -> 상속의 이유
    // 

    // 접근하는 수단이 부모라면 자식 객체(heap메모리)의 멤버함수를 사용 못함

    // 정적 바인딩
    // 
    // 동적 바인딩+다형성(월요일)
    // 
    // class<- Player(자식)
    //      <- Monster(자식)
    // 
    // 상속을 잘 썼다면 컴파일 에러남
    // 
    // 상점 구현 초중고급 검, 초중고급 옷 구매
    // 
    // 

    return 0;
}
// 
// class 상속
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 