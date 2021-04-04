/* 
 * Notes:
 * 阻止non-heap对象的产生的方法：
 * 1. 将operator new和operator delete声明为private.
 */

#include <iostream>
#include <stdio.h>
#include "test_util.h"

/* 
@brief 将operator new和operator delete声明为private, 该类就不能在heap上生成。
 */
class ClassCantCreateOnHeap {
public:
    ClassCantCreateOnHeap() = default;
    ~ClassCantCreateOnHeap() = default;

private:
    static void *operator new(size_t size);
    static void operator delete(void *ptr) noexcept;

    static void *operator new[](size_t size);
    static void operator delete[](void *ptr) noexcept;
};

int Test_ClassCantCreateOnHeap() {
    // ClassCantCreateOnHeap *p = new ClassCantCreateOnHeap();  // 错误
    // delete p;  // 错误
    ClassCantCreateOnHeap obj;  // 正确
}

int main(int argc, char** argv) {
    test_decorator(Test_ClassCantCreateOnHeap, "Test_ClassCantCreateOnHeap")();
}