/* 
Notes:

Reference:
[1] 
 */

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include "mock_duck.h"
#include "test_util.h"


int TestCastBasicNumericTypes() {
    uint8_t u8 = 64;
    int8_t i8 = -64;
    uint32_t u32 = 64534534;
    int32_t i32 = 142893244;
    int64_t u64 = 56453453443423;
    int64_t i64 = 9079842343242432432;
    float f32 = 3.1415926535898;
    double f64 = 3.1415926535898;
    char c = 'a';
    u_char uc = 'a';

    printf("u8: %i\n", u8);
    printf("i8: %i\n", i8);
    printf("i8: %u\n", i8);
    printf("i32: %d\n", i32);
    printf("i64: %ld\n", i64);
    printf("u32: %u\n", u32);
    printf("u64: %lu\n", u64);
    printf("f32: %.13f\n", f32);
    printf("f64: %.13f\n", f64);
    printf("c: %c\n", c);
    printf("uc: %c\n", uc);

    float f32_cast_from_i32 = (float)i32;  // 有损失
    float f32_cast_from_i64 = (float)i64;  // 有损失
    double f64_cast_from_i64 = (double)i64;  // 有损失
    float f32_cast_from_f64 = (float)f64;  // 有精度损失
    printf("f32_cast_from_i32: %.13f\n", f32_cast_from_i32);
    printf("f32_cast_from_i64: %.13f\n", f32_cast_from_i64);
    printf("f64_cast_from_i64: %.13f\n", f64_cast_from_i64);
    printf("f32_cast_from_f64: %.13f\n", f32_cast_from_f64);
}

int TestCastPolymorphicTypePointers() {
    Bird* bird_ptr;
    Anatidae* anatidae_ptr;
    Duck* duck_ptr;

    Duck duck;
    
    bird_ptr = (Bird*)(&duck);
    anatidae_ptr = (Anatidae*)(&duck);
    duck_ptr = (Duck*)(&duck);

    bird_ptr->Eat();
    anatidae_ptr->Eat();
    duck_ptr->Eat();
}

int Test_static_cast() {

}

int Test_dynamic_cast() {

}

int Test_const_cast() {

}

int Test_reinterpret_cast() {

}

int main(int argc, char** argv) {
    test_decorator(TestCastBasicNumericTypes, "TestCastBasicNumericTypes")();
    test_decorator(TestCastPolymorphicTypePointers, "TestCastPolymorphicTypePointers")();
    test_decorator(Test_static_cast, "Test_static_cast")();
    test_decorator(Test_dynamic_cast, "Test_dynamic_cast")();
    test_decorator(Test_const_cast, "Test_const_cast")();
    test_decorator(Test_reinterpret_cast, "Test_reinterpret_cast")();
}