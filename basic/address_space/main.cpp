#include <iostream>
#include <stdio.h>
#include "test_util.h"

int Test_InspectAddressOfStackHeapAndStaticObjects() {
    char c = 'a';
    char *pc = new char('b');
    static char sc = 'c';

    printf("&c = %p\n", &c);
    printf("pc = %p\n", pc);
    printf("&sc = %p\n", &sc);

    printf("&c > pc: %d\n", &c > pc);
    printf("pc > &sc: %d\n", pc > &sc);
}

int main(int argc, char** argv) {
    test_decorator(Test_InspectAddressOfStackHeapAndStaticObjects, "Test_InspectAddressOfStackHeapAndStaticObjects")();
}
