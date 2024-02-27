#pragma once

#include <array>
#include <iostream>

enum class BlockType {
    LONG_STICK,
    STICK,
    BOX,
    STAIR_LEFT,
    STAIR_RIGHT,
    STAIR,
    CORNER_LEFT,
    CORNER_RIGHT
};

enum class Color {
    NONE     = 0,
    RED      = 1,
    GREEN    = 2,
    YELLOW   = 3,
    BLUE     = 4,
    PURPLE   = 5,
    CYAN     = 6,
    RED_S    = 7,
    GREEN_S  = 8,
    YELLOW_S = 9,
    BLUE_S   = 10,
    PURPLE_S = 11,
    CYAN_S   = 12
};

namespace block {
    using BlockArr = std::array<std::array<int, 4>, 4>;
}

// 坐标:
//   ┌───> x
// y │
//   v
class Block {
public:
    Block();
    Block(const BlockType type, const Color color, int x, int y);
    Block(const BlockType type, int x, int y);

    // 顺时针旋转 90°
    void rotate();

    // 移动位置
    void move(int x, int y);

    // 最下方的坐标
    int bottom();
    // 最左边的坐标
    int left();
    // 最右边的坐标
    int right();
    // 最上方的坐标
    int top();

    int x();
    int y();
    block::BlockArr arr();
    Color color();

private:
    BlockType type_;
    block::BlockArr block_;
    Color color_;

    // 左上角为坐标原点
    int x_;
    int y_;
};