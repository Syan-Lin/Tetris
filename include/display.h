#pragma once
#include "table.h"

// 与 controller.h 循环引用，需要前向声明
enum class Difficulty;

class Display {
public:
    Display();

    // 绘制主菜单
    void main_menu(int select);

    // 绘制难度选择界面
    void difficulty(int select);

    // 打印分数信息
    void score_panel(int width, int score);

    // 打印难度信息
    void difficulty_panel(int width, Difficulty difficulty);

    // 打印下一个方块信息
    void next_panel(int width, Block block);

    // 打印操作信息
    void operation_panel(int width);

    // 绘制游戏棋盘
    void game_table(Table& table);

    // 游戏结束界面
    void game_over_panel(int width, int height, int select);

    // 游戏暂停界面
    void pause_panel(int width, int height);

    // 清空屏幕
    void clear();

private:

    // 颜色打印
    std::string with_color(std::string, Color color);

    // 工具函数
    void move_cursor(int line, int column);

private:
    int panel_width_;
    int window_width_;
    int menu_width_;
};