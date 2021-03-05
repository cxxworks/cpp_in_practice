#include <iostream>
#include <stdio.h>
#include <functional>
#include "test_util.h"

int Test1() {
	char c = 'h';
    char* ptr = &c;

    printf("&c = %p\n", &c);
    printf("ptr = %p\n", ptr);
    std::cout << "*ptr = " << *ptr << std::endl;
    
    *ptr = 'w';
    printf("ptr = %p\n", ptr);
    std::cout << "*ptr = " << *ptr << std::endl;
}

int Test2()
{
	char ch = 'a';
    char* ptr_to_ch = &ch;
    std::cout << "ch: " << ch << std::endl;
    std::cout << "*ptr_to_ch: " << *ptr_to_ch << std::endl;
    *ptr_to_ch = 'b';
    std::cout << "ch: " << ch << std::endl;
    std::cout << "*ptr_to_ch: " << *ptr_to_ch << std::endl;
}

int Test3() {
    const char const_ch = 'a';
    const char* ptr_to_const_ch = &const_ch;
    // *ptr_to_const_ch = 'b';  // 编译失败：指针`ptr_to_const_ch`指向常量char， 无法通过指针修改
}

int Test4() {
    char ch = 'a';
    char ch2 = 'b';
    char* const const_ptr_to_ch = &ch;
    *const_ptr_to_ch = 'c';
    // const_ptr_to_ch = &ch2;  // 编译失败：常量指针`const_ptr_to_ch`无法修改
}

int Test5() {
    auto tmp_func = []() -> const int* {
        int *ptr = new int(1);
        return ptr;
    };

    // int *ptr = tmp_func();  // 编译失败：无法从`const int*`到`int*`
    const int *ptr = tmp_func();
    std::cout << "*ptr = " << *ptr << std::endl;
    // *ptr = 2;  // 编译失败：*ptr不是可修改的左值
    delete ptr;  // 编译成功，可以释放ptr所指内存
    std::cout << "*ptr = " << *ptr << std::endl;
}

int main(int argc, char** argv) {
    test_decorator(Test1, "Test1")();
    test_decorator(Test2, "Test2")();
    test_decorator(Test3, "Test3")();
    test_decorator(Test4, "Test4")();
    test_decorator(Test5, "Test5")();
}