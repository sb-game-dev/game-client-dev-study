#include "pch.h"
class CObj
{
public:
    CObj(string temp):m_iA(temp) {}
    ~CObj() {}

public:
    void Render() { cout << m_iA << endl; }
private:
    const string m_iA;
};


int main()
{
    CObj Obj("hello");
    Obj.Render();
}


