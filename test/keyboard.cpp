#include <thread>
#include <iostream>
#include "keyboard.h"

using namespace std;

int main() {
    Keyboard key;
    while(true) {
        Input input = key.input();
        switch(input) {
            case Input::LEFT:
                cout << "LEFT" << endl;
                break;
            case Input::RIGHT:
                cout << "RIGHT" << endl;
                break;
            case Input::DOWN:
                cout << "DOWN" << endl;
                break;
            case Input::ROTATE:
                cout << "ROTATE" << endl;
                break;
            case Input::PAUSE:
                cout << "PAUSE" << endl;
                break;
            case Input::NONE:
                break;
        }
        this_thread::sleep_for(33ms);
    }
    return 0;
}