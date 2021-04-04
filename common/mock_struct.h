#ifndef MOCK_STRUCT_H
#define MOCK_STRUCT_H

#include <iostream>
#include <string>

struct user_t {
    std::string id;
    std::string name;
    uint8_t age;
    std::string gender;
    std::string address;
};


struct log_record_t {
    user_t user;
    std::string msg;
    uint64_t timestamp;
};

#endif