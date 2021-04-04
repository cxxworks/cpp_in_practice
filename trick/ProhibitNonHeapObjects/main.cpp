/* 
 * Notes:
 * 阻止non-heap对象的产生的方法：
 * 1. 控制构造函数、析构函数的访问权限（声明为private或protected），就能阻止隐式调用构造动作和析构动作。
 *    一般只将析构函数声明为private，保持构造函数为public就可以了（而且存在多种形式的构造函数，如果要将构造声明为private就不能放过每一个）。
 * 
 *    但是构造和析构private的声明会影响到类的继承（inheritance）和内含（containment）。
 *    对于继承问题，可以将基类析构函数声明为protected, 然后派生类通过public继承。
 *    对于内含问题，可以通过内含一个指针而不是内含一个对象。
 */

#include <iostream>
#include <string>
#include <cstdio>
#include "test_util.h"

/* 
 * @brief 将析构函数声明为private, 可阻止non-heap对象。
 * 
 * 但这个类无法被继承。
 */
class ClassWithPrivateDtor {
public:
    ClassWithPrivateDtor() = default;

    // 提供伪析构函数，用于显式调用析构
    void Destroy() {
        std::cout << "ClassWithPrivateDtor::Destroy" << std::endl;
    }

private:
    // 析构函数被声明为private，不能通过delete隐式调用
    ~ClassWithPrivateDtor() {
        std::cout << "ClassWithPrivateDtor::~ClassWithPrivateDtor" << std::endl;
    }
};

int Test_ClassWithPrivateDtor() {
    // ClassWithPrivateDtor obj;  // 错误: 因为析构函数被声明为private，无法访问
    ClassWithPrivateDtor *p = new ClassWithPrivateDtor();  // 正确
    // delete p;  // 错误
    p->Destroy();  // 正确
}


class ClassWithProtectedDtor {
public:
    ClassWithProtectedDtor() = default;

    // 提供伪析构函数，用于显式调用析构
    void Destroy() {
        std::cout << "ClassWithProtectedDtor::Destroy" << std::endl;
    }

protected:
    // 析构函数被声明为private，不能通过delete隐式调用
    ~ClassWithProtectedDtor() {
        std::cout << "ClassWithProtectedDtor::~ClassWithProtectedDtor" << std::endl;
    }
};


class DerivedClassWithProtectedDtor: public ClassWithProtectedDtor {
public:
    DerivedClassWithProtectedDtor()
        : ClassWithProtectedDtor() {}

    ~DerivedClassWithProtectedDtor() {
        std::cout << "DerivedClassWithProtectedDtor::~DerivedClassWithProtectedDtor" << std::endl;
    }
};

class Asset {
public:
    Asset()
        : p(new ClassWithProtectedDtor()) {}

    ~Asset() {
        std::cout << "Asset::~Asset" << std::endl;
        p->Destroy();
    };

private:
    ClassWithProtectedDtor *p;
};

int Test_ClassWithProtectedDtor() {
    // ClassWithProtectedDtor obj;  // 错误: 因为析构函数被声明为protected，无法访问
    ClassWithPrivateDtor *p = new ClassWithPrivateDtor();  // 正确
    // delete p;  // 错误
    p->Destroy();  // 正确
}

int Test_ClassWithProtectedDtor_Inheritance() {
    DerivedClassWithProtectedDtor *p = new DerivedClassWithProtectedDtor();
    delete p;
}

int Test_DerivedClassWithProtectedDtor_Containment() {
    Asset *p = new Asset();
    delete p;
}


int main(int argc, char** argv) {
    test_decorator(Test_ClassWithPrivateDtor, "Test_ClassWithPrivateDtor")();
    test_decorator(Test_ClassWithProtectedDtor, "Test_ClassWithProtectedDtor")();
    test_decorator(Test_ClassWithProtectedDtor_Inheritance, "Test_ClassWithProtectedDtor_Inheritance")();
    test_decorator(Test_DerivedClassWithProtectedDtor_Containment, "Test_DerivedClassWithProtectedDtor_Containment")();
}