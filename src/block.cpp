#include "block.h"

namespace block {

// ████████
const BlockArr long_stick = {
    {{0, 0, 0, 0},
    {1, 1, 1, 1},
    {0, 0, 0, 0},
    {0, 0, 0, 0}}
};
// ██████
const BlockArr stick = {
    {{0, 0, 0, 0},
    {1, 1, 1, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}}
};
// ████
// ████
const BlockArr box = {
    {{0, 0, 0, 0},
    {0, 1, 1, 0},
    {0, 1, 1, 0},
    {0, 0, 0, 0}}
};
// ██
// ██████
const BlockArr corner_left = {
    {{0, 0, 0, 0},
    {1, 0, 0, 0},
    {1, 1, 1, 0},
    {0, 0, 0, 0}}
};
//     ██
// ██████
const BlockArr corner_right = {
    {{0, 0, 0, 0},
    {0, 0, 1, 0},
    {1, 1, 1, 0},
    {0, 0, 0, 0}}
};
//   ██
// ██████
const BlockArr stair = {
    {{0, 0, 0, 0},
    {0, 1, 0, 0},
    {1, 1, 1, 0},
    {0, 0, 0, 0}}
};
// ████
//   ████
const BlockArr stair_left = {
    {{0, 0, 0, 0},
    {1, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 0, 0}}
};
//   ████
// ████
const BlockArr stair_right = {
    {{0, 0, 0, 0},
    {0, 1, 1, 0},
    {1, 1, 0, 0},
    {0, 0, 0, 0}}
};

} // namespace block

Block::Block(const BlockType type, int x, int y): type_(type), x_(x), y_(y) {
    switch(type) {
        case BlockType::LONG_STICK:    block_ = block::long_stick;     break;
        case BlockType::STICK:         block_ = block::stick;          break;
        case BlockType::BOX:           block_ = block::box;            break;
        case BlockType::STAIR_LEFT:    block_ = block::stair_left;     break;
        case BlockType::STAIR_RIGHT:   block_ = block::stair_right;    break;
        case BlockType::STAIR:         block_ = block::stair;          break;
        case BlockType::CORNER_LEFT:   block_ = block::corner_left;    break;
        case BlockType::CORNER_RIGHT:  block_ = block::corner_right;   break;
        default: throw;
    }
}

void Block::rotate() {
    block::BlockArr after_rotate;
    for(size_t i = 0; i < block_.size(); i++) {
        for(size_t j = 0; j < block_.size(); j++) {
            after_rotate[j][block_.size() - 1 - i] = block_[i][j];
        }
    }
    block_ = after_rotate;
}

void Block::move(int x, int y) {
    x_ += x;
    y_ += y;
}

int Block::bottom() {
    int btm = 0;
    for(size_t i = 0; i < block_.size(); i++) {
        for(size_t j = 0; j < block_.size(); j++) {
            if(block_[i][j] == 1 && i > btm) {
                btm = i;
            }
        }
    }
    return y_ + btm;
}

int Block::left() {
    int lft = 4;
    for(size_t i = 0; i < block_.size(); i++) {
        for(size_t j = 0; j < block_.size(); j++) {
            if(block_[i][j] == 1 && j < lft) {
                lft = j;
            }
        }
    }
    return x_ + lft;
}

int Block::right() {
    int rgt = 0;
    for(size_t i = 0; i < block_.size(); i++) {
        for(size_t j = 0; j < block_.size(); j++) {
            if(block_[i][j] == 1 && j > rgt) {
                rgt = j;
            }
        }
    }
    return x_ + rgt;
}

int Block::top() {
    int tp = 4;
    for(size_t i = 0; i < block_.size(); i++) {
        for(size_t j = 0; j < block_.size(); j++) {
            if(block_[i][j] == 1 && i < tp) {
                tp = i;
            }
        }
    }
    return y_ + tp;
}

int Block::x() {
    return x_;
}

int Block::y() {
    return y_;
}

block::BlockArr Block::arr() {
    return block_;
}