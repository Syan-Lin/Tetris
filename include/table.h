# pragma once

#include <vector>
#include <array>
#include "block.h"
#include "keyboard.h"

/* 游戏表盘:

Spawn Area: width * 4
Game Area:  width * height
╔════════════════════════╗
║                        ║
║       Spawn Area       ║
║                        ║
╠════════════════════════╣
║                        ║
║       Game Area        ║
║                        ║
╚════════════════════════╝

*/

class Test;

enum class TouchType {
    BORDER,
    BOTTOM,
    NONE
};

class Table {
    friend Test;
public:
    using TableArr = std::vector<std::vector<Color>>;

    Table(size_t width, size_t height);
    Table(size_t width, size_t height, TableArr map);

    // 生成一个方块
    void spawn(Block block);

    // 获取消除的行数
    int removed_lines();

    // 重置游戏棋盘
    void reset_map();

    // 检查游戏是否失败
    bool game_loss();

    // 更新棋盘状态, 返回方块是否触底
    bool update(Input input);

    // 旋转方块
    void rotate();

    // 获取游戏棋盘的矩阵（包含方块）
    TableArr map();

    // 获取游戏棋盘的宽度
    size_t width();

    // 获取游戏棋盘的高度
    size_t height();

private:
    // 水平方向移动方块
    void move_block(int x);

    // 方块下落, 返回是否还能继续下落
    bool gravity();

    // 将方块放置到棋盘
    void set_block();

    // 检查是否碰到边界或其他方块, 返回碰撞类型
    TouchType touch();

    // 消去满足要求的行, 返回消除的行数
    int remove_line();

    // 获取游戏棋盘的矩阵（包含方块和 Spawn Area）
    TableArr map_for_check();

private:
    size_t width_;
    size_t height_;
    size_t hidden_;
    size_t removed_line_;
    TableArr map_;
    Block block_;
};