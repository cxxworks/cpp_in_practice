#include <iostream>
#include <string>
#include <sstream>
#include "test_util.h"


int TestIntToString() {
    int int_var = 100;
    std::string str_var;
    std::stringstream s;
    s << int_var;
    s >> str_var;
    std::cout << "str_var: " << str_var << std::endl;
}

int main(int arvc, char **argv) {
    test_decorator(TestIntToString, "TestIntToString")();
}