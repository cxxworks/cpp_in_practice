#include <iostream>
#include <vector>
#include <initializer_list>
#include <assert.h>
#include "test_util.h"

template <typename T>
class List {
public:
    List() = default;

    List(std::initializer_list<T>&& il)
        : v_(il) {
        std::cout << "List's constructor is called." << std::endl;
        Print();
    }

    List<T>& operator=(std::initializer_list<T> && il){
        v_ = il;
        std::cout << "List's move assignment operator is called." << std::endl;
        return *this;
    }

protected:
    void Print() {
        std::cout << "values in the list: " << std::endl;
        for (auto iter = v_.begin(); iter != v_.end(); iter++) {
            std::cout << *iter << " ";
        }
        std::cout << std::endl;
    }

private:
    std::vector<T> v_;
};

template <typename T>
void tmp_fn(T) {

}

template <typename T>
void tmp_fn2(std::initializer_list<T>&& il) {

}

int Test1() {
    List<int> l1({1, 2, 3});
    List<int> l2 = {4, 5, 6};
    List<int> l3;
    l3 = {7, 8, 9};

}

int Test2() {
    std::initializer_list<int> il = {1, 2, 3};
    tmp_fn(il);
    // tmp_fn({1, 2, 3}); // 因为`{1, 2, 3}`无类型，无法推导T
}

int Test3() {    
    tmp_fn2({1, 2, 3});
}

int Test4() {    
    for (auto x : {1, 2, 3}) {}
}

int Test5() {    
    assert(1 == 2);
    std::initializer_list<int> il = {1, 2, 3};
    
    std::cout << "il.size(): " << il.size() << std::endl;

    std::cout << "values in il: \n";
    for (std::initializer_list<int>::iterator iter = il.begin(); iter != il.end(); iter++) {
        std::cout << *iter << " ";
    }
    std::cout << '\n';

    std::cout << typeid(std::initializer_list<int>::value_type).name() << std::endl;
    std::initializer_list<int>::reference i = *il.begin();
}

int main(int arvc, char **argv) {
    test_decorator(Test1, "Test1")();
    test_decorator(Test2, "Test2")();
    test_decorator(Test3, "Test3")();
    test_decorator(Test4, "Test4")();
    test_decorator(Test5, "Test5")();
    return 0;
}