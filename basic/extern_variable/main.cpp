#include <stdio.h>
#include "header.h"

const int gValue = 1;

int main(int argc, char **argv) {
    printf("main: &gValue: %p\n", &gValue);
    printf("main: gValue: %d\n", gValue);

    FuncA();
    FuncB();
}