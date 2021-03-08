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
    /* 
    Notes:
    静态强制转换。但运行时没有类型检查不能保证转换的安全。

    作用:
    1. 用于继承层次结构中基类和派生类之间的指针或引用的转换。其中向上转换（派生类指针 -> 基类指针）是安全的。
       向下转换（基类指针 -> 派生类指针）是不安全的（由于运行时不会进行类型检查）。
    2. 把void*转换成目标类型的指针。
    3. 基本数据类型（非指针）之间的转换，比如从char转int.
    4. 把任何类型的表达式转换为void类型。
    */

    {
        char ch = 'c';
        int int_cast_from_char = static_cast<int>(ch);

        double f64 = 123;
        int int32_cast_from_f64 = static_cast<int>(f64);
    }

    {
        double f64 = 3.14;
        // int* int32_cast_from_f64 = static_cast<int*>(&f64); // 编译错误: invalid static_cast from type ‘double*’ to type ‘int*’
        void* void_ptr = static_cast<void*>(&f64); // 正确
        double* double_ptr = static_cast<double*>(void_ptr); // 正确
        printf("*double_ptr: %f\n", *double_ptr);
    }

    {
        Duck* duck_ptr = new Duck();
        Anatidae* anatidae_ptr = new Anatidae();

        if (Anatidae* ptr = static_cast<Anatidae*>(duck_ptr)) {
            ptr->Fly();  // Output: Duck::Fly，是正确的
        }

        if (Duck* ptr = static_cast<Duck*>(anatidae_ptr)) {
            ptr->Fly();  // Output: Anatidae::Fly而不是Duck::Fly，因此不太安全
        }
    }
}

int Test_dynamic_cast() {
    /* 
    Notes:
    动态强制转换。在继承层次结构中向下转换时会进行类型检查，比static_cast更安全，但耗费成本更高，会降低程序性能.

    作用:
    1. 用于继承层次结构中基类和派生类之间的指针或引用的转换。对于指针，如果转换失败返回空指针；
       而对于引用，则会抛出std::bad_cast异常 (定义在type_info头文件中)。
    */

    std::cout << "测试 派生类指针 -> 基类指针 的转换: \n";
    {
        Duck* duck_ptr = new Duck();
        
        if (Anatidae* ptr = dynamic_cast<Anatidae*>(duck_ptr)) {
            std::cout << "ptr: " << ptr << std::endl;
            ptr->Fly();  // Output: Duck::Fly，是正确的
        }

        delete duck_ptr;
    }

    std::cout << "测试 基类指针-> 派生类指针 的转换: \n";
    {
        Anatidae* anatidae_ptr = new Anatidae();
        if (Duck* ptr = dynamic_cast<Duck*>(anatidae_ptr)) {  // ptr为nullptr
            std::cout << "ptr: " << ptr << std::endl;
            ptr->Fly();
        }
        delete anatidae_ptr;
    }

    std::cout << "测试 派生类引用 -> 基类引用 的转换: \n";
    {
        Duck duck;
        Duck& duck_ref = duck;
        Anatidae& anatidae_ref = dynamic_cast<Anatidae &>(duck_ref);
        anatidae_ref.Fly();
    }

    std::cout << "测试 基类引用 -> 派生类引用 的转换: \n";
    {
        Anatidae anatidae;
        Anatidae& anatidae_ref = anatidae;
        try {
            Duck& duck_ref = dynamic_cast<Duck &>(anatidae_ref);
            duck_ref.Fly();
        } catch(std::bad_cast& e) {
            std::cout << "std::bad_cast exception raised when do dynamic casting. \n";
        }
    }
}

int Test_const_cast() {
    /* 
    Notes:
    去除const限定的强制转换。

    用途:
    1. 将”常量指针“被强转为“非常量指针”，且仍然指向原来的对象
    2. 将“常量引用”被强转为“非常量引用”，且仍然引用原来的对象
    3、”将常量对象“被强转为”非常量对象“.
    */

    std::cout << "测试去除常量对象的const限定: \n";
    {
        const int const_int = 1;
        int const_casted_int = const_cast<int&>(const_int);
        printf("&const_int = %p, &const_casted_int = %p\n", &const_int, &const_casted_int);
    }

    std::cout << "测试去除常量指针的const限定: \n";
    {
        const int *const_int_ptr = new int(1);
        int* const_casted_int_ptr = const_cast<int*>(const_int_ptr);
        printf("const_int_ptr = %p, const_casted_int_ptr = %p\n", const_int_ptr, const_casted_int_ptr);
        printf("*const_int_ptr = %d, *const_casted_int_ptr = %d\n", *const_int_ptr, *const_casted_int_ptr);
        *const_casted_int_ptr = 2;
        printf("*const_int_ptr = %d, *const_casted_int_ptr = %d\n", *const_int_ptr, *const_casted_int_ptr);
    }

    std::cout << "测试去除常量引用的const限定: \n";
    {
        int i = 1;
        const int& const_int_ref = i;
        int& const_casted_int_ref = const_cast<int&>(const_int_ref);
        printf("&const_int_ref = %p, &const_casted_int_ref = %p\n", &const_int_ref, &const_casted_int_ref);
        printf("const_int_ref = %d, const_casted_int_ref = %d\n", const_int_ref, const_casted_int_ref);
        const_casted_int_ref = 2;
        printf("const_int_ref = %d, const_casted_int_ref = %d\n", const_int_ref, const_casted_int_ref);
    }
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