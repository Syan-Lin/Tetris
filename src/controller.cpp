#include "controller.h"
#include "block.h"
#include <thread>
#include <chrono>
#include <math.h>

Controller::Controller(size_t width, size_t height, int fps)
        : table_(width, height), fps_(fps) {
    init();
}

void Controller::init() {
    frames_ = 0;
    scores_ = 0;
    pause_ = false;
    game_over_ = false;
    table_.reset_map();
}

void Controller::set_difficulty(Difficulty difficulty) {
    difficulty_ = difficulty;
}

void Controller::menu() {
    int select = 1;
    auto menu_func = [&select, this](Input in) -> bool {
        screen_.clear();
        screen_.main_menu(select);
        switch(in) {
            case Input::ROTATE:
                select--;
                if(select < 1) {
                    select = 2;
                }
                break;
            case Input::DOWN:
                select++;
                if(select > 2) {
                    select = 1;
                }
                break;
            case Input::PAUSE:
                return true;
            default: break;
        }
        return false;
    };
    loop(menu_func);

    if(select == 1) {
        choose_difficulty();
    }
}

void Controller::choose_difficulty() {
    int select = 1;

    auto difficulty_func = [&select, this](Input in) -> bool {
        screen_.clear();
        screen_.difficulty(select);
        switch(in) {
            case Input::ROTATE:
                select--;
                if(select < 1) {
                    select = 4;
                }
                break;
            case Input::DOWN:
                select++;
                if(select > 4) {
                    select = 1;
                }
                break;
            case Input::PAUSE:
                return true;
            default: break;
        }
        return false;
    };
    loop(difficulty_func);

    switch(select) {
        case 1:
            set_difficulty(Difficulty::EASY);
            break;
        case 2:
            set_difficulty(Difficulty::NORMAL);
            break;
        case 3:
            set_difficulty(Difficulty::HARD);
            break;
        case 4:
            set_difficulty(Difficulty::HELL);
            break;
        default: break;
    }
    game_start();
}

Block Controller::generate_block() {
    int x = rand() % (table_.width() - 3);
    BlockType type = static_cast<BlockType>(rand() % 8);
    return Block(type, x, 0);
}

void Controller::game_start() {
    init();

    table_.spawn(generate_block());
    Block block = generate_block();
    int frame_per_milliseconds = 1000 / fps_;
    screen_.clear();
    screen_.game_table(table_);
    screen_.score_panel(table_.width(), scores_);
    screen_.difficulty_panel(table_.width(), difficulty_);
    screen_.next_panel(table_.width(), block);
    screen_.operation_panel(table_.width());

    auto game_func = [&, this](Input in) -> bool {
        if(game_over_) {
            return true;
        }
        if(in == Input::PAUSE) {
            pause_ = !pause_;
        }
        if(!pause_) {
            screen_.game_table(table_);
            move_block(in, block);

            // 自动下降
            int drop_per_frames = static_cast<int>(difficulty_) / frame_per_milliseconds;
            if(frames_ % drop_per_frames == 0) {
                move_block(Input::DOWN, block);
            }
        } else {
            screen_.pause_panel(table_.width(), table_.height());
        }
        frames_++;
        return false;
    };
    loop(game_func);
    if(game_over_) {
        game_over(block);
    }
}

void Controller::game_over(Block block) {
    int select = 1;
    auto game_over_func = [&, this](Input in) -> bool {
        screen_.game_over_panel(table_.width(), table_.height(), select);
        switch(in) {
            case Input::ROTATE:
                select--;
                if(select < 1) {
                    select = 2;
                }
                break;
            case Input::DOWN:
                select++;
                if(select > 2) {
                    select = 1;
                }
                break;
            case Input::PAUSE:
                return true;
            default: break;
        }
        return false;
    };
    loop(game_over_func);

    if(select == 1) {
        game_start();
    } else {
        menu();
    }
}

void Controller::move_block(Input in, Block& block) {
    if(table_.update(in)) {
        if(table_.game_loss()) {
            game_over_ = true;
        } else {
            table_.spawn(block);
            block = generate_block();
            screen_.next_panel(table_.width(), block);
        }
        int lines = table_.removed_lines();
        if(lines > 0) {
            scores_ += 100 * pow(lines, 2);
            screen_.score_panel(table_.width(), scores_);
        }
    }
}

void Controller::loop(std::function<bool(Input)>&& func) {
    using std::chrono::milliseconds, std::this_thread::sleep_for;
    int frame_per_milliseconds = 1000 / fps_;

    while(true) {
        sleep_for(milliseconds(frame_per_milliseconds));

        Input in = key_.input();
        bool state = func(in);
        if(state) {
            break;
        }
    }
}