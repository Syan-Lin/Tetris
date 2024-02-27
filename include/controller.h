#pragma once
#include <functional>
#include "display.h"
#include "keyboard.h"
#include "table.h"

// 每多少毫秒下降一格
enum class Difficulty {
    EASY    = 500,
    NORMAL  = 350,
    HARD    = 200,
    HELL    = 100
};

class Controller {
public:
    Controller(size_t width, size_t height, int fps);

    void init();

    void set_difficulty(Difficulty difficulty);

    void menu();

    void choose_difficulty();

    void game_start();

    void game_over(Block block);

    void move_block(Input in, Block& block);

    void loop(std::function<bool(Input)>&& func);

private:
    Block generate_block();

private:
    Display screen_;
    Table table_;
    Keyboard key_;
    Difficulty difficulty_;
    unsigned int frames_;
    int fps_;
    int scores_;
    bool pause_;
    bool game_over_;
};