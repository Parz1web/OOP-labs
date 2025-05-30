#include <iostream>
#include <vector>
#include <crtdbg.h>
#include <string>

class Class1 {
public:
    int a;
    int b;

    Class1() {
        a = 142;
        b = a - 12;
    }

    Class1(const Class1 &obj) {
        a = obj.a;
        b = obj.b;
    }

    virtual ~Class1() = default;
};

class Class2 : public Class1 {
public:
    int c;

    Class2() {
        c = 512;
    }

    Class2(const Class2 &obj): Class1(obj) {
        c = obj.c;
    }

    ~Class2() = default;
};

template<typename T>
T *myCopy(const T &obj) {
    return new T(obj);
}

int main() {
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);

    std::vector<Class1 *> db;
    for (int i = 0; i < 10; i++) {
        Class1 c1;
        Class2 c2;
        if (i % 2 == 0) {
            db.push_back(myCopy(c1));
        } else {
            db.push_back(myCopy(c2));
        }
    }

    for (int i = 0; i < db.size(); i++) {
        std::cout << "Object #" << i + 1 << ": " << typeid(*db[i]).name() << "\n";
        delete db[i];
    }

    _CrtDumpMemoryLeaks();
    return 0;
}