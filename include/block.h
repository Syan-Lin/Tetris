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

namespace block {
    using BlockArr = std::array<std::array<int, 4>, 4>;
}

// 坐标:
//   ┌───> x
// y │
//   v
class Block {
public:
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

private:
    const BlockType type_;
    block::BlockArr block_;

    // 左上角为坐标原点
    int x_;
    int y_;
};