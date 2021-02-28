#include <iostream>
#include <stdio.h>

void func1()
{
    static int static_int = 1;
    
    static_int++;

    std::cout << "static_int: " << static_int << std::endl;
}

int* func2()
{
    static int static_int = 1;
    
    static_int++;
    
    return &static_int;
}

void func3()
{
    int* ret = func2();
    std::cout << "func2 return: " << *ret << std::endl;

    ret = func2();
    std::cout << "func2 return: " << *ret << std::endl;

    (*ret)++;

    ret = func2();
    std::cout << "func2 return: " << *ret << std::endl;
}

int main(int argc, char** argv)
{
    func1();
    func1();

    func3();
    return 0;
}