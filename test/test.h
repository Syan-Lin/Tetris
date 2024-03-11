#pragma once
#include <iostream>
#include <vector>
#include "block.h"
#include "table.h"

#define ANSI_RED "\x1b[0;31m"
#define ANSI_GREEN "\x1b[1;32m"
#define ANSI_BLUE "\x1b[1;34m"
#define RESET "\x1b[0;m"

template<typename value>
void check_equal(int line, std::string str1, std::string str2, value val1, value val2) {
    if(val1 != val2) {
        std::cerr << ANSI_RED << "expected " << ANSI_BLUE << str1 << ANSI_RED << " to be " << ANSI_GREEN << val1
            << ANSI_RED << " but get " << ANSI_BLUE << val2 << ANSI_RED << " at line " << line << RESET << std::endl;
        std::terminate();
    }
}

#define CHECK_EQUAL(val1, val2) check_equal(__LINE__, #val1, #val2, val1, val2)

class Test {
public:
    ~Test();
    void table_test();
    void block_test();

private:
    void print_map(const Table::TableArr& map);
    void print_block(const block::BlockArr& arr);
};