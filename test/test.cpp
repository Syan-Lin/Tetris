#include "test.h"

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

void Test::print_map(const std::vector<std::vector<Color>>& map) {
    std::cout << "╔═";
    for(auto col : map[0]) {
        std::cout << "══";
    }
    std::cout << "═╗" << std::endl;
    for(auto row: map) {
        std::cout << "║ ";
        for(auto col: row) {
            if(col == Color::NONE) {
                std::cout << "  ";
            } else if((int)col <= 6){
                std::cout << "██";
            } else {
                std::cout << "▫️▫️";
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

void print(const std::vector<std::vector<Color>>& map) {
    for(auto row: map) {
        for(auto col: row) {
            std::cout << int(col) << " ";
        }
        std::cout << std::endl;
    }
}

Test::~Test() {
    std::cout << ANSI_GREEN << "All Tests Passed!" << std::endl;
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

    std::cout << ANSI_GREEN << "block_test() Passed!" << RESET << std::endl;
}

void Test::table_test() {
    Table::TableArr map = {
        {(Color)0, (Color)0, (Color)0, (Color)0, (Color)0},
        {(Color)0, (Color)0, (Color)0, (Color)0, (Color)0},
        {(Color)0, (Color)0, (Color)0, (Color)0, (Color)0},
        {(Color)0, (Color)0, (Color)0, (Color)0, (Color)0},

        {(Color)0, (Color)0, (Color)0, (Color)0, (Color)0},
        {(Color)0, (Color)0, (Color)0, (Color)0, (Color)0},
        {(Color)0, (Color)0, (Color)0, (Color)0, (Color)0},
        {(Color)0, (Color)0, (Color)0, (Color)0, (Color)0},
        {(Color)1, (Color)1, (Color)1, (Color)1, (Color)1},
        {(Color)1, (Color)0, (Color)1, (Color)1, (Color)1},
    };
    Table table = Table(5 ,6, map);
    table.spawn(Block(BlockType::STAIR_LEFT, 0, 0));
    CHECK_EQUAL((int)table.touch(table.block_), (int)TouchType::NONE);
    print_map(table.map());

    table.spawn(Block(BlockType::STAIR_RIGHT, -1, 0));
    CHECK_EQUAL((int)table.touch(table.block_), (int)TouchType::BORDER);
    print_map(table.map());

    table.spawn(Block(BlockType::STICK, 1, 5));
    CHECK_EQUAL((int)table.touch(table.block_), (int)TouchType::NONE);
    print_map(table.map());

    table.spawn(Block(BlockType::LONG_STICK, 1, 6));
    CHECK_EQUAL((int)table.touch(table.block_), (int)TouchType::NONE);
    print_map(table.map());

    table.spawn(Block(BlockType::STAIR, 1, 10));
    CHECK_EQUAL((int)table.touch(table.block_), (int)TouchType::BOTTOM);
    print_map(table.map());

    table.remove_line();
    print_map(table.map());

    table.spawn(Block(BlockType::BOX, 1, 1));
    print_map(table.map());
    CHECK_EQUAL(table.update(Input::LEFT), false);
    print_map(table.map());
    CHECK_EQUAL(table.update(Input::LEFT), false);
    print_map(table.map());
    CHECK_EQUAL(table.update(Input::LEFT), false);
    print_map(table.map());

    CHECK_EQUAL(table.update(Input::RIGHT), false);
    print_map(table.map());
    CHECK_EQUAL(table.update(Input::RIGHT), false);
    print_map(table.map());
    CHECK_EQUAL(table.update(Input::RIGHT), false);
    print_map(table.map());
    CHECK_EQUAL(table.update(Input::RIGHT), false);
    print_map(table.map());

    CHECK_EQUAL(table.update(Input::DOWN), false);
    print_map(table.map());
    CHECK_EQUAL(table.update(Input::DOWN), false);
    print_map(table.map());
    CHECK_EQUAL(table.update(Input::DOWN), false);
    print_map(table.map());
    CHECK_EQUAL(table.update(Input::DOWN), false);
    print_map(table.map());
    CHECK_EQUAL(table.update(Input::DOWN), false);
    print_map(table.map());
    CHECK_EQUAL(table.update(Input::DOWN), true);
    print_map(table.map());

    print_map(table.map());
    table.spawn(Block(BlockType::CORNER_LEFT, 0, 6));
    print_map(table.map());
    table.rotate();
    print_map(table.map());
    CHECK_EQUAL(table.update(Input::RIGHT), false);
    CHECK_EQUAL((int)table.touch(table.block_), (int)TouchType::NONE);
    CHECK_EQUAL(table.update(Input::DOWN), true);
    table.remove_line();
    print_map(table.map());

    table.spawn(Block(BlockType::CORNER_RIGHT, 0, 3));
    table.set_block();
    print_map(table.map());
    CHECK_EQUAL(table.game_loss(), false);
    table.spawn(Block(BlockType::STAIR_LEFT, 0, 2));
    table.set_block();
    print_map(table.map());
    CHECK_EQUAL(table.game_loss(), true);
}