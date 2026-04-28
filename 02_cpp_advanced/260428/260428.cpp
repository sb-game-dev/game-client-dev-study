#include "pch.h"
#include <vector>
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
    vector<int> v;
    v.push_back(10);
    cout << v.size() << endl;
    Obj.Render();
}


