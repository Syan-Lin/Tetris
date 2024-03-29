#include "table.h"
#include "block.h"
#include <sched.h>

Table::Table(size_t width, size_t height): width_(width), height_(height) {
    hidden_ = 4;
    removed_line_ = 0;
    map_ = TableArr(height + hidden_, std::vector<Color>(width, Color::NONE));
}

Table::Table(size_t width, size_t height, TableArr map)
        : width_(width), height_(height), map_(map) {
    hidden_ = 4;
    removed_line_ = 0;
    if(map.size() != height_ + hidden_ || map.at(0).size() != width_) {
        throw std::invalid_argument("Invalid map size");
    }
}

void Table::spawn(Block block) {
    block_ = block;
}

int Table::removed_lines() {
    int temp = removed_line_;
    removed_line_ = 0;
    return temp;
}

void Table::reset_map() {
    for(size_t i = 0; i < map_.size(); i++) {
        for(size_t j = 0; j < map_.at(0).size(); j++) {
            map_.at(i).at(j) = Color::NONE;
        }
    }
}

bool Table::game_loss() {
    for(size_t i = 0; i < hidden_; i++) {
        for(size_t j = 0; j < width_; j++) {
            if(map_.at(i).at(j) != Color::NONE) {
                return true;
            }
        }
    }
    return false;
}

bool Table::update(Input input) {
    switch(input) {
        case Input::LEFT:
            move_block(-1);
            break;
        case Input::RIGHT:
            move_block(1);
            break;
        case Input::ROTATE:
            rotate();
            break;
        case Input::DOWN:
            return gravity();
        default:
            break;
    }
    return false;
}

void Table::rotate() {
    block_.rotate();
    // 如果有碰撞，则再旋转三次还原
    if(touch(block_) != TouchType::NONE) {
        block_.rotate();
        block_.rotate();
        block_.rotate();
    }
}

Table::TableArr Table::map() {
    // 去掉 Spawn Area
    TableArr copy = TableArr(height_, std::vector<Color>(width_));
    for(int i = 0; i < height_; i++) {
        for(int j = 0; j < width_; j++) {
            copy.at(i).at(j) = map_.at(i + hidden_).at(j);
        }
    }

    // Block 下落位置
    Block shadow_block = block_;
    for(int i = 0; i < map_.size(); i++) {
        shadow_block.move(0, 1);
        if(touch(shadow_block) != TouchType::NONE) {
            shadow_block.move(0, -1);
            break;
        }
    }
    block::BlockArr arr_s = shadow_block.arr();
    size_t x = 0, y = 0;
    for(int i = shadow_block.y(); i <= shadow_block.bottom(); i++) { // 行
        x = 0;
        for(int j = shadow_block.x(); j <= shadow_block.right(); j++) { // 列
            if((i >= hidden_ && i < height_ + hidden_)
                        && (j >= 0 && j < width_)
                        && arr_s.at(y).at(x) == 1) {
                copy.at(i - hidden_).at(j) = (Color)((int)shadow_block.color() + 6);
            }
            x++;
        }
        y++;
    }

    // Block 位置
    block::BlockArr arr = block_.arr();
    y = 0;
    for(int i = block_.y(); i <= block_.bottom(); i++) { // 行
        x = 0;
        for(int j = block_.x(); j <= block_.right(); j++) { // 列
            if((i >= hidden_ && i < height_ + hidden_)
                        && (j >= 0 && j < width_)
                        && arr.at(y).at(x) == 1) {
                copy.at(i - hidden_).at(j) = block_.color();
            }
            x++;
        }
        y++;
    }

    return copy;
}

Table::TableArr Table::map_for_check() {
    TableArr copy = map_;
    size_t x = 0, y = 0;
    block::BlockArr arr = block_.arr();
    for(int i = block_.y(); i <= block_.bottom(); i++) { // 行
        x = 0;
        for(int j = block_.x(); j <= block_.right(); j++) { // 列
            if((i >= 0 && i < height_ + hidden_)
                        && (j >= 0 && j < width_)
                        && arr.at(y).at(x) == 1) {
                copy.at(i).at(j) = block_.color();
            }
            x++;
        }
        y++;
    }
    return copy;
}

size_t Table::width() {
    return width_;
}

size_t Table::height() {
    return height_;
}

void Table::move_block(int x) {
    block_.move(x, 0);
    if(touch(block_) != TouchType::NONE) {
        block_.move(-x, 0);
    }
}

bool Table::gravity() {
    block_.move(0, 1);
    if(touch(block_) == TouchType::BOTTOM) {
        block_.move(0, -1);
        set_block();
        return true;
    }
    return false;
}

void Table::set_block() {
    map_ = map_for_check();
    removed_line_ = remove_line();
}

TouchType Table::touch(Block block) {
    // 检查边界
    if(block.left() < 0 || block.right() > width_ - 1) {
        return TouchType::BORDER;
    } else if(block.bottom() >= height_ + hidden_) {
        return TouchType::BOTTOM;
    }
    // 检查其他方块
    size_t x = 0, y = 0;
    block::BlockArr arr = block.arr();
    for(int i = block.y(); i <= block.bottom(); i++) { // 行
        x = 0;
        for(int j = block.x(); j <= block.right(); j++) { // 列
            if((i > hidden_ - 1 && i < height_ + hidden_) && (j >= 0 && j < width_)) {
                if(arr.at(y).at(x) == 1 && map_.at(i).at(j) != Color::NONE) {
                    return TouchType::BOTTOM;
                }
            }
            x++;
        }
        y++;
    }

    return TouchType::NONE;
}

int Table::remove_line() {
    int count = 0;
    for(size_t i = hidden_; i < height_ + hidden_; i++) {
        bool remove = true;
        for(size_t j = 0; j < width_; j++) {
            if(map_.at(i).at(j) == Color::NONE) {
                remove = false;
                break;
            }
        }
        if(remove) {
            count++;
            for(size_t row = i; row > hidden_ - 1; row--) {
                for(size_t j = 0; j < width_; j++) {
                    map_.at(row).at(j) = map_.at(row - 1).at(j);
                }
            }
            for(int row = hidden_; row >= 0; row--) {
                for(size_t j = 0; j < width_; j++) {
                    map_.at(row).at(j) = Color::NONE;
                }
            }
        }
    }
    return count;
}