#include <iostream>
#include <stdio.h>
#include "test_util.h"

class BaseWithoutVirtualDtor {
public:
    BaseWithoutVirtualDtor() {
        std::cout << "BaseWithoutVirtualDtor::BaseWithoutVirtualDtor" << std::endl;
    }

    ~BaseWithoutVirtualDtor() {
        std::cout << "BaseWithoutVirtualDtor::~BaseWithoutVirtualDtor" << std::endl;
    }
};

class DerivedWithoutVirtualDtor: public BaseWithoutVirtualDtor {
public:
    DerivedWithoutVirtualDtor() {
        std::cout << "DerivedWithoutVirtualDtor::DerivedWithoutVirtualDtor" << std::endl;

    }

    ~DerivedWithoutVirtualDtor() {
        std::cout << "DerivedWithoutVirtualDtor::~DerivedWithoutVirtualDtor" << std::endl;

    }
};

class BaseWithVirtualDtor {
public:
    BaseWithVirtualDtor() {
        std::cout << "BaseWithVirtualDtor::BaseWithVirtualDtor" << std::endl;
    }

    virtual ~BaseWithVirtualDtor() {
        std::cout << "BaseWithVirtualDtor::~BaseWithVirtualDtor" << std::endl;
    }
};

class DerivedWithVirtualDtor: public BaseWithVirtualDtor {
public:
    DerivedWithVirtualDtor() {
        std::cout << "DerivedWithVirtualDtor::DerivedWithVirtualDtor" << std::endl;

    }

    ~DerivedWithVirtualDtor() {
        std::cout << "DerivedWithVirtualDtor::~DerivedWithVirtualDtor" << std::endl;

    }
};

int Test_CreateOnStackWithoutVirtualDtor() {
    DerivedWithoutVirtualDtor d;
}

int Test_CreateOnHeapWithoutVirtualDtor() {
    std::cout << "@deconstruct with the base classess pointer:" << std::endl;
    BaseWithoutVirtualDtor* b_ptr = new DerivedWithoutVirtualDtor();
    delete b_ptr;

    std::cout << "@deconstruct with the derived classess pointer:" << std::endl;
    DerivedWithoutVirtualDtor* d_ptr = new DerivedWithoutVirtualDtor();
    delete d_ptr;
}

int Test_CreateOnStackWithVirtualDtor() {
    DerivedWithoutVirtualDtor d;
}

int Test_CreateOnHeapWithVirtualDtor() {
    std::cout << "@deconstruct with the base classess pointer:" << std::endl;
    BaseWithVirtualDtor* b_ptr = new DerivedWithVirtualDtor();
    delete b_ptr;
    std::cout << "@deconstruct with the derived classess pointer:" << std::endl;
    DerivedWithVirtualDtor* d_ptr = new DerivedWithVirtualDtor();
    delete d_ptr;
}

int main(int argc, char** argv) {
    test_decorator(Test_CreateOnStackWithoutVirtualDtor, "Test_CreateOnStackWithoutVirtualDtor")();
    test_decorator(Test_CreateOnHeapWithoutVirtualDtor, "Test_CreateOnHeapWithoutVirtualDtor")();
    test_decorator(Test_CreateOnStackWithVirtualDtor, "Test_CreateOnStackWithVirtualDtor")();
    test_decorator(Test_CreateOnHeapWithVirtualDtor, "Test_CreateOnHeapWithVirtualDtor")();
}