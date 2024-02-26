#include "test.h"
#include "table.h"

void Test::print_block(const block::BlockArr& arr) {
    std::cout << "╔═";
    for(auto col : arr[0]) {
        std::cout << "══";
    }
    std::cout << "═╗" << std::endl;
    for(auto row: arr) {
        std::cout << "║ ";
        for(auto col: row) {
            if(col == 0) {
                std::cout << "  ";
            } else {
                std::cout << "██";
            }
        }
        std::cout << " ║" << std::endl;
    }
    std::cout << "╚═";
    for(auto col : arr[0]) {
        std::cout << "══";
    }
    std::cout << "═╝" << std::endl;
}

void Test::print_map(const std::vector<std::vector<int>>& map) {
    std::cout << "╔═";
    for(auto col : map[0]) {
        std::cout << "══";
    }
    std::cout << "═╗" << std::endl;
    for(auto row: map) {
        std::cout << "║ ";
        for(auto col: row) {
            if(col == 0) {
                std::cout << "  ";
            } else {
                std::cout << "██";
            }
        }
        std::cout << " ║" << std::endl;
    }
    std::cout << "╚═";
    for(auto col : map[0]) {
        std::cout << "══";
    }
    std::cout << "═╝" << std::endl;
}

Test::~Test() {
    std::cout << GREEN << "All Tests Passed!" << std::endl;
}

void Test::block_test() {
    Block long_stick(BlockType::LONG_STICK, 0, 0);
    Block stick(BlockType::STICK, 0, 0);
    Block box(BlockType::BOX, 0, 0);
    Block stair_left(BlockType::STAIR_LEFT, 0, 0);
    Block stair_right(BlockType::STAIR_RIGHT, 0, 0);
    Block stair(BlockType::STAIR, 0, 0);
    Block corner_left(BlockType::CORNER_LEFT, 0, 0);
    Block corner_right(BlockType::CORNER_RIGHT, 0, 0);

    // 样式测试
    print_block(long_stick.arr());
    print_block(stick.arr());
    print_block(box.arr());
    print_block(stair_left.arr());
    print_block(stair_right.arr());
    print_block(stair.arr());
    print_block(corner_left.arr());
    print_block(corner_right.arr());

    // 单元测试
    CHECK_EQUAL(long_stick.x(), 0);
    CHECK_EQUAL(long_stick.y(), 0);

    CHECK_EQUAL(long_stick.bottom(), 1);
    CHECK_EQUAL(long_stick.left(), 0);
    CHECK_EQUAL(long_stick.right(), 3);
    CHECK_EQUAL(long_stick.top(), 1);

    long_stick.rotate();

    CHECK_EQUAL(long_stick.x(), 0);
    CHECK_EQUAL(long_stick.y(), 0);

    CHECK_EQUAL(long_stick.bottom(), 3);
    CHECK_EQUAL(long_stick.left(), 2);
    CHECK_EQUAL(long_stick.right(), 2);
    CHECK_EQUAL(long_stick.top(), 0);

    long_stick.move(2, 3);

    CHECK_EQUAL(long_stick.x(), 2);
    CHECK_EQUAL(long_stick.y(), 3);

    CHECK_EQUAL(long_stick.bottom(), 6);
    CHECK_EQUAL(long_stick.left(), 4);
    CHECK_EQUAL(long_stick.right(), 4);
    CHECK_EQUAL(long_stick.top(), 3);

    long_stick.rotate();

    CHECK_EQUAL(long_stick.bottom(), 5);
    CHECK_EQUAL(long_stick.left(), 2);
    CHECK_EQUAL(long_stick.right(), 5);
    CHECK_EQUAL(long_stick.top(), 5);

    long_stick.rotate();

    CHECK_EQUAL(long_stick.bottom(), 6);
    CHECK_EQUAL(long_stick.left(), 3);
    CHECK_EQUAL(long_stick.right(), 3);
    CHECK_EQUAL(long_stick.top(), 3);

    long_stick.rotate();

    CHECK_EQUAL(long_stick.bottom(), 4);
    CHECK_EQUAL(long_stick.left(), 2);
    CHECK_EQUAL(long_stick.right(), 5);
    CHECK_EQUAL(long_stick.top(), 4);

    std::cout << GREEN << "block_test() Passed!" << RESET << std::endl;
}

void Test::table_test() {

}