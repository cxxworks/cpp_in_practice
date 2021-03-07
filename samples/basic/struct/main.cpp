/* 
Notes:
 */

#include <iostream>
#include "test_util.h"

#define offset(type, v) ((size_t)&((type *)0)->v)

struct struct_1 {};

struct struct_2 {
    std::string id;
};

struct struct_3 {
    std::string id;
    std::string name;
};

struct struct_4 {
    std::string id;
    std::string name;
    uint8_t age;
};

struct struct_5 {
    std::string id;
    std::string name;
    uint8_t age;

    struct_5(const std::string& id, const std::string& name, uint8_t age) 
        : id(id), name(name), age(age) {}
    
    ~struct_5() {}

    void Register() {}
};

int TestSizeOfStructs() {
    std::cout << "sizeof(struct_1): " << sizeof(struct_1) << std::endl;
    std::cout << "sizeof(struct_2): " << sizeof(struct_2) << std::endl;
    std::cout << "sizeof(struct_3): " << sizeof(struct_3) << std::endl;
    std::cout << "sizeof(struct_4): " << sizeof(struct_4) << std::endl;
}

int TestInitialize() {
    struct_4 s = {"1", "Lee", 18};
    struct_4 s2({"1", "Lee", 18});
    struct_5 s3("1", "Lee", 18);
}

int TestPointerOffset() {
    struct test_struct {
        float a;
        int b;
        char c;
    };

    test_struct s = {1, 2, 'c'};
    test_struct* sp = &s;

    std::cout << "offsetof(test_struct, a): " << offsetof(test_struct, a) << std::endl;
    std::cout << "offsetof(test_struct, b): " << offsetof(test_struct, b) << std::endl;
    std::cout << "offsetof(test_struct, c): " << offsetof(test_struct, c) << std::endl;

    std::cout << "offset(test_struct, a): " << offset(test_struct, a) << std::endl;
    std::cout << "offset(test_struct, b): " << offset(test_struct, b) << std::endl;
    std::cout << "offset(test_struct, c): " << offset(test_struct, c) << std::endl;

    std::cout << "&test_struct::a: " << &test_struct::a << std::endl;
    std::cout << "&test_struct::b: " << &test_struct::b << std::endl;
    std::cout << "&test_struct::c: " << &test_struct::c << std::endl;

    char* s_storage_p = reinterpret_cast<char*>(sp);
    float* ap = reinterpret_cast<float*>(s_storage_p + offsetof(test_struct, a));
    int* bp = reinterpret_cast<int*>(s_storage_p + offsetof(test_struct, b));
    char* cp = reinterpret_cast<char*>(s_storage_p + offsetof(test_struct, c));

    std::cout << "*ap: " << *ap << std::endl;
    std::cout << "*bp: " << *bp << std::endl;
    std::cout << "*cp: " << *cp << std::endl;
}

int main(int argc, char** argv) {
    test_decorator(TestSizeOfStructs, "TestSizeOfStructs")();
    test_decorator(TestInitialize, "TestInitialize")();
    test_decorator(TestPointerOffset, "TestPointerOffset")();
}