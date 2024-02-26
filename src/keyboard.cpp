#include "keyboard.h"

#ifdef _WIN32
#include <conio.h>

int get_input() {
    int code = 0;
    if(_kbhit()) {
        code = _getch();
    }
    return code;
}
void init() {

}
#endif

#ifdef linux
#include <unistd.h>
#include <termios.h>
#include <sys/select.h>

int get_input() {
    int code = 0;
    fd_set rfds;
    struct timeval tv;

    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&rfds);
    FD_SET(STDIN_FILENO, &rfds);

    int retval = select(STDIN_FILENO + 1, &rfds, NULL, NULL, &tv);

    if (retval > 0) {
        // 监听到输入
        read(STDIN_FILENO, &code, 1);
    }
    return code;
}
void init() {
    // 获取当前终端设置
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);

    // 设置为非阻塞模式
    term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
#endif

Keyboard::Keyboard() {
    init();
}

Input Keyboard::input() {
    int code;
    code = get_input();
    switch(code) {
        case 'a': case 'A':
            return Input::LEFT;
        case 'd': case 'D':
            return Input::RIGHT;
        case 's': case 'S':
            return Input::DOWN;
        case 'w': case 'W':
            return Input::ROTATE;
        case ' ':
            return Input::PAUSE;
        default:
            return Input::NONE;
    }
}

char Keyboard::key() {
    char code = 0;
    while(true) {
        code = get_input();
        if(code) {
            break;
        }
    }
    return code;
}