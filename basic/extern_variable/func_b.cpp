#include <stdio.h>
#include "header.h"

void FuncB()
{
    printf("FuncB: &gValue: %p\n", &gValue);
    printf("FuncB: gValue: %d\n", gValue);
}