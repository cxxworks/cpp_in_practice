
#include <iostream>
#include <string>

#include "mock_string.h"


void TestPassByValue() {
    auto func = [](String str) {
        std::cout << "str's content: " << str << std::endl;
    };

    std::cout << std::endl;
    std::cout << "<<< TestPassByValue <<<" << std::endl;
    String test_str("Hello World!");
    func(test_str);
    std::cout << "<<< End of The Output <<<" << std::endl;   
}

void TestPassByReference() {
    auto func = [](String& str) {
        std::cout << "str's content: " << str << std::endl;
    };

    std::cout << std::endl;
    std::cout << "<<< TestPassByReference <<<" << std::endl;
    String test_str("Hello World!");
    func(test_str);
    std::cout << "<<< End of The Output <<<" << std::endl;
}

void TestReturnValue1() {
    auto func = [](const String& str) -> String {
        String tmp(str);
        return tmp;
    };

    std::cout << std::endl;
    std::cout << "<<< TestReturnValue1 <<<" << std::endl;
    String test_str("Hello World!");
    String ret = func(test_str);
    std::cout << "<<< End of The Output <<<" << std::endl;
}

void TestReturnValue2() {
    auto func = [](const String& str) -> String {
        return String(str);
    };

    std::cout << std::endl;
    std::cout << "<<< TestReturnValue2 <<<" << std::endl;
    String test_str("Hello World!");
    String ret = func(test_str);
    std::cout << "<<< End of The Output <<<" << std::endl;
}

void TestCopyConstructor() {
    auto func = []() {
        String str1("Hello World!");
        String str2(str1);
    };

    std::cout << std::endl;
    std::cout << "<<< TestCopyConstructor <<<" << std::endl;
    func();
    std::cout << "<<< End of The Output <<<" << std::endl;
}

void TestMoveConstructor() {
    auto func = []() {
        String str1(String("Hello World!"));
        String str2 = String("Hello World!");
    };

    std::cout << std::endl;
    std::cout << "<<< TestMoveConstructor <<<" << std::endl;
    func();
    std::cout << "<<< End of The Output <<<" << std::endl;
}

void TestCopyAssignment() {
    auto func = []() {
        String str1("Hello World!");
        String str2;
        str2 = str1;
    };

    std::cout << std::endl;
    std::cout << "<<< TestCopyAssignment <<<" << std::endl;
    func();
    std::cout << "<<< End of The Output <<<" << std::endl;
}

void TestMoveAssignment() {
    auto func = []() {
        String str2;
        str2 = String("Hello World!");
    };
    
    std::cout << std::endl;
    std::cout << "<<< TestMoveAssignment <<<" << std::endl;
    func();
    std::cout << "<<< End of The Output <<<" << std::endl;
}

int main(int argc, char **argv) {
    TestPassByValue();
    TestPassByReference();
    TestReturnValue1();
    TestReturnValue2();
    TestCopyConstructor();
    TestMoveConstructor();
    TestCopyAssignment();
    TestMoveAssignment();
    return 0;
}