#include <string>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include "test_util.h"

int TestBasicMethodsOfString() {
    std::string str = "Hello World!";

    printf("str: %s\n", str.c_str());
    printf("str.size(): %lu\n", str.size());
    printf("str.length(): %lu\n", str.length());
    printf("str.capacity(): %lu\n", str.capacity());
}

int TestConversionBetweenStringAndChars() {
    std::string raw_str = "Hello World!";
    char raw_chars[13] = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!', '\0'};

    printf("1. std::string转char*:\n");
    {
        const char *ch_ptr = raw_str.data();
        printf("*ch_ptr: %s\n", ch_ptr);
    }

    printf("2. std::string转char*:\n");
    {
        const char *ch_ptr = raw_str.c_str();
        printf("*ch_ptr: %s\n", ch_ptr);
    }

    printf("3. std::string转char[]:\n");
    {
        const size_t str_len = raw_str.length();
        char chars[str_len + 1];
        raw_str.copy(chars, str_len, 0);
        *(chars + str_len) = '\0';
        printf("chars: %s\n", chars);
    }

    printf("4. char[]转std::string转:\n");
    {
        std::string str(raw_chars);
        std::string str2 = raw_chars;

        printf("str: %s\n", str.c_str());
        printf("str2: %s\n", str2.c_str());
    }
}

int main(int argc, char** argv) {
    test_decorator(TestBasicMethodsOfString, "TestBasicMethodsOfString")();
    test_decorator(TestConversionBetweenStringAndChars, "TestConversionBetweenStringAndChars")();
}