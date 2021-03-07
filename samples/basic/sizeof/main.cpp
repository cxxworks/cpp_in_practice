/* 
Notes:
 */

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <cassert>
#include "test_util.h"
#include "mock_duck.h"
#include "mock_rect.h"
#include "mock_struct.h"


int TestSizeOfBasicNumericTypes() {
    std::cout << "sizeof(uint8_t): " << sizeof(uint8_t) << std::endl;
    std::cout << "sizeof(int8_t): " << sizeof(int8_t) << std::endl;
    std::cout << "sizeof(uint16_t): " << sizeof(uint16_t) << std::endl;
    std::cout << "sizeof(int16_t): " << sizeof(int16_t) << std::endl;
    std::cout << "sizeof(uint32_t): " << sizeof(uint32_t) << std::endl;
    std::cout << "sizeof(int32_t): " << sizeof(int32_t) << std::endl;
    std::cout << "sizeof(uint64_t): " << sizeof(uint64_t) << std::endl;
    std::cout << "sizeof(int64_t): " << sizeof(int64_t) << std::endl;

    std::cout << "sizeof(int): " << sizeof(int) << std::endl;
    std::cout << "sizeof(long): " << sizeof(long) << std::endl;
    std::cout << "sizeof(long long): " << sizeof(long long) << std::endl;
    std::cout << "sizeof(short): " << sizeof(short) << std::endl;

    std::cout << "sizeof(float): " << sizeof(float) << std::endl;
    std::cout << "sizeof(double): " << sizeof(double) << std::endl;
}

int TestSizeOfCharTypes() {
    std::cout << "sizeof(char): " << sizeof(char) << std::endl;
    std::cout << "sizeof(u_char): " << sizeof(u_char) << std::endl;
    std::cout << "sizeof(std::string): " << sizeof(std::string) << std::endl;
}

int TestSizeOfTemplateTypes() {
    std::cout << "sizeof(Rect<int>): " << sizeof(Rect<int>) << std::endl;
    std::cout << "sizeof(Rect<float>): " << sizeof(Rect<float>) << std::endl;

    std::cout << "sizeof(std::vector<int>): " << sizeof(std::vector<int>) << std::endl;
    std::cout << "sizeof(std::vector<float>): " << sizeof(std::vector<float>) << std::endl;
    std::cout << "sizeof(std::vector<std::string>): " << sizeof(std::vector<std::string>) << std::endl;
}

int TestSizeOfUserDefinedTypes() {
    std::cout << "sizeof(Duck): " << sizeof(Duck) << std::endl;
    std::cout << "sizeof(Anatidae): " << sizeof(Anatidae) << std::endl;
    std::cout << "sizeof(Bird): " << sizeof(Bird) << std::endl;
}

int TestSizeOfPointers() {
    std::cout << "sizeof(Duck*): " << sizeof(Duck*) << std::endl;
    std::cout << "sizeof(Anatidae*): " << sizeof(Anatidae*) << std::endl;
    std::cout << "sizeof(Bird*): " << sizeof(Bird*) << std::endl;
}

int TestSizeOfSmartPointers() {
    std::cout << "sizeof(std::shared_ptr<Duck>): " << sizeof(std::shared_ptr<Duck>) << std::endl;
    std::cout << "sizeof(std::shared_ptr<Anatidae>): " << sizeof(std::shared_ptr<Anatidae>) << std::endl;
    std::cout << "sizeof(std::shared_ptr<Bird>): " << sizeof(std::shared_ptr<Bird>) << std::endl;
}

int TestSizeOfStructs() {
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

    std::cout << "sizeof(struct_1): " << sizeof(struct_1) << std::endl;
    std::cout << "sizeof(struct_2): " << sizeof(struct_2) << std::endl;
    std::cout << "sizeof(struct_3): " << sizeof(struct_3) << std::endl;
    std::cout << "sizeof(struct_4): " << sizeof(struct_4) << std::endl;
    std::cout << "sizeof(struct_5): " << sizeof(struct_5) << std::endl;
}

int main(int argc, char** argv) {
    test_decorator(TestSizeOfBasicNumericTypes, "TestSizeOfBasicNumericTypes")();
    test_decorator(TestSizeOfCharTypes, "TestSizeOfCharTypes")();
    test_decorator(TestSizeOfTemplateTypes, "TestSizeOfTemplateTypes")();
    test_decorator(TestSizeOfUserDefinedTypes, "TestSizeOfUserDefinedTypes")();
    test_decorator(TestSizeOfPointers, "TestSizeOfPointers")();
    test_decorator(TestSizeOfSmartPointers, "TestSizeOfSmartPointers")();
    test_decorator(TestSizeOfStructs, "TestSizeOfStructs")();
}