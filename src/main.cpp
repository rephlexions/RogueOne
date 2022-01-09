#include <ncurses.h>
#include <iostream>
#include <string>
#include "./Player/Player.h"
#include "./Room/Room.h"
#include "./Position/Position.h"
#include "./Level/Level.h"
#include "./utils/utils.h"

using namespace std;

int main()
{

    Position newPosition;
    int inputChar;
    screenSetup();
    Level level(3);
    addMonsters(level);
    // ASCII 113 -> 'q'
    while ((inputChar = getch()) != 113)
    {
        newPosition = handleInput(inputChar, level.player);
        checkPosition(newPosition, level.player, level.getTiles());
        moveMonster(level);
    }

    endwin();
    return 0;
}
