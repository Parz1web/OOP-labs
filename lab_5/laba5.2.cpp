#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <typeinfo>

using namespace std;

class A {
public:
    string s;
    A() {
        cout << "����������� �� ��������� ������ A" << endl;
    }

    A(const char* a) {
        s = a;
        cout << "���������������� ����������� ������ A" << endl;
        cout << s << endl;
    }

    virtual ~A() {
        cout << "���������� ������ A" << endl;
        cout << typeid(*this).name() << endl;
    }
};

class B : public A {
public:
    B() {
        cout << "����������� ������ B" << endl;
    }

    B(const char* a) : A(a) {
        cout << "���������������� ����������� ������ B" << endl;
        cout << a << endl;
    }

    ~B() {
        cout << "���������� ������ B" << endl;
        cout << typeid(*this).name() << endl;
    }
};

void del(vector<A*>& v) {
    for (size_t i = 0; i < v.size(); ++i)
        delete v[i];
    v.clear();
}

int main() {
    setlocale(LC_ALL, "Russian");
    list<A*> l;
    vector<A*> v;

    l.push_back(new A("first"));
    l.push_back(new B("second"));

    v.assign(l.begin(), l.end());

    del(v);

    return 0;
}