#ifndef MOCK_DUCK_H
#define MOCK_DUCK_H

#include <iostream>

/* 
@brief 鸟类
 */
class Bird {
public:
    virtual void Eat() = 0;
    virtual void Fly() = 0;
};

/* 
@brief 鸭科类
 */
class Anatidae : public Bird {
public:
    Anatidae() {
        std::cout << "Anatidae::Anatidae" << std::endl;
    }

    Anatidae(const Anatidae& other) {
        std::cout << "Anatidae::Anatidae(const Anatidae& other)" << std::endl;
    }

    Anatidae(Anatidae&& other) {
        std::cout << "Anatidae::Anatidae(Anatidae&& other)" << std::endl;
    }

    virtual ~Anatidae() {
        std::cout << "Anatidae::~Anatidae" << std::endl;
    }

    virtual void Fly() override {
        std::cout << "Anatidae::Fly" << std::endl;
    }

    void Eat() override {
        std::cout << "Anatidae::Eat" << std::endl;
    }
};

/* 
@brief 鸭类
 */
class Duck : public Anatidae {
public:
    Duck()
     : Anatidae() {
        std::cout << "Duck::Duck" << std::endl;
    }

    Duck(const Duck& other) {
        std::cout << "Duck::Duck(const Duck& other)" << std::endl;
    }

    Duck(Duck&& other) {
        std::cout << "Duck::Duck(Duck&& other)" << std::endl;
    }

    virtual ~Duck() {
        std::cout << "Duck::~Duck" << std::endl;
    }

    void Fly() override {
        std::cout << "Duck::Fly" << std::endl;
    }
};


template <typename T>
void LetBirdInstanceFly(T&& obj) {
    obj->Fly();
}

#endif