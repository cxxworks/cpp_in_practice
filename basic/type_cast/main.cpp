/* 
Notes:

Reference:
[1] https://en.cppreference.com/w/cpp/language/static_cast
[2] https://en.cppreference.com/w/cpp/language/dynamic_cast
[3] https://en.cppreference.com/w/cpp/language/const_cast
[4] https://en.cppreference.com/w/cpp/language/reinterpret_cast
 */

#include <iostream>
#include <stdio.h>
#include <string>
#include <cstring>
#include <vector>
#include "mock_duck.h"
#include "test_util.h"
#include "string_util.h"

int test_func() { return 42; }

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
    动态强制转换。在继承层次结构中向下转换（基类指针 -> 派生类指针）时会进行类型检查，比static_cast更安全，但耗费成本更高，会降低程序性能.

    作用:
    1. 用于继承层次结构中基类和派生类之间的指针或引用的转换。对于指针，如果转换失败返回空指针；
       而对于引用，则会抛出std::bad_cast异常 (定义在type_info头文件中)。
    2. 凡涉及多重或虚拟基类指针的对象会拥有多个地址，可以通过dynamic_cast<void*>(obj_ptr)获取指向对象的内存起始处的指针。
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

    作用:
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
    /* 
    Notes:
    reinterpret_cast通过重新解释对象的比特位来进行强制类型转换。
    
    不像static_cast，但和const_cast一样，reinterpret_cast<new type>表达式不会被编译成任何CPU指令（除了整数和指针之间的转换外）
    它纯粹是一个编译时指令，指示编译器它视为具有<new type>的类型。
    
    reinterpret_cast转换了操作数的类型，但仅仅是重新解释了操作数的比特位而没有进行二进制转换（比如int*转double*仅仅是复制int的比特位到double）

    作用:
    1. 整数、枚举值、指针等表达式的转换，转换后的值和表达式的一致。
    2. 将指针转换为足够大的整数类型（std::uintptr_t）。
    3. 将整数类型、枚举类型转换为指针类型。
    4. 任何指向函数的指针可以被转换为指向另一个函数类型的指针。
       转换后的指针是不安全的（undefined），但是转换回原始函数的指针是安全的。
    5. 将函数指针和void*或者其它类型的指针之间的转换。
    6. 将std::nullptr_t类型的值 （比如nullptr）转换为任何整数的类型。
    7. T1*可以转换为T2*（等价于static_cast<cv T2*>(static_cast<cv void*>(expression)）。
       当"T2's alignment is not stricter than T1's"，转换回的指针是可以yield原始值。
    8. T1类型的左值可以转换为T2类型的引用，转换后的结果是引用原始对象的左值。
    9. 指向T1某个成员函数的指针可以被转换为指向T2的某个成员函数的指针，转换后的指针是不安全的，但是转换回的指针是安全的。
    10. 指向T1某个成员变量的指针可以被转换为指向T2的某个成员变量的指针。
        转换后的指针是不安全的，但是如果"T2's alignment is not stricter than T1's"，转换回的指针可以yield原始值。
    */

    std::cout << "测试指针转整数: \n";
    {
        int i = 1;
        std::uintptr_t p1 = reinterpret_cast<std::uintptr_t>(&i);
        std::cout << "The value of &i is 0x" << std::hex << p1 << '\n';
    }

    std::cout << "测试函数指针转void*: \n";
    {
        void(*fp1)() = reinterpret_cast<void(*)()>(test_func);
        int(*fp2)() = reinterpret_cast<int(*)()>(fp1);
        std::cout << "fp2(): " << std::dec << fp2() << '\n';
    }

    std::cout << "测试T1类型的左值转换为T2类型的引用: \n";
    {
        int i = 1;
        reinterpret_cast<unsigned int&>(i) = 2;
        std::cout << "i: " << i << '\n';
    }

    std::cout << "测试T1类型的左值转换为T2类型的引用: \n";
    {
        int i = 32;
        unsigned char* p = reinterpret_cast<unsigned char*>(&i);

        printf("p[0] = %x\n", p[0]);
        printf("\\x7 = %x\n", '\x7');

        if(p[0] == '\x20')
            std::cout << "This system is little-endian\n";
        else
            std::cout << "This system is big-endian\n";

        std::cout << "hex_str: " << to_hex(p) << std::endl; // Output: 0x20 (32的十六进制表示)，说明复制了int的比特位到char*
    }
}


int TestDifferenceBetween_reinterpret_cast_And_static_cast() {
    /* 
    reinterpret_cast和static_cast的区别在于多重继承。

    比如下面的例子，打印出来的前两个地址是相同的，而static_cast转换后的地址偏移了4个字节。
    这是因为static_cast计算了父子类指针转换的偏移量，并将之转换到正确的地址，而reinterpret_cast却不会做这一层转换。
    */

    class A {
        public:
        int m_a;
    };
    
    class B {
        public:
        int m_b;
    };
    
    class C : public A, public B {};

    C c;
    printf("%p, %p, %p", &c, reinterpret_cast<B*>(&c), static_cast<B*>(&c));
}

int main(int argc, char** argv) {
    test_decorator(TestCastBasicNumericTypes, "TestCastBasicNumericTypes")();
    test_decorator(TestCastPolymorphicTypePointers, "TestCastPolymorphicTypePointers")();
    test_decorator(Test_static_cast, "Test_static_cast")();
    test_decorator(Test_dynamic_cast, "Test_dynamic_cast")();
    test_decorator(Test_const_cast, "Test_const_cast")();
    test_decorator(Test_reinterpret_cast, "Test_reinterpret_cast")();
    test_decorator(TestDifferenceBetween_reinterpret_cast_And_static_cast, "TestDifferenceBetween_reinterpret_cast_And_static_cast")();
}