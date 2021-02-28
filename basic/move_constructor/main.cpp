#include <iostream>

using namespace std;


class FloatNumber
{
public:
    explicit FloatNumber(float v)
     : value_(new float(v))
    {
        std::cout << "FloatNumber's constructor has called." << std::endl;
    }

    FloatNumber(const FloatNumber& other)
    {
        value_ = new float(*other.value_);
        std::cout << "FloatNumber's copy constructor has called." << std::endl;
    }

    FloatNumber(FloatNumber&& other)
    {
        value_ = other.value_;
        other.value_= nullptr;
        
        std::cout << "FloatNumber's move constructor has called." << std::endl;
    }

    FloatNumber& operator=(const FloatNumber& other)
    {
        *value_ = *other.value_;

        std::cout << "FloatNumber's copy assignment operator has called." << std::endl;

        return *this;
    }

    FloatNumber& operator=(FloatNumber&& other)
    {
        if (value_ != nullptr)
        {
            delete value_;
        }
        
        value_ = other.value_;
        other.value_= nullptr;

        std::cout << "FloatNumber's move assignment operator has called." << std::endl;

        return *this;
    }

    FloatNumber& operator*=(const FloatNumber& other)
    {
        *value_ += *other.value_;

        std::cout << "FloatNumber's move assignment operator has called." << std::endl;

        return *this;
    }

    ~FloatNumber()
    {
        std::cout << "pointer to value: " << value_ << std::endl;
        
        if (value_ != nullptr)
        {
            delete value_;
        }
        std::cout << "FloatNumber's deconstructor has called." << std::endl;
    }

    float get_value() const
    {
        return *value_;
    }

private:
    float *value_;
};


inline FloatNumber operator*(const FloatNumber& lv, const FloatNumber& rv)
{
    std::cout << "operator* has called." << std::endl;
    return FloatNumber(lv.get_value() * rv.get_value());
}


int main(int argc, char **argv)
{
    FloatNumber a(1);
    std::cout << "1 --------------" << std::endl;
    
    FloatNumber b(a);
    std::cout << "2 --------------" << std::endl;

    FloatNumber c = a;
    std::cout << "3 --------------" << std::endl;

    FloatNumber d(3);
    d = FloatNumber(4);
    std::cout << "4 --------------" << std::endl;

    FloatNumber e = std::move(a);
    std::cout << "5 --------------" << std::endl;

    FloatNumber f = e * b;
    std::cout << "6 --------------" << std::endl;

}


// g++ -o main main.cpp -std=c++11
// g++ -o main main.cpp -std=c++11 -fno-elide-constructors