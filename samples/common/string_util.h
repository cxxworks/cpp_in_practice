#ifndef STRING_UTIL_H
#define STRING_UTIL_H

#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <iomanip>

std::string to_hex(unsigned char* data) {
    size_t len = strlen(reinterpret_cast<char*>(data));
    std::stringstream ss;
    ss << "0x";
    ss << std::uppercase << std::hex << std::setfill('0');
    for (int i = 0; i < len; i++) {
        ss << std::setw(2) << static_cast<unsigned>(data[i]);
    }
    return ss.str();
}

#endif