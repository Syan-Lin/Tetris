#pragma once

enum class Input {
    LEFT,
    RIGHT,
    DOWN,
    ROTATE,
    PAUSE,
    NONE
};

int get_input();
void init();

// 非阻塞监听键盘输入
class Keyboard {
public:
    Keyboard();
    Input input();
    char key();
};