#include <iostream>
#include <stdio.h>
#include "def.h"

void b_func()
{
    int g_int1;
    printf("b_func: &g_int1: %p\n", &g_int1);
    printf("b_func: g_int1: %d\n", g_int1);

    int g_int2;
    printf("b_func: &g_int2: %p\n", &g_int2);
    printf("b_func: g_int2: %d\n", g_int2);
}