/* 
Notes:

Reference:
[1] http://www.cplusplus.com/reference/cstdio/printf/
 */

#include <iostream>
#include <stdio.h>
#include "test_util.h"

int TestPrintfBasicNumericTypes() {
    uint8_t u8 = 64;
    int8_t i8 = -64;
    uint32_t u32 = 64534534;
    int32_t i32 = 142893244;
    // int32_t i32 = 142893244343;  // 错误: overflow
    int64_t u64 = 56453453443423;
    int64_t i64 = 9079842343242432432;
    // int64_t i64 = 9079842343242432432432;  // 错误: overflow
    float f32 = 3.1415926535898;
    double f64 = 3.1415926535898;
    
    printf("u8: %i\n", u8);
    printf("i8: %i\n", i8);
    printf("i8: %u\n", i8);
    printf("i32: %d\n", i32);
    printf("i64: %ld\n", i64);
    printf("u32: %u\n", u32);
    printf("u64: %lu\n", u64);
    printf("f32: %.13f\n", f32);
    printf("f64: %.13f\n", f64);
}

int TestPrintfCharTypes() {
    char c = 'a';
    u_char uc = 'a';
    // char chars[13] = "Hello World!"; // 错误：C++禁止从string到char*的隐式转换
    char chars[13] = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!', '\0'};

    printf("c: %c\n", c);
    printf("uc: %c\n", uc);
    printf("chars: %s\n", chars);
}

int main(int argc, char** argv) {
    test_decorator(TestPrintfBasicNumericTypes, "TestPrintfBasicNumericTypes")();
    test_decorator(TestPrintfCharTypes, "TestPrintfCharTypes")();
}