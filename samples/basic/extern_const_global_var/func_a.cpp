#include <stdio.h>
#include "header.h"

void FuncA() {
    printf("FuncA: &gValue: %p\n", &gValue);
    printf("FuncA: gValue: %d\n", gValue);
}