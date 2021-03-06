#include <iostream>
#include <functional>
#include "test_util.h"

int Test1() {
    auto func = []() {
        std::cout << "Print in the lambda function." << std::endl;
    };

    func();
}

int Test2() {
    int a = 1;
    auto add_a = [a](int b) -> int{
        return a + b;
    };

    std::cout << "add_a(3) = " << add_a(3) << std::endl;
}

int Test3() {
    int a = 1;
    auto add_a = [&](int b) -> int{
        return a + b;
    };

    std::cout << "add_a(3) = " << add_a(3) << std::endl;
}

int Test4() {
    int a = 1;
    const int b = 1;
    auto modify_vars = [&]() {
        a = 3;
        // b = 3;  // 编译失败: a不是可修改的作值
    };
    modify_vars();
}

int main(int arvc, char **argv) {
    test_decorator(Test1, "Test1")();
    test_decorator(Test2, "Test2")();
    test_decorator(Test3, "Test3")();
    test_decorator(Test4, "Test4")();
    return 0;
}