#ifndef TEST_UTIL_H
#define TEST_UTIL_H

#include <string>
#include <functional>
#include <iostream>
#include <sstream>

class AbcTest {
public:
    virtual void ExecuteTest() = 0;
    virtual void Test() = 0;
};

class BaseTest: public AbcTest {
public:
    BaseTest(const std::string& name)
        : name_(name) {}

    void ExecuteTest() override {
        std::cout << "<<< Test: " << name_ << " <<<" << std::endl;
        Test();
        std::cout << "<<< End of The Test Output <<<" << std::endl;
    }

private:
    std::string name_;
};

template<typename FuncRetType, typename... FuncArgs>
std::function<FuncRetType(FuncArgs... args)> test_decorator(FuncRetType(*p_func)(FuncArgs... args), 
    const std::string& name = std::string(), bool cal_cost_time = false) {

    auto wrapper = [&](FuncArgs... args) -> FuncRetType {
        std::cout << ">>> Start of the test: " << name << " >>>" << std::endl;
        FuncRetType result = (*p_func)(args...);
        std::cout << "<<< End of the test <<<\n" << std::endl;
        return result;
    };
    return wrapper;
}

#define GET_NAME_STR(stuff) #stuff

#define RUN_TEST(function) \
    { \
        test_decorator(function, GET_NAME_STR(function))(); \
    }

#endif