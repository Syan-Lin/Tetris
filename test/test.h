#pragma once
#include <iostream>

#define RED "\x1b[0;31m"
#define GREEN "\x1b[1;32m"
#define BLUE "\x1b[1;34m"
#define RESET "\x1b[0;m"

template<typename value>
void check_equal(int line, std::string str1, std::string str2, value val1, value val2) {
    if(val1 != val2) {
        std::cerr << RED << "expected " << BLUE << str1 << RED << " to be " << GREEN << val1
            << RED << " but get " << BLUE << val2 << RED << " at line " << line << RESET << std::endl;
        throw;
    }
}

#define CHECK_EQUAL(val1, val2) check_equal(__LINE__, #val1, #val2, val1, val2)