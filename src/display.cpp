#include "display.h"
#include "block.h"
#include "controler.h"
#include <string>

#define ANSI_RED "\x1b[31m"
#define ANSI_GREEN "\x1b[32m"
#define ANSI_YELLOW "\x1b[33m"
#define ANSI_BLUE "\x1b[34m"
#define ANSI_PURPLE "\x1b[35m"
#define ANSI_CYAN "\x1b[36m"
#define ANSI_RESET "\x1b[m"
#define ANSI_INVISIBLE "\x1b[?25l"

#ifdef _WIN32
#include <windows.h>
void terminal_init() {
    // 设置中文输出
    SetConsoleOutputCP(CP_UTF8);

    // 隐藏光标
    std::cout << ANSI_INVISIBLE << std::endl;
}
#endif

#ifdef linux
void terminal_init() {
    // 隐藏光标
    std::cout << ANSI_INVISIBLE << std::endl;
}
#endif

// 工具函数
void print_head(int width, std::string str, int str_width) {
    std::cout << "╔═";
    for(int i = 0; i < (width - str_width) / 2; i++) {
        std::cout << "═";
    }
    std::cout << str;
    for(int i = 0; i < (width - str_width) / 2; i++) {
        std::cout << "═";
    }
    if((width - str_width) % 2 == 1) {
        std::cout << "═";
    }
    std::cout << "═╗" << std::endl;
}

void print_tail(int width) {
    std::cout << "╚═";
    for(int i = 0; i < width; i++) {
        std::cout << "═";
    }
    std::cout << "═╝" << std::endl;
}

void print_middle(int width, std::string str, int str_width) {
    width += 2;
    std::cout << "║";
    for(int i = 0; i < (width - str_width) / 2; i++) {
        std::cout << " ";
    }
    std::cout << str;
    for(int i = 0; i < (width - str_width) / 2; i++) {
        std::cout << " ";
    }
    if((width - str_width) % 2 == 1) {
        std::cout << " ";
    }
    std::cout << "║" << std::endl;
}


Display::Display() {
    terminal_init();
    panel_width_ = 10;
    menu_width_ = 28;
    window_width_ = 14;
}

void Display::main_menu(int select) {
    move_cursor(1, 1);
    print_head(menu_width_, with_color("✨ 俄罗斯方块 ✨", Color::GREEN), 16);
    print_middle(menu_width_, "", 0);
    if(select == 0) {
        print_middle(menu_width_, with_color("1. 开始游戏", Color::GREEN), 11);
        print_middle(menu_width_, with_color("0. 退出游戏", Color::RED), 11);
    } else {
        print_middle(menu_width_, with_color("1. 开始游戏", Color::RED), 11);
        print_middle(menu_width_, with_color("0. 退出游戏", Color::GREEN), 11);
    }
    print_middle(menu_width_, "", 0);
    std::cout << "╚═════════════════════════v0.1═╝" << std::endl;
}

void Display::difficulty(int select) {
    move_cursor(1, 1);
    print_head(menu_width_, with_color("✨ 选择难度 ✨", Color::GREEN), 14);
    print_middle(menu_width_, "", 0);
    print_middle(menu_width_, (select == 1
                                    ? with_color("1. 简 单", Color::RED)
                                    : with_color("1. 简 单", Color::GREEN)), 8);
    print_middle(menu_width_, (select == 2
                                    ? with_color("2. 中 等", Color::RED)
                                    : with_color("2. 中 等", Color::GREEN)), 8);
    print_middle(menu_width_, (select == 3
                                    ? with_color("3. 困 难", Color::RED)
                                    : with_color("3. 困 难", Color::GREEN)), 8);
    print_middle(menu_width_, (select == 4
                                    ? with_color("4. 地 狱", Color::RED)
                                    : with_color("4. 地 狱", Color::GREEN)), 8);
    print_middle(menu_width_, "", 0);
    print_tail(menu_width_);
}

void Display::game_panel(
        Table& table,
        int score,
        Difficulty difficulty,
        Block block,
        bool game_over,
        int select) {
    game_table(table);
    score_panel(table, score);
    difficulty_panel(table, difficulty);
    next_panel(table, block);
    operation_panel(table);
    if(game_over) {
        game_over_panel(table, select);
    }
}

void Display::game_table(Table& table) {
    move_cursor(0, 0);
    auto map = table.map();
    int height = table.height();
    int width = table.width();

    print_head(width * 2, "", 0);

    for(int i = 0; i < height; i++) {
        std::cout << "║ ";
        for(int j = 0; j < width; j++) {
            if(map[i][j] == Color::NONE) {
                std::cout << "  ";
            } else {
                std::cout << with_color("██", map[i][j]);
            }
        }
        std::cout << " ║" << std::endl;
    }

    print_tail(width * 2);
}

void Display::score_panel(Table& table, int score) {
    int width = table.width();

    move_cursor(1, (width + 3) * 2);
    print_head(panel_width_, "得分", 4);

    move_cursor(2, (width + 3) * 2);
    std::string str = std::to_string(score);
    print_middle(panel_width_, str, str.length());

    move_cursor(3, (width + 3) * 2);
    print_tail(panel_width_);
}

void Display::difficulty_panel(Table& table, Difficulty difficulty) {
    using std::string, std::cout;
    int width = table.width();
    string str;
    switch(difficulty) {
        case Difficulty::EASY:
            str = "简单";
            break;
        case Difficulty::NORMAL:
            str = "中等";
            break;
        case Difficulty::HARD:
            str = "困难";
            break;
        case Difficulty::HELL:
            str = "地狱";
            break;
    }

    move_cursor(5, (width + 3) * 2);
    print_head(panel_width_, "难度", 4);

    move_cursor(6, (width + 3) * 2);
    print_middle(panel_width_, str, 4);

    move_cursor(7, (width + 3) * 2);
    print_tail(panel_width_);
}

void Display::next_panel(Table& table, Block block) {
    int width = table.width();
    int height = table.height();
    auto arr = block.arr();

    move_cursor(9, (width + 3) * 2);
    print_head(panel_width_, "下一个", 6);

    move_cursor(10, (width + 3) * 2);
    for(int i = 0; i < arr.size(); i++) {
        std::string str;
        for(int j = 0; j < arr[i].size(); j++) {
            if(arr[i][j] == 0) {
                str += "  ";
            } else {
                str += with_color("██", block.color());
            }
        }
        print_middle(panel_width_, str, 8);
        move_cursor(10 + i + 1, (width + 3) * 2);
    }
    print_tail(panel_width_);
}

void Display::operation_panel(Table& table) {
    int width = table.width();
    move_cursor(16, (width + 3) * 2);
    print_head(panel_width_, "操作", 4);

    move_cursor(17, (width + 3) * 2);
    print_middle(panel_width_, "W: 旋转", 7);

    move_cursor(18, (width + 3) * 2);
    print_middle(panel_width_, "A: 左移", 7);

    move_cursor(19, (width + 3) * 2);
    print_middle(panel_width_, "S: 下移", 7);

    move_cursor(20, (width + 3) * 2);
    print_middle(panel_width_, "D: 右移", 7);

    move_cursor(21, (width + 3) * 2);
    print_middle(panel_width_, "空格暂停", 8);

    move_cursor(22, (width + 3) * 2);
    print_tail(panel_width_);
}

void Display::game_over_panel(Table& table, int select) {
    int width = table.width();
    int height = table.height();
    int line = height / 2 - 1;
    int column = width - window_width_ / 2 + 1;

    move_cursor(line, column);
    print_head(window_width_, "游戏结束", 8);

    move_cursor(line + 1, column);
    print_middle(window_width_, (select == 0
                                ? with_color("重新开始", Color::RED)
                                : with_color("重新开始", Color::GREEN)), 8);

    move_cursor(line + 2, column);
    print_middle(window_width_, (select == 1
                                ? with_color("返回菜单", Color::RED)
                                : with_color("返回菜单", Color::GREEN)), 8);

    move_cursor(line + 3, column);
    print_tail(window_width_);
}

std::string Display::with_color(std::string str, Color color) {
    switch(color) {
        case Color::RED:
            return ANSI_RED + str + ANSI_RESET;
        case Color::GREEN:
            return ANSI_GREEN + str + ANSI_RESET;
        case Color::YELLOW:
            return ANSI_YELLOW + str + ANSI_RESET;
        case Color::BLUE:
            return ANSI_BLUE + str + ANSI_RESET;
        case Color::PURPLE:
            return ANSI_PURPLE + str + ANSI_RESET;
        case Color::CYAN:
            return ANSI_CYAN + str + ANSI_RESET;
        default:
            return str;
    }
}

void Display::move_cursor(int line, int column) {
    std::cout << "\x1b[" << line << ";" << column << "H";
}

void Display::clear() {
    std::cout << "\x1b[2J";
}