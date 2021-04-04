#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdio>
#include <list>
#include <algorithm>
#include "test_util.h"


class HeapTracked {
public:
    class MissingAddressError: public std::runtime_error {
    public:
        MissingAddressError(std::string &str) : std::runtime_error(str) {}
        MissingAddressError() : std::runtime_error("MissingAddressError") {}
    };

    virtual ~HeapTracked() = 0;

    static void *operator new(size_t size);

    static void operator delete(void *ptr);

    bool IsOnHeep() const;

private:
    using RawAddressType = const void*;
    static std::list<RawAddressType> addresses;
};


/* 
 * 虽然HeapTracked的析构函数是个纯虚函数，但是这里也要定义。
 * 为什么？
 */
HeapTracked::~HeapTracked() {
    std::cout << "HeapTracked::~HeapTracked" << std::endl;
}


/* 
 * 在类外初始化static成员:
 */
std::list<HeapTracked::RawAddressType> HeapTracked::addresses;


void * HeapTracked::operator new(size_t size) {
    void* mem_ptr = ::operator new(size);
    
    addresses.push_front(mem_ptr);

    return mem_ptr;
}

void  HeapTracked::operator delete(void *ptr) {
    auto found = std::find(addresses.begin(), addresses.end(), ptr);
    if (found != addresses.end()) {
        addresses.erase(found);
        ::operator delete(ptr);
    } else {
        throw MissingAddressError();
    }
}


bool HeapTracked::IsOnHeep() const {
    const void* mem_ptr = dynamic_cast<const void*>(this);

    auto found = std::find(addresses.begin(), addresses.end(), mem_ptr);
    return found != addresses.end();
}

class Derived : public HeapTracked {
public:
    Derived() = default;
    ~Derived() {
        std::cout << "Derived::~Derived" << std::endl;
    }
};

int Test_HeapTrackedObjects() {
    Derived *p = new Derived();
    if (p->IsOnHeep()) {
        std::cout << "*p is on the heap" << std::endl;
    } else {
        std::cout << "*p is not on the heap" << std::endl;
    }
    delete p;

    Derived obj;
    if (obj.IsOnHeep()) {
        std::cout << "obj is on the heap" << std::endl;
    } else {
        std::cout << "obj is not on the heap" << std::endl;
    }
}


int main(int argc, char** argv) {
    test_decorator(Test_HeapTrackedObjects, "Test_HeapTrackedObjects")();
}