#include <iostream>
#include <stdio.h>
#include "def.h"


void b_func()
{
    printf("b_func: &g_int: %p\n", &g_int);
    printf("b_func: g_int: %d\n", g_int);
}