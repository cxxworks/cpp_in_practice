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
        data = new u_char[1];
    }

    Anatidae(const Anatidae& other) {
        std::cout << "Anatidae::Anatidae(const Anatidae& other)" << std::endl;
        data = new u_char[1];
    }

    Anatidae(Anatidae&& other) {
        std::cout << "Anatidae::Anatidae(Anatidae&& other)" << std::endl;
        data = other.data;
        other.data = nullptr;
    }

    virtual ~Anatidae() {
        std::cout << "Anatidae::~Anatidae" << std::endl;
        delete[] data;
    }

    virtual void Fly() override {
        std::cout << "Anatidae::Fly" << std::endl;
        data[0] = '1';
    }

    void Eat() override {
        std::cout << "Anatidae::Eat" << std::endl;
        data[0] = '2';
    }

private:
    u_char* data = nullptr;
};

/* 
@brief 鸭类
 */
class Duck : public Anatidae {
public:
    Duck()
     : Anatidae() {
        std::cout << "Duck::Duck" << std::endl;
        duck_data = new u_char[10];
    }

    Duck(const Duck& other) {
        std::cout << "Duck::Duck(const Duck& other)" << std::endl;
        duck_data = new u_char[10];
    }

    Duck(Duck&& other) {
        std::cout << "Duck::Duck(Duck&& other)" << std::endl;
    }

    virtual ~Duck() {
        std::cout << "Duck::~Duck" << std::endl;
        delete[] duck_data;
    }

    void Fly() override {
        std::cout << "Duck::Fly" << std::endl;
        duck_data[9] = '3';
    }

private:
    u_char* duck_data = nullptr;
};


template <typename T>
void LetBirdInstanceFly(T&& obj) {
    obj->Fly();
}

#endif