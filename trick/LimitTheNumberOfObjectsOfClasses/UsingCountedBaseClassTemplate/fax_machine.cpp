#include <iostream>
#include "fax_machine.h"

FaxMachine::FaxMachine() {
    std::cout << "FaxMachine::FaxMachine" << std::endl;
}

FaxMachine::FaxMachine(const FaxMachine& rhs) {
    std::cout << "FaxMachine::FaxMachine" << std::endl;
}

FaxMachine::~FaxMachine() {
    std::cout << "FaxMachine::~FaxMachine" << std::endl;
}

std::shared_ptr<FaxMachine> FaxMachine::makeFaxMachine() {
    // return std::make_shared<FaxMachine>();  // 错误: 因为FaxMachine::FaxMachine()声明为private, 阻止std::make_shared隐式调用构造函数
    return std::shared_ptr<FaxMachine>(new FaxMachine());
}

std::shared_ptr<FaxMachine> FaxMachine::makeFaxMachine(const FaxMachine& rhs) {
    // return std::make_shared<FaxMachine>(rhs);  // 错误: 因为FaxMachine::FaxMachine(const FaxMachine& rhs)声明为private, 阻止std::make_shared隐式调用构造函数
    return std::shared_ptr<FaxMachine>(new FaxMachine(rhs));
}

template<>
const int Counted<FaxMachine>::kMaxObjects = 2;

template<>
int Counted<FaxMachine>::numObjects = 0;