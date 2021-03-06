#ifndef MOCK_POLYMORPHIC_H
#define MOCK_POLYMORPHIC_H

#include <iostream>

class Abc {
    virtual void Interface1() = 0;
    virtual void Interface2() = 0;
};

class Base : public Abc {
public:
    Base() {
        std::cout << "Base::Base" << std::endl;
    }

    Base(const Base& other) {
        std::cout << "Base::Base(const Base& other)" << std::endl;
    }

    Base(Base&& other) {
        std::cout << "Base::Base(Base&& other)" << std::endl;
    }

    virtual ~Base() {
        std::cout << "Base::~Base" << std::endl;
    }

    void Interface1() override {
        std::cout << "Base::Interface1" << std::endl;
    }

    virtual void Interface2() override {
        std::cout << "Base::Interface2" << std::endl;
    }
};

class DerivedA : public Base {
public:
    DerivedA()
     : Base() {
        std::cout << "DerivedA::DerivedA" << std::endl;
    }

    DerivedA(const DerivedA& other) {
        std::cout << "DerivedA::DerivedA(const DerivedA& other)" << std::endl;
    }

    DerivedA(DerivedA&& other) {
        std::cout << "DerivedA::DerivedA(DerivedA&& other)" << std::endl;
    }

    virtual ~DerivedA() {
        std::cout << "DerivedA::~DerivedA" << std::endl;
    }

    void Interface2() override {
        std::cout << "DerivedA::Interface2" << std::endl;
    }
};

class DerivedB final : public DerivedA {
public:
    DerivedB()
     : DerivedA() {
        std::cout << "DerivedB::DerivedB" << std::endl;
    }

    DerivedB(const DerivedB& other) {
        std::cout << "DerivedB::DerivedB(const DerivedB& other)" << std::endl;
    }

    DerivedB(DerivedB&& other) {
        std::cout << "DerivedB::DerivedB(DerivedB&& other)" << std::endl;
    }

    ~DerivedB() {
        std::cout << "DerivedB::~DerivedB" << std::endl;
    }

    void Interface2() override {
        std::cout << "DerivedB::Interface2" << std::endl;
    }
};

#endif