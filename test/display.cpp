#include "display.h"
#include "block.h"
#include "controler.h"
#include "table.h"

using namespace std;

int main() {
    Display display;
    display.clear();
    char s;

    Table::TableArr map = {
        {(Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0},
        {(Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0},
        {(Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0},
        {(Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0},
        {(Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0},
        {(Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0},
        {(Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0},
        {(Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0},
        {(Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0},
        {(Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0},
        {(Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0},
        {(Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0},
        {(Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0},
        {(Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0},
        {(Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0},
        {(Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0},
        {(Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0},
        {(Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0},
        {(Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0},
        {(Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0, (Color)0},
        {(Color)1, (Color)2, (Color)3, (Color)4, (Color)5, (Color)5, (Color)5, (Color)5, (Color)5, (Color)5},
        {(Color)6, (Color)0, (Color)1, (Color)1, (Color)1, (Color)1, (Color)1, (Color)1, (Color)1, (Color)1},
        {(Color)1, (Color)2, (Color)3, (Color)4, (Color)5, (Color)5, (Color)5, (Color)5, (Color)5, (Color)5},
        {(Color)6, (Color)0, (Color)1, (Color)1, (Color)1, (Color)1, (Color)1, (Color)1, (Color)1, (Color)1},
    };
    Table table = Table(10, 20, map);
    Block block = Block(BlockType::STAIR_LEFT, Color::BLUE, 0, 4);
    table.spawn(block);
    display.game_panel(table, 123, Difficulty::EASY, block, true, 1);

    cout << "输入任意键到下一个 UI" << endl;
    cin >> s;
    display.clear();
    display.main_menu(0);

    cout << "输入任意键到下一个 UI" << endl;
    cin >> s;
    display.clear();
    display.difficulty(4);

    return 0;
}