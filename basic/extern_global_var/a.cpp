#include <iostream>
#include <stdio.h>
#include "def.h"

extern int g_int2;

void a_func()
{
    int g_int1 = 3;
    int g_int2 = 5;

    printf("a_func: &g_int1: %p\n", &g_int1);
    printf("a_func: g_int1: %d\n", g_int1);

    printf("a_func: &g_int2: %p\n", &g_int2);
    printf("a_func: g_int2: %d\n", g_int2);
}