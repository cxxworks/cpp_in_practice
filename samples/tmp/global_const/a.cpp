#include <iostream>
#include <stdio.h>
#include "def.h"


void a_func()
{
    printf("a_func: &g_int: %p\n", &g_int);
    printf("a_func: g_int: %d\n", g_int);
}