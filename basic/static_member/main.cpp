#include <iostream>
#include <stdio.h>
#include "test_util.h"

class Base {
public:
    virtual ~Base() = 0;  // 通过将纯虚析构函数将其声明为接口类。注意一定要实现这个虚析构函数。

    static const int& getCount();

private:
    static int count;
};


Base::~Base() {}

const int& Base::getCount() {
    return count;
}

int Base::count = 0;


class Derived1: private Base { // 通过private继承，隐藏Base的protected成员
public:
    Derived1() {
        std::cout << "Derived1::Derived1" << std::endl;
    }

    ~Derived1() {
        std::cout << "Derived1::~Derived1" << std::endl;
    }

    using Base::getCount;
};


class Derived2: private Base {
public:
    Derived2() {
        std::cout << "Derived2::Derived2" << std::endl;
    }

    ~Derived2() {
        std::cout << "Derived2::~Derived2" << std::endl;
    }

    using Base::getCount;
};

int Test() {
    Derived1 d1;
    std::cout << "&d1.getCount(): " << &d1.getCount() << std::endl;
    Derived1 d2;
    std::cout << "&d2.getCount(): " << &d2.getCount() << std::endl;
    Derived2 d3;
    std::cout << "&d3.getCount(): " << &d3.getCount() << std::endl;
}

int main(int argc, char** argv) {
    test_decorator(Test, "Test")();
}