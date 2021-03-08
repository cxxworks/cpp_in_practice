#ifndef STRING_H
#define STRING_H

#include <sstream>
#include <iostream>
#include <cstring>
#include <string>

class String {
public:
    explicit String()
        : data_(nullptr) {
        std::cout << "String's default constructor is called." << std::endl;
    }

    explicit String(const char *chars)
        : data_(nullptr) {
        std::cout << "String's constructor is called." << std::endl;
        reallocate(chars);
    }

    explicit String(const std::string &str)
        : data_(nullptr) {
        std::cout << "String's constructor is called." << std::endl;
        reallocate(str.data());
    }

    String(const String& other) {
        std::cout << "String's copy constructor is called." << std::endl;
        reallocate(other.data_);
    }

    String(String&& other) {
        std::cout << "String's move constructor is called." << std::endl;
        deallocate();
        data_ = other.data_;
        other.data_ = nullptr;
    }

    String& operator=(const String& other) {
        std::cout << "String's copy assignment operator is called." << std::endl;
        if (this != &other) {
            reallocate(other.data_);
        }
        return *this;
    }

    String& operator=(String&& other) noexcept {
        std::cout << "String's move assignment operator is called." << std::endl;
        if (this != &other) {
            deallocate();
            data_ = other.data_;
            other.data_= nullptr;
        }
        return *this;
    }

    ~String() {
        std::cout << "String's deconstructor is called." << std::endl;
        deallocate();
    }

    size_t len() const {
        return strlen(data_);
    }

    const char* data() const {
        return data_;
    }

    char* mutable_data() {
        return data_;
    }

private:
    void reallocate(const char *chars) {
        // std::cout << "String's reallocate is called." << std::endl;
        deallocate();

        const size_t chars_len = strlen(chars);
        data_ = new char[chars_len];
        memcpy(data_, chars, chars_len);
    }

    void deallocate() {
        if (data_ != nullptr) {
            delete[] data_;
        }
    }

private:
    char *data_ = nullptr;
};


inline std::ostream& operator<<(std::ostream& os, const String& str) {
    return os << str.data();
}

#endif