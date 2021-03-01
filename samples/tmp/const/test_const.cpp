#include <iostream>
#include <stdio.h>

using namespace std;


void test1()
{
	char c = 'h';
    char* ptr = &c;

    printf("&c = %p\n", &c);
    printf("ptr = %p\n", ptr);
    std::cout << "*ptr = " << *ptr << std::endl;
    
    *ptr = 'w';
    printf("ptr = %p\n", ptr);
    std::cout << "*ptr = " << *ptr << std::endl;
}


// void test2()
// {
// 	char c = 'h';
//     const char* ptr = &c;
//     std::cout << "*ptr: " << *ptr << std::endl;

//     *ptr = 'w';
//     std::cout << "*ptr: " << *ptr << std::endl;
// }


// void test3()
// {
//     const char const_c = 'h';

//     char* ptr1 = &const_c;

// }


void test4()
{
    const char const_c = 'h';
    const char* ptr = &const_c;

    printf("&const_c = %p\n", &const_c);
    printf("ptr = %p\n", ptr);
}


const int* func2()
{
    const int *a = new int(1);
    return a;
}


const int& func3()
{
    const int a = 1;
    return a;
}


int main(int argc, char** argv)
{
    // test1();
    // test4();
    const int *a = func2();
    std::cout << "*a = " << *a << std::endl;
}