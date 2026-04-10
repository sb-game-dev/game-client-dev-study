# C++ 심화 개념

### 1일차 (260409) c++개론, class
<details>
  <summary>c++개론</summary>

- 절차 지향 프로그래밍: ~하다(동사) 중심의 언어적 구성  
- 객체 지향 프로그래밍: 주어 중심의 언어적 구성, 프로그래밍을 구성하는 각 객체간의 소통  
- 객체 지향은 속도가 느리지만 유지보수가 편리함, 절차 지향 프로그래밍을 속도가 빠르지만 유지보수가 어려움.  
  
- 객체: 실세계를 구성하는 하나의 실체  
- 객체지향: 실세계를 그대로 프로그래밍에 구현  

- 객체: 인스턴스 + 클래스

- 추상화: 공통된 요소로 추출하는 과정 / 작업
- C++은 추상화!  
</details>

<details>
  <summary>클래스</summary>

> 클래스 = 데이터(변수, 상수) + 기능(함수)

> 클래스의 속성
1. 은닉화
2. 캡슐화
3. 상속성
4. 다형성

- 접근제어 지시자 (private, public): 변수 또는 함수의 접근을 제어하기 위해 만든 키워드.
- 멤버 변수는 private에 선언해야하고 private에 선언하는 경우 클래스 외부에서 접근할 수 없음
- 멤버 변수를 클래스 밖에서 접근하려면 access method를 통해 접근할 수 있다.
- access method를 제외한 멤버함수는 헤더파일에서 몸체를 만들 수 없으므로 cpp파일에서 만들 때는 Cobj:: 연산자를 사용  
```cpp
class CObj
{
private: //멤버 변수는 무조건 private
    int m_ix;
    int m_iy;
public: //access method, 멤버 변수별로 각각 만들어야 함.
    int GetX() {return m_ix};
    int SetX(int iX) {m_ix = iX};
public: //멤버 함수는 public으로(재사용)
    void Render();
};

void CObj::Render()
{
    cout << m_ix << endl;
}

int main()
{
    CObj Obj = {10,20};
    Obj.SetX(40);
    cout << Obj.GetX(); //access method를통해 x값 가져온 뒤 cout으로 출력 
    Obj.Render(); //멤버함수를 통해 값 출력
}
```
</details>

### 2일차 (260410) class 생성자, 소멸자











