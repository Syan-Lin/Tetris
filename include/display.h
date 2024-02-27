#pragma once
#include "table.h"
#include "controler.h"

class Display {
public:
    Display();

    // 绘制主菜单
    void main_menu(int select);

    // 绘制难度选择界面
    void difficulty(int select);

    // 绘制游戏界面
    void game_panel(
        Table& table,
        int score,
        Difficulty difficulty,
        Block block,
        bool game_over,
        int select);

    // 清空屏幕
    void clear();

private:
    // 打印分数信息
    void score_panel(Table& table, int score);

    // 打印难度信息
    void difficulty_panel(Table& table, Difficulty difficulty);

    // 打印下一个方块信息
    void next_panel(Table& table, Block block);

    // 游戏结束界面
    void game_over_panel(Table& table, int select);

    // 打印操作信息
    void operation_panel(Table& table);

    // 绘制游戏棋盘
    void game_table(Table& table);

    // 颜色打印
    std::string with_color(std::string, Color color);

    // 工具函数
    void move_cursor(int line, int column);

private:
    int panel_width_;
    int window_width_;
    int menu_width_;
};