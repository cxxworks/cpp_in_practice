/* 
Notes:


Reference:
[1] https://en.cppreference.com/w/cpp/memory/unique_ptr
[2] https://en.cppreference.com/w/cpp/memory/shared_ptr
 */

#include <iostream>
#include <memory>
#include <cassert>
#include <vector>
#include "mock_floatnumber.h"
#include "mock_rect.h"
#include "mock_duck.h"
// #include "mock_polymorphism.h"
#include "test_util.h"

int TestUniquePtr() {
    std::cout << "测试构造: \n";
    {
        std::unique_ptr<FloatNumber> p = std::unique_ptr<FloatNumber>(new FloatNumber(3.1415926));
        std::cout << "p->value(): " << p->value() << std::endl;

        std::unique_ptr<FloatNumber> p1(new FloatNumber(3.1415926));
        // std::unique_ptr<FloatNumber> new_p1(p1); // 错误: unique_ptr不允许拷贝构造
        // std::unique_ptr<FloatNumber> new_p1 = p1; // 错误: unique_ptr不允许左值的赋值操作
        std::unique_ptr<FloatNumber> new_p1(std::move(p1)); // 正确: 允许通过移动构造的方式转移所有权
    }

    std::cout << "测试swap方法: \n"; 
    {
        std::unique_ptr<FloatNumber> p = std::make_unique<FloatNumber>(3.0);  // 注意: std::make_unique是C++14中的特性
        std::unique_ptr<FloatNumber> p1 = std::make_unique<FloatNumber>(5.0);

        FloatNumber* ptr = p.release();
        std::cout << "*ptr: " << *ptr << std::endl;
        assert(!p);

        p1.reset();
        assert(!p1);
    }

    std::cout << "测试reset和release方法: \n";
    {
        std::unique_ptr<FloatNumber> p = std::make_unique<FloatNumber>(3.0);
        std::unique_ptr<FloatNumber> p1 = std::make_unique<FloatNumber>(5.0);

        FloatNumber* ptr = p.release();
        std::cout << "*ptr: " << *ptr << std::endl;
        assert(!p);

        p1.reset();
        assert(!p1);
    }

    std::cout << "测试临时右值移动: \n";
    {
        auto create_floatnumber = [](float v) -> std::unique_ptr<FloatNumber> {
            std::unique_ptr<FloatNumber> tmp(new FloatNumber(v));
            return tmp;
        };

        std::unique_ptr<FloatNumber> p = create_floatnumber(3.0); // create_floatnumber返回的临时右值可以移动到ptr3中
        p = create_floatnumber(4.0); // create_floatnumber返回的临时右值可以移动到ptr3中
        std::unique_ptr<FloatNumber> p1 = create_floatnumber(5.0);
    }
    
    std::cout << "测试作为参数传递: \n";
    {
        auto tmp_fn1 = [](std::unique_ptr<Duck> p) {
            p->Fly();
        };

        auto tmp_fn2 = [](const std::unique_ptr<Duck>& p) {
            p->Fly();
        };

        auto tmp_fn3 = [](std::unique_ptr<Duck>&& p) {
            p->Fly();
        };

        auto tmp_fn4 = [](const std::unique_ptr<Anatidae>& p) {
            p->Fly();
        };

        std::unique_ptr<Duck> p(new Duck());
        // tmp_fn1(p); // 错误: 按值传递参数，unique_ptr不允许拷贝构造
        tmp_fn1(std::move(p));
        tmp_fn1(std::make_unique<Duck>());

        tmp_fn2(std::make_unique<Duck>());
        std::unique_ptr<Duck> p2(new Duck());
        tmp_fn2(p2);

        tmp_fn3(std::make_unique<Duck>());
        // tmp_fn4(std::make_shared<Duck>()); // 错误: 参数不匹配，无法传递std::unique_ptr<Dock>， 通过类型转换后可以吗？

        LetAvesInstanceFly(std::make_unique<Duck>()); // 正确: 可以通过模板函数
    }

    std::cout << "测试多态和容器: \n";
    {
        std::vector<std::unique_ptr<Aves>> v;  // unique_ptr can be stored in a container

        v.push_back(std::make_unique<Anatidae>());
        v.push_back(std::make_unique<Duck>());

        // iterate the vector
        for(auto& p: v) {
            p->Fly(); // virtual dispatch
        }

        // reference the first item
        auto& p1 = v[0];
        const auto& p2 = v[0];
    }

    std::cout << "测试lambda-expression删除器: \n";
    {

        auto DuckDeleter = [](Duck* ptr){
            std::cout << "deleting from a deleter\n";
            delete ptr;
        };

        using DerivedBUPtr = std::unique_ptr<Duck, std::function<void(Duck*)>>;
        DerivedBUPtr p(new Duck(), DuckDeleter);
        
        using DerivedBUPtr2 = std::unique_ptr<Duck, decltype(DuckDeleter)>;
        DerivedBUPtr2 p2(new Duck(), DuckDeleter);

        DerivedBUPtr p3 = std::make_unique<Duck>();
    }

    std::cout << "测试Functor删除器: \n";
    {
        class DuckDeleter {
        public:
            void operator()(Duck* ptr) const {
                std::cout << "deleting from a deleter\n";
                delete ptr;
            }
        };

        using DerivedBUPtr = std::unique_ptr<Duck, DuckDeleter>;
        DerivedBUPtr a(new Duck(), DuckDeleter());
    }
}

int TestSharedPtr() {
    using FloatRect = Rect<float>;
    std::shared_ptr<FloatRect> ptr(new FloatRect(1, 1, 5, 5));
    std::cout << "*ptr: " << *ptr << std::endl;
    std::cout << "ptr->get(): " << ptr.get() << std::endl;
    std::cout << "ptr.use_count(): " << ptr.use_count() << std::endl;
    std::cout << "ptr.unique(): " << ptr.unique() << std::endl;

    std::shared_ptr<FloatRect> ptr2(ptr);
    std::shared_ptr<FloatRect> ptr3 = ptr;
    std::cout << "ptr3.use_count(): " << ptr3.use_count() << std::endl;
    std::cout << "ptr.use_count(): " << ptr.use_count() << std::endl;
    std::cout << "ptr.unique(): " << ptr.unique() << std::endl;
    std::cout << "ptr.owner_before(ptr2): " << ptr.owner_before(ptr2) << std::endl;
    std::cout << "ptr3.owner_before(ptr2): " << ptr3.owner_before(ptr2) << std::endl;

    ptr2.reset();
    std::cout << "ptr.use_count(): " << ptr.use_count() << std::endl;

    ptr3 = std::make_shared<FloatRect>(30.0, 30.0, 5.0, 5.0);
    std::cout << "ptr.use_count(): " << ptr.use_count() << std::endl;

    ptr.swap(ptr3);
    std::cout << "*ptr: " << *ptr << std::endl;
    std::cout << "*ptr3: " << *ptr3 << std::endl;
    std::cout << "ptr.use_count(): " << ptr.use_count() << std::endl;
    std::cout << "ptr3.use_count(): " << ptr.use_count() << std::endl;

    std::cout << "Test polymorphism and stored in a container: \n";
    {
        std::vector<std::shared_ptr<Aves>> v;  // shared_ptr can be stored in a container

        // push some items
        v.push_back(std::make_shared<Anatidae>());
        v.push_back(std::make_shared<Duck>());

        // iterate the vector
        for(auto& p: v) {
            p->Fly(); // virtual dispatch
            p->Fly(); // virtual dispatch
        }

        // reference the first item
        auto p1 = v[0];
        auto& p2 = v[0];
        const auto& p3 = v[0];
    }

    std::cout << "测试作为参数传递: \n";
    {
        auto tmp_fn1 = [](std::shared_ptr<Duck> p) {
            p->Fly();
        };

        auto tmp_fn2 = [](const std::shared_ptr<Duck>& p) {
            p->Fly();
        };

        auto tmp_fn3 = [](std::shared_ptr<Duck>&& p) {
            p->Fly();
        };

        auto tmp_fn4 = [](const std::shared_ptr<Anatidae>& p) {
            p->Fly();
        };

        std::shared_ptr<Duck> p(new Duck());
        tmp_fn1(p);
        tmp_fn2(p);
        tmp_fn3(std::move(p));
        tmp_fn3(std::make_shared<Duck>());
        tmp_fn4(std::make_shared<Duck>()); // 正确: 可以从std::shared<Duck>转换到std::shared_ptr<Anatidae>

        tmp_fn2(std::make_unique<Duck>());
        tmp_fn3(std::make_unique<Duck>());
        
        LetAvesInstanceFly(std::make_shared<Duck>());
    }

    std::cout << "测试static_cast: \n";
    {
        std::shared_ptr<Anatidae> a = std::make_shared<Anatidae>();
        std::shared_ptr<Duck> d = std::make_shared<Duck>();

        std::shared_ptr<Anatidae> a2 = std::static_pointer_cast<Anatidae>(d);
        a2->Fly();
        std::shared_ptr<Duck> d2 = std::static_pointer_cast<Duck>(a2);
        d2->Fly();

        std::shared_ptr<Duck> d3 = std::static_pointer_cast<Duck>(a);
        d3->Fly();
    }

    std::cout << "测试dynamic_cast: \n";
    {
        std::shared_ptr<Anatidae> a = std::make_shared<Anatidae>();
        std::shared_ptr<Duck> d = std::make_shared<Duck>();
        
        std::shared_ptr<Anatidae> a2 = std::dynamic_pointer_cast<Anatidae>(d);
        a2->Fly();
        std::shared_ptr<Duck> d2 = std::dynamic_pointer_cast<Duck>(a2);
        d2->Fly();

        std::shared_ptr<Anatidae> d3 = std::dynamic_pointer_cast<Duck>(a);
        // d3->Fly();  // 错误: Segmentation fault (core dumped)
    }
}

int main(int argc, char** argv) {
    test_decorator(TestUniquePtr, "TestUniquePtr")();
    test_decorator(TestSharedPtr, "TestSharedPtr")();
}